/**
* File: child.c
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h> 

int main(int argc, char *argv[]) { 
	//Initialize the variables
	pid_t pid; 
	int ret_value;
	
	//Check that all the arguments are there
	if (argc != 3) { 
		printf("\n Usage: %s <value> <sleeptime[1,49]>\n", argv[0]); 
		exit(1); 
	}
	
	int T = atoi(argv[2]); //Sleeptime
	
	//Check that the sleep time is within range
	if ( T < 1 || T > 49 ){
		printf("\n Sleeptime must be between 1 and 49, inclusive.\n");
		exit(1);
	}
	 
 	pid = getpid(); 
	ret_value = (int) (pid % 256); //calculate the return address value
	srand((unsigned) pid); //generate a random number within range
	sleep(rand() % T); 
 	
	if (atoi(*(argv + 1)) % 2) { 
		printf("Child %d is terminating with signal 009\n", pid);
		kill(pid, 9); 
 	} else { 
		printf("Child %d is terminating with exit(%04X)\n", pid, ret_value); 
		exit(ret_value); 
	}
} 