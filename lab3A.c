/*********************
Author: Edgar Cobos
Filename: Lab3A.c
**********************/
# include <stdio.h> 
# include <stdlib.h> 
# include <sys/types.h> 
# include <unistd.h> 
int main(int argc, char *argv[]) 
{ 
	if (argc > 1) { 
		execlp("/Users/ecobos/Documents/csulb/cecs_326/lab1/lab1", "LabOne", argv[1], (char *) NULL); 
		perror ("exec failure"); 
		exit(1); 
 	} 
 
	printf("\n Usage: %s <argument>\n", *argv); 
	exit(1) ; 
} 
