#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

int main()
{
	key_t key = ftok("/tmp/msg.temp", 1);

	int q_id = msgget(key, IPC_CREAT | 0777 );

	if( -1 == q_id ) {
		perror("msgget");
		return -1;
	}
	
	char buffer[100] = { 0 };
	
	ssize_t nb = msgrcv(q_id, buffer, sizeof(buffer), 0, 0);
	
	if( -1 == nb ) {
		perror("msgrcv");
	} else if(nb > 0) {
		FILE* file = fopen("/home/box/message.txt", "w+");
		if( !file ) {
			perror("fopen");
		} else {
			fprintf(file, "%s", buffer);
			fclose(file);
		}
	}
	msgctl(q_id, IPC_RMID, NULL);
	return 0;
}




