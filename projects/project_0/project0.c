/**
 * By: Joe Cormier
 * Description: This program is to demonstrate my general understanding of the C language.
 **/

#include <stdio.h>
#include <stdlib.h>

void print_backwards( FILE *, FILE * );
void prn_info( char * );

/**
 * main 
 **/
main( int argc, char **argv ){
	FILE *ifp, *ofp;
	if ( 3 != argc ){
		prn_info( argv[0] );
		exit( 1 );
	}
	// open for reading 
	ifp = fopen( argv[1], "r" ); 
	
	//open for writing
	ofp = fopen( argv[2], "w" );

	print_backwards( ifp, ofp );
	fclose( ifp );
	fclose( ofp );
}//end main

/**
 * print backwards
 * FILE *ifp, FILE *ofp
 * prints a file backwards into another file
 **/
void print_backwards( FILE *ifp, FILE *ofp ){
	char helper[256];
	int x;
	while( EOF != ( fgets( helper, 1000, ifp ) ) ){
		fputs( helper, ofp );
		fseek( ofp, 0, SEEK_SET );
	} 
}// end print_backwards

/**
 * prn_info
 * char *pgm_name
 * prints out the program usage
 **/
void prn_info( char *pgm_name ){
	printf( "\n%s%s%s\n\n%s%s\n\n",
					"Usage: ", pgm_name, " infile outfile",
					"The contents of infile will be double-spaced ",
					"and written to outfile." );
}//end prn_info
