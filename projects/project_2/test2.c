#include <stdio.h>
#include <stdlib.h>
char string0[] = "Hello, this is the parent process";
char string1[] = "Hi, this is the child process 1";
char string2[] = "Hi, this is the child process 2";
main(){
	char buf[1024];
	int i, fds0[2], fds1[2], fds2[2];
	pipe(fds0); //pipe used by the parent process--zs
	pipe(fds1); //pipe used by the child 1 process--zs
	pipe(fds2); //pipe used by the child 2 process--zs
	//The first child process is created.--zs
	if(fork()==0) {
		close(fds0[1]);
		//read from the parent --zs
		read(fds0[0], buf, sizeof(string0));
		printf("child 1 reads: %s\n", buf);
		//write child message to parent via its pipe--zs
		close(fds1[0]);
		write(fds1[1], string1, sizeof(string1));
		exit(0);
	}
	//The second child process--zs
	else if(fork()==0) {
		sleep(1);
		close(fds0[1]);
		//Get something from the parent process--zs
		read(fds0[0], buf, sizeof(string0));
		printf("child 2 reads: %s\n", buf);
		//write child message into fds2
		close(fds2[0]);
		write(fds2[1], string2, sizeof(string2));
		exit(0);
	}
	else {//Parent process starts--zs
		//write parent message into fds0
		close(fds0[0]);
		write(fds0[1], string0, sizeof(string0));
		//read child 1 message from its associated pipe--zs
		
		close(fds1[1]);
		read(fds1[0],buf,sizeof(string1));
		printf("parent reads from Child 1: %s\n", buf);
		
		//write something into fds0 again to child 2--zs
		close(fds0[0]);
		write(fds0[1], string0, sizeof(string0));

		//read child 2 message from its associated pipe--zs
		close(fds2[1]);
		read(fds2[0],buf,sizeof(string2));
		printf("parent reads from Child 2: %s\n", buf);
		exit(0);
		}
}
