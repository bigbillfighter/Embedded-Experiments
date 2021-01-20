#include <stdio.h>

int main(){
    int a = 1, i=1;
    while(i<10) a*=i++;
    printf("%d\n", a);
    return 0;
}
