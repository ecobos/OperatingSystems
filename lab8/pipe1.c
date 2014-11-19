#include <stdio.h>
#include <stdlib.h> 
#include <limits.h>
#include <unistd.h> 
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

/* Named pipe pipe1.c */ 
/* Usage: pipe1 pipename. Child writes a message to parent */ 

# define BUFSIZE 256 
int main(int argc, char *argv[]) { 
	//declre the FIFO persmission
 	mode_t fifo_mode = S_IRUSR | S_IWUSR; 
	int fd, status, child; 
	char buf[BUFSIZE]; 
	unsigned strsize; 
 
	//make sure that the proper number of arguments are supplied
	if (argc !=2) { 
		printf ("\n Usage: %s pipename\n", argv[0]); 
		exit(1); 
	} 
 
	/* generate a named pipe with r/w for user */ 
 	if ((mkfifo(argv[1],fifo_mode) == -1) && (errno != EEXIST)) { 
		//only execute if there is and issue creating the pipe
		perror ("Pipe"); 
		exit(1); 
	} 
 
	if (( child = fork()) == -1) { 
		perror ("Fork"); 
		exit(1); 
	} 
 	else if (child == 0){ 
		//child if goign to attempt opening the pipe
		printf ("\nChild %ld is about to open FIFO %s\n", (long)getpid(), argv[1]); 
 		if ((fd = open(argv[1], O_WRONLY)) == -1) {
			perror("Child cannot open FIFO"); 
			exit(1);
		} 
 
		/* In the child */ 
		// convert the long pid into a char*
 		sprintf (buf, "This was written by child %ld\n", (long)getpid()); 
		//string size needed for the write() function
		strsize = strlen(buf) + 1; 
 	
		//write the message to the queue
		if (write(fd, buf, strsize) != strsize) { 
			printf("Child write to FIFO failed\n"); 
			exit(1); 
		} 
 		printf ("Child %ld is done\n", (long)getpid()); 
	} else { /* parent does a read */ 
		//parent tries to read from the queue
 		printf ("Parent %ld is about to open FIFO %s\n", (long) getpid(), argv[1]); 
 		if ((fd = open(argv[1], O_RDONLY | O_NONBLOCK)) == -1) { 
			//only execute if there is an issue opening the pipe
			perror("Parent cannot open FIFO"); 
			exit(1); 
		} 
 		printf ("Parent is about to read\n");
		//wait for the child process to exit 
 		while ((wait(&status) == -1) && (errno == EINTR)); 
 		//parent tries to read from the queue (buffer)
		if (read(fd, buf, BUFSIZE) <=0) { 
			perror("Parent read from FIFO failed\n");
			exit(1); 
		} 
 		printf ("Parent %ld received: %s\n", (long)getpid(), buf); 
 	} 
 	exit(0); 
} 