#include <stdio.h>

int arr[10];


int oz(int a){
    return arr[a];
}


int phypo(int a){
    return (a+1)*oz(a);
}

int main(){
    arr[0] = arr[1] = 1;
    for(int i=2; i<10; i++){
    	arr[i] = arr[i-1]+arr[i-2];
    }
    int a=10, b=1;
    for(int c=0; c<a; c++){
	b += phypo(c);
	printf("b: %d\n", b);
    
    }
    return 0;
}
