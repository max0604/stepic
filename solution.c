#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>

int main()
{
	//mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
	//int mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio);
	//ssize_t mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio);
	struct mq_attr attr;
	attr.mq_maxmsg = 5;
	attr.mq_msgsize = 256;
	mqd_t q_id = mq_open("/test.mq", O_CREAT | O_RDONLY, 0664, &attr );
	if( -1 == q_id ) {
		perror("mq_open");
	}

	long buffer_size = attr.mq_msgsize + 1;
	char* memory = malloc( buffer_size );
	memset(memory, 0, buffer_size);
	ssize_t nb =  mq_receive(q_id, memory, buffer_size - 1, NULL);

	if( nb > 0 ) {
		FILE* file = fopen("/home/box/message.txt", "w+");
		fprintf(file, "%s", &memory[0]);
		fclose(file);
	} else {
		perror("mq_receive");
	}
	free(memory);
	mq_close(q_id);
	mq_unlink("/test.mq");
	return 0;
}
