#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <pthread.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_barrier_t barrier;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t cond_thread, barrier_thread;

void* m_r(void*) { 
        while(true) { pthread_cond_wait(&cond, &mutex); };
}

void* s_r(void*) {
        while(true) { pthread_barrier_wait(&barrier); };
}

int main()
{
        pid_t pid = getpid();
        FILE* file = fopen("/home/box/main.pid", "w+");
        if(!file) { perror("fopen"); }
        fprintf(file, "%d\n", pid);
        fclose(file);

//	pthread_mutex_lock(&mutex);
	pthread_barrier_init(&barrier, NULL, 1);

	pthread_create(&cond_thread, NULL, m_r, NULL);
	pthread_create(&barrier_thread, NULL, m_r, NULL);

	while(true) {sleep(1);}

}
