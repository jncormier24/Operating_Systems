/**
 * Integrate with Trapazoids
 * By: Joe Cormier
 * This program will find the area of under a curve using the trapazoidal rule.
 * Each trapazoid will execute in a new process and report back to the main process 
 * **/

#include <stdio.h>
#include <stdlib.h>
int fd1[2], fd2[2], fd3[2], fd4[2], fd5[2], fd6[2], fd7[2], fd8[2], N, i;
float total, upper, lower, helper, trap;
char buf[1024];
char str[256];

float do_calc( float n ){
	//do some calculations
	return (1.0 / ( n + 1.0) );
}

main(){
	float b = 2.0;
	float a = 0.0;
	int c = 1;
	int n = 64;
	total = 0;
	pid_t pid;
	pipe( fd1 );
	pipe( fd2 );

	if( 0 > ( pid = fork() ) ){
		//there is an error
		exit(0);
	}
	else if( 0 == pid ){
		//the child is now doing things
		while(1){
			close( fd2[1] );
			read( fd2[0], buf, sizeof( buf ) );
			sscanf(buf, "%f", &trap);
			
			helper = do_calc( trap );
			sprintf(str, "%f", helper);
			close( fd1[0] );
			write( fd1[1], str, sizeof( str ) );	
		}
	}
	else{
		//the parent is now doing things
		for(i = 0; i <= n; i++){
			if( 1 == i || 64 == i ){
				i = i * 1.0;
				trap = ( (b - a) / n ) * i;
				sprintf(str, "%f", trap);
				close( fd2[0] );
				write( fd2[1], str, sizeof( str ) );	
			
				close( fd1[1] );
				read( fd1[0], buf, sizeof( buf ) );
				sscanf(buf,"%f",&helper);
				total = total + helper;
			}
			else{
				i = i * 1.0;
				trap = ( (b - a) / n ) * i;
				sprintf(str, "%f", trap);
				close( fd2[0] );
				write( fd2[1], str, sizeof( str ) );	
			
				close( fd1[1] );
				read( fd1[0], buf, sizeof( buf ) );
				sscanf(buf,"%f",&helper);
				total = total + (2.0 * helper);
			}
		}
		total = ( ( b - a ) / ( 2 * n ) ) * total;
		printf("This is the total: %f. \n", total);
	}
}
