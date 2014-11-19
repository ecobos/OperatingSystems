#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>

/* Unnamed pipe pipe.c */ 
/* Usage: pipe message_to_be_written. Parent write a message to child */ 

int main(int argc, char *argv[]) { 
 	int f_des[2]; //use for the message queue
	static char message[BUFSIZ]; 
	char buffer[MAX_CANON]; 
	//char *c; 
	int i, k, n; 
	pid_t childpid;
	 
	//make sure that the proper number of arguments are supplied
 	if (argc !=2) { 
		printf ("\n Usage: %s message\n", *argv); 
		exit(1);
	} 
 	
	/* generate pipe */ 
	if (pipe(f_des) == -1) { 
		//only execute if there is an issue creating the pipe
		perror ("Pipe"); 
		exit(2); 
	} 
 	
	switch (fork()) { 
 		case -1:
			//only execute if there is an issue forking 
			perror ("Fork"); 
			exit(3); 
 		case 0: /* In the child */ 
 			//delete the file descriptor for the read buffer
			close(f_des[0]); 
			//write the message to the buffer
			if (write(f_des[0], argv[1], strlen(argv[1])) != -1) { 
				printf ("Message sent by child: *%s*\n", argv[1]); 
				fflush(stdout); 
			} 
 			else { 
				perror ("Read"); 
				exit(4);
			} 
			break; 
 		default: /* In the parent */ 
			//delete the file descriptor for the write buffer
			close(f_des[1]);
			//read a message from the buffer 
 			if (read(f_des[1], message, BUFSIZ) != -1){ 
 				printf ("Message read by parent: [%s]\n", message); 
				fflush(stdout); 
			} 
 			else { 
				perror ("Write"); 
				exit(5); 
			} 
 	} 
 	exit(0); 
} 