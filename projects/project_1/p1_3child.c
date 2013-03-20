#include <stdio.h>
int main(){
	printf("Process[%d]: child in execution...\n", getpid());
	sleep(2);
	printf("Process[%d]: child terminating...\n", getpid());
}
