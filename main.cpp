#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_spinlock_t spin;
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
pthread_t mutex_thread, spin_thread, r_thread, w_thread;

void* m_r(void*) { 
	while(true) { pthread_mutex_trylock(&mutex); }
}

void* s_r(void*) {
	while(true) { pthread_spin_trylock(&spin); }
}

void* r_r(void*) {
	while(true) { pthread_rwlock_tryrdlock(&rwlock); }
}

void* w_r(void*) {
	while(true) { pthread_rwlock_trywrlock(&rwlock); }
}

int main()
{
	pid_t pid = getpid();
	FILE* file = fopen("/home/box/main.pid", "w+");
	if(!file) { perror("fopen"); }
	fprintf(file, "%d\n", pid);
	fclose(file);

	pthread_mutex_lock(&mutex);
	pthread_spin_lock(&spin);
        pthread_rwlock_rdlock(&rwlock);
        pthread_rwlock_wrlock(&rwlock);

	pthread_create(&mutex_thread, NULL, m_r, NULL);
	pthread_create(&mutex_thread, NULL, s_r, NULL);
	pthread_create(&mutex_thread, NULL, r_r, NULL);
	pthread_create(&mutex_thread, NULL, w_r, NULL);
}
