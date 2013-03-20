#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int globalVar = 6; /* external variable in the initialized data */
char buf[] = "Write to the standard output\n";

int main(){
	int localVar; /* local variable in the initialized data */
	pid_t pid;
	localVar = 88;
	if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1){
		printf("write error");
		exit(1);
	}
	printf("Now, the fork starts\n");
	if ( (pid = fork()) < 0){
		printf("fork error\n");
		exit(1);
	}
	else if (pid == 0) {
		globalVar++;
		localVar++;
		//1.exit(0);
	}
		//2. 
	else sleep(2);
	printf("pid = %d, globalVar = %d, localVar = %d\n", getpid(), globalVar, localVar);
	exit(0);
}
