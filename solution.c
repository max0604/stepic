#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>

const int semaphore_nb = 16;

int main()
{
	key_t key = ftok("/tmp/sem.temp", 1);

	int sem_set_id = semget(key, semaphore_nb, IPC_CREAT);
	if( -1 == sem_set_id ) {
		perror("semget");
	}
	
	unsigned short args[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

	int res = semctl( sem_set_id, 0, SETALL, args );
	
	
	res = semctl(sem_set_id, 0, IPC_RMID, 0);
	if( -1 == res ) {
		perror("semctl IPC_RMID");
	}
	return 0;
}
