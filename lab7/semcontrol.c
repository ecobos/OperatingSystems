# include <stdio.h>
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/sem.h>
# include <unistd.h>
# include <stdlib.h>
# define NS 3 
//time.h is included to be able to use the 'ctime' function
# include <time.h>

/*************************** 
Already defined in the system files (usr/include/sys/sem.h). Commenting out.

union semun {
	int val; 
	struct semid_ds *buf; 
	ushort *array;
}; 
****************************/

int main(void) {
	int sem_id, sem_value, i; 
	key_t ipc_key; //used to setore the unique key for the semaphore
	struct semid_ds sem_buf; 
	static ushort sem_array[NS] = {-3, 1, 4}; //define the semaphore set
	union semun arg;
	ipc_key = ftok(".", 'S'); //generate the unique key for the semaphore
	
	// Create semaphore and add IPC_EXCL creation condition to the semflag parameter
	// IPC_EXCL forces semget to fail if the semaphore already exists
	if ((sem_id = semget(ipc_key, NS, IPC_CREAT | 0666 | IPC_EXCL)) == -1) {
		perror ("semget: IPC | 0666"); //should only execute if there is an issue with semget
		exit(1);
	}
	printf ("Semaphore identifier %d\n", sem_id);
	/* Set arg (the union) to the address of the storage location for */
	/* returned semid_ds value */
	arg.buf = &sem_buf;
	
	// Fetch the semaphore set's struct semid_ds, storing it in the memory pointed to by arg.buf
	if (semctl(sem_id, 0, IPC_STAT, arg) == -1) {
		perror ("semctl: IPC_STAT"); //should only execute if there is an issue with semctl
		exit(2);
	}
	printf ("Create %s", ctime(&sem_buf.sem_ctime));
	
	/* Set arg (the union) to the address of the initializing vector */
	arg.array = sem_array;
	
	//Set the values of all the semaphores in the set to the values in the array pointed to by arg.array
	if (semctl(sem_id, 0, SETALL, arg) == -1) {
		perror("semctl: SETALL");
		exit(3);
	}
	
	//Itereate through and return the value of semaphore at semnum i
	for (i=0; i<NS; ++i) {
		if ((sem_value = semctl(sem_id, i, GETVAL, 0)) == -1) {
			perror("semctl : GETVAL");
			exit(4);
		}
		printf ("Semaphore %d has value of %d\n",i, sem_value);
	}
	
	/*** remove semaphore *** 
	
	if (semctl(sem_id, 0, IPC_RMID, 0) == -1) {
		perror ("semctl: IPC_RMID");
		exit(5);
	}
	*/
}