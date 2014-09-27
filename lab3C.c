# include <stdio.h> 
# include <stdlib.h> 
# include <sys/types.h> 
# include <unistd.h> 
int main(int argc, char *argv[]) 
{ 
	static char *new_argv[] = {"LabOne","5", (char *) 0}; 
	execvp("/Users/ecobos/Documents/csulb/cecs_326/lab1/lab1", new_argv); 
	perror("exec failure"); 
	exit(1); 
} 
