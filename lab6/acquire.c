/***********************************************************************************
 PROGRAM: acquire.c
 DESCRIPTION: This program attempts to create a lock file. If it fails then it the
	process goes to sleep for a random time. Wakes up then tries again N number of
	times before giving up. 
************************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h> 
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{ 
	char *fname; //declare a pointer to the char array (string)
	int fd, sleeptime, n_try, //declare file status, sleep time and number of tries
	count = 0; // initialize the count
	pid_t pid = getpid(); //get the process ID	
	srand((unsigned) pid); //set the random number seed
	
	//Make sure that the proper number of areguments are supplied
	if(argc != 4){
		printf("\nUsage: %s <lock file name> <sleep time> <number of tries>\n", argv[0]);
		exit(1);
	}
	 
	fname = argv[1]; //get the lock file name to create
	sleeptime = atoi(argv[2]); //get the sleep time argument
	//Make sure that the sleep time is not a negative value
	if(sleeptime < 1){
		printf("\nError: Sleeptime has to be an integer greater than zero\n");
		exit(1);
	}
	n_try = atoi(argv[3]); //get the number of tries aregument
 	
	// creat success returns an int. Failure returns -1, sets errno
	while ((fd = creat(fname, 0)) == -1 && errno == EACCES) {
		//If there is a failure with creating the file, then 
		// increment the count of tries and place the process to sleep for period of time 
 		if (++count < n_try) 
			sleep(rand()%sleeptime); //place proc to sleep for a random time within range
 		else { 
			//if the file can't be created after the specified tries, the print out the error and exit out
			printf ("\n Unable to generate.\n"); exit(-1); 
 		} 
	}
 	//deletes the descriptor from the per-process obj reference table
	close (fd); 	
	//This only prints if the lock file was created succcessfully
	printf ("\n File %s has been created\n", fname);
	
} 
