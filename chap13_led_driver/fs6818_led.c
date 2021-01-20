#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <mach/platform.h>
#include <mach/gpio.h>
#include <asm/gpio.h>
#include <linux/device.h>

#include "fs6818_led.h"

MODULE_LICENSE("Dual BSD/GPL");

#define LED_MA 500
#define LED_MI 0
#define LED_NUM 1

#define LED_D10			(PAD_GPIO_C + 2)
#define LED_D9			(PAD_GPIO_B + 12)
#define LED_D8			(PAD_GPIO_E + 13)
#define LED_D7			(PAD_GPIO_A + 28)
#define LED_D19			(PAD_GPIO_B + 9)
#define LED_D18			(PAD_GPIO_C + 30)
#define LED_D17			(PAD_GPIO_D + 22)
#define LED_D12			(PAD_GPIO_D + 27)


struct cdev cdev;
struct class *class;
struct device *device;

void fs6818_led_on(int nr)
{
	switch(nr) {
	case LED1: 
		gpio_set_value(LED_D10, 1);	
		break;
	case LED2: 
		gpio_set_value(LED_D9, 1);	
		break;
	case LED3: 
		gpio_set_value(LED_D8, 1);	
		break;
	case LED4: 
		gpio_set_value(LED_D7, 1);	
		break;
	case LED5: 
		gpio_set_value(LED_D19, 1);	
		break;
	case LED6: 
		gpio_set_value(LED_D18, 1);	
		break;
	case LED7: 
		gpio_set_value(LED_D17, 1);	
		break;
	case LED8: 
		gpio_set_value(LED_D12, 1);	
		break;
	}
}

void fs6818_led_off(int nr)
{
	switch(nr) {
	case LED1: 
		gpio_set_value(LED_D10, 0);
		break;
	case LED2: 
		gpio_set_value(LED_D9, 0);
		break;
	case LED3: 
		gpio_set_value(LED_D8, 0);
		break;
	case LED4: 
		gpio_set_value(LED_D7, 0);
		break;
	case LED5: 
		gpio_set_value(LED_D19, 0);
		break;
	case LED6: 
		gpio_set_value(LED_D18, 0);
		break;
	case LED7: 
		gpio_set_value(LED_D17, 0);
		break;
	case LED8: 
		gpio_set_value(LED_D12, 0);
		break;

	}
}
void fs6818_led_io_init(void)
{
	gpio_request(LED_D10, "fs6818_led");
	gpio_request(LED_D9, "fs6818_led");
	gpio_request(LED_D8, "fs6818_led");
	gpio_request(LED_D7, "fs6818_led");
	gpio_request(LED_D19, "fs6818_led");
	gpio_request(LED_D18, "fs6818_led");
	gpio_request(LED_D17, "fs6818_led");
	gpio_request(LED_D12, "fs6818_led");
}
static int fs6818_led_open(struct inode *inode, struct file *file)
{
	fs6818_led_io_init();
	return 0;
}

static int fs6818_led_release(struct inode *inode, struct file *file)
{
	gpio_free(LED_D10);
	gpio_free(LED_D9);
	gpio_free(LED_D8);
	gpio_free(LED_D7);
	gpio_free(LED_D19);
	gpio_free(LED_D18);
	gpio_free(LED_D17);
	gpio_free(LED_D12);
	return 0;
}

static long fs6818_led_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int nr;

	if(copy_from_user((void *)&nr, (void *)arg, sizeof(nr)))
		return -EFAULT;

//	if (nr < 1 || nr > 4)
//		return -EINVAL;

	switch (cmd) {
	case LED_ON:
		fs6818_led_on(nr);
		printk("LED ON\n");
		break;
	case LED_OFF:
		fs6818_led_off(nr);
		printk("LED OFF\n");
		break;
	default:
		printk("Invalid argument");
		return -EINVAL;
	}

	return 0;
}

struct file_operations fs6818_led_fops = {
	.owner = THIS_MODULE,
	.open = fs6818_led_open,
	.release = fs6818_led_release,
	.unlocked_ioctl = fs6818_led_unlocked_ioctl,
};

static int fs6818_led_init(void)
{
	dev_t devno = MKDEV(LED_MA, LED_MI); 
	int ret;
	ret = register_chrdev_region(devno, LED_NUM, "newled");
	if (ret < 0) {
		printk("register_chrdev_region\n");
		return ret;
	}

	cdev_init(&cdev, &fs6818_led_fops);
	cdev.owner = THIS_MODULE;
	ret = cdev_add(&cdev, devno, LED_NUM);
	if (ret < 0) {
		printk("cdev_add\n");
		goto err1;
	}
	class = class_create(THIS_MODULE, "fs6818_led");	
	if (!class) {
		printk("%s, %s, class_create failed\n", __FILE__, __func__);
		goto err2;
	}

	device = device_create(class, NULL, devno, NULL, "led");
	if (!device) {
		printk("%s, %s, device_create failed\n", __FILE__, __func__);
		goto err3;
	}
	printk("Led init\n");

	return 0;
err3:
	class_destroy(class);
err2:
	cdev_del(&cdev);
err1:
	unregister_chrdev_region(devno, LED_NUM);
	return ret;
}

static void fs6818_led_exit(void)
{
	dev_t devno = MKDEV(LED_MA, LED_MI);

	cdev_del(&cdev);
	unregister_chrdev_region(devno, LED_NUM);
	device_destroy(class, devno);
	class_destroy(class);
	printk("Led exit\n");
}

module_init(fs6818_led_init);
module_exit(fs6818_led_exit);
