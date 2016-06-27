#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

const int length = 1024*1024;

int main()
{
	shm_unlink("test.shm");
	int fd = shm_open("test.shm", O_CREAT | O_EXCL | O_RDWR, 0666);
	if(-1 == fd) {
		perror("shm_open");
		return -1;
	}
	int res = ftruncate(fd, length);
	if(-1 == res) {
		perror("ftruncate");
	}

	char* ptr = mmap(NULL, length, PROT_WRITE, MAP_SHARED, fd, 0);
	if( (void*)-1 == ptr ) {
		perror("mmap");
		return -1;
	}

	memset(ptr, 13, length);
	
	res = munmap(ptr, length);
	if(-1 == res) {
		perror("munmap");
		return -1;
	}

	res = shm_unlink("test.shm"); 
	if(-1 == res) {
		perror("sem_unlink");
		return -1;
	}
	return 0;
}
