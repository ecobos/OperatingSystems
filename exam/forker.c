#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main (){
	pid_t childpid;
	childpid = 0;
	
	childpid = fork();
	if(childpid != 0){
		printf("\nMy process ID is %d and child is %d \n", getpid(), childpid);
		wait(15);
	}
	else {
		printf("I am a child process, my ID is %d\n", getpid());
	}
	exit(1);
}
