#include <stdio.h>
int main(){
    int i=0;
    for(i=0; i<379; i++){
        if(i>=100) fprintf(stdout, "%d", i);
	else if(i>=10) fprintf(stdout, "0%d", i);
	else fprintf(stdout, "00%d", i);
    }
    fprintf(stdout, "\n");
}
