/**
 * This program takes in no parameters. It spawns a child process that will calculate the area of a circle, square, and triangle. 
 * **/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	float t_base = 3.0;
	float t_height = 4.0;
	float triangle;
	float c_radius = 5.0;
	float circle;
	float s_side = 4.0;
	float square;
	pid_t pid;

	if( pid = fork() < 0 ){
		printf("ERROR");
	}
	else if( 0 == pid ){
		square = s_side * s_side;
		circle = 3.14;
		circle = circle * ( c_radius * c_radius );
		triangle = ( t_base * t_height ) / 2;
		printf("The square is %f, the circle is %f, and the triangle is %f.\n", square, circle, triangle);
	}
}
