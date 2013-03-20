/* The parent.c file */
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	if(fork()==0){
		//Notice the following name of "child" is not an accident
		execve("child", NULL, NULL);
		//1. 
		printf("I am done\n");
	}
	printf("Process[%d]: Parent in execution...\n", getpid());
	//2. 
	sleep(1);
	//3. 
	//if(wait(NULL)>0){
		printf("Process[%d]: Parent detects terminating child \n", getpid());
		printf("Process[%d]: parent terminating...\n", getpid());
	//}
}
