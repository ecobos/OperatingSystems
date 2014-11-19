/**
* File: parent.c
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ctype.h> 


int main(int argc, char *argv[]) { 
	//Initialize the variables
	pid_t pid, w; 
	int k, status, N, T; 
	char value[3];
	
	if (argc != 3) { 
			//Check for the arguments
	 		printf("\n Usage: %s <Number of Processes [1,19]> <sleeptime[1,49]>\n", argv[0]); 
		 	exit(1); 
	}
	
	N = atoi(argv[1]); //Number of processes
	T = atoi(argv[2]); //Sleeptime
	
	// Check that the sleep time is within range
	if ( T < 1 || T > 49 ){
			printf("\n Sleeptime must be an integer between 1 and 49, inclusive.\n");
			exit(1);
	}
	
	//Check that the number of processes are within time
	if( N < 1 || N > 19){
		printf("\n Number of processes must be an integer between 1 and 19, inclusive.\n");
		exit(1);
	}
	
	//Create all the processes with this loop 
 	for (k = 0;k < N; ++k) { 
 		if ((pid = fork()) == 0) { 
			sprintf(value, "%d", k); // convert an int to a char array
			execl("child", "child", value, argv[2], (char *) 0); 
		} 
 		else printf ("Forked child %d\n", pid); 
 	} 

	/* Wait for children */ 
 	while ((w = wait(&status)) && w != - 1) { 
		//wait for the process to return a status
 		if (w != - 1) printf ("Wait on PID: %d returns status of: %04X\n", w, status); 
	} 
 	exit(0); 
} 