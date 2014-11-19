/***********************************************************************************
 PROGRAM: release.c
 DESCRIPTION: The program tried to remove the lock file from the working directory
	if it is unable to remove the lock then the process goes to sleep for a random 
	amount of time, with the max sleeptime specified by the command line arguments.
	Once the process wakes up it tries N number of times before giving up.
************************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h> 
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{ 
	char *fname; //declare a pointer to a char array (string)
	int fd, sleeptime, n_try, count=0;  
	pid_t pid = getpid(); //get the process ID 
	srand((unsigned) pid); //set the random number seed
	
	//Make sure that the proper number of areguments are supplied
	if(argc != 4) {
		printf("\nUsage: %s <lock file name> <sleep time> <number of tries>\n", argv[0]);
		exit(1);
	}
	
	fname = argv[1]; //get the lock file name to release
	sleeptime = atoi(argv[2]); //get the sleeptime
	//Make sure that the sleep time is not a negative value
	if(sleeptime < 1){
		printf("\nError: Sleeptime has to be an integer greater than zero\n");
		exit(1);
	} 
	n_try = atoi(argv[3]); //get the number of tries from the arguments supplied
 
    //unlink success returns 0. Failure returns -1, sets errno
	while (unlink(fname)!=0){
		//If there is a failure with unlinking the file, the place the proc to sleep 
 		if (++count < n_try) 
			sleep(sleeptime); //place proc to sleep for a random time within range
 		else { 
			//if the file can't be realeased after the specified number of tries, then exit
			printf ("\n Cannot release file\n"); 
			exit(-1); 
 		} 
	}
	//This prints only if the lock file was unlinked properly
 	printf ("\n File is released\n"); 
 
} 
