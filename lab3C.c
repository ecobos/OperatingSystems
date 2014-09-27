# include <stdio.h> 
# include <stdlib.h> 
# include <sys/types.h> 
# include <unistd.h> 
int main(int argc, char *argv[]) 
{ 
	static char *new_argv[] = {"cat","tester_file.txt", (char *) 0}; 
	execvp("/bin/cat", new_argv); 
	perror("exec failure"); 
	exit(1); 
} 
