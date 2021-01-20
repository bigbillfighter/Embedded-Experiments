#ifndef __FS4418_LED_H__
#define __FS4418_LED_H__

#define LED_MAGIC 'L'
#define LED_ON	_IOW(LED_MAGIC, 0, int)
#define LED_OFF	_IOW(LED_MAGIC, 1, int)


#define RED_LED   'r'
#define GREEN_LED 'g'
#define BLUE_LED  'b'
#define LED1	1
#define LED2	2
#define LED3	3
#define LED4	4
#define LED5	5
#define LED6	6
#define LED7	7
#define LED8	8
#endif
