# include <stdio.h> 
# include <stdlib.h> 
# include <sys/types.h> 
# include <unistd.h> 
int main(int argc, char *argv[]) 
{ 
	execvp(argv[1], &argv[1]); 
	perror("exec failure"); 
	exit(1);
} 
