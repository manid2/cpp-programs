// Online C compiler to run C program online
#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void *thread_func(void *args)
{
	char *thname = (char *)args;
	printf("Thread func tid=%d, name=%s\n", gettid(), thname);
	sleep(10);
}

int main(int, char **)
{
	// Write C code here
	printf("This process id=%d\n", getpid());
	for (int i = 0; i < 5; i++) {
		pthread_t thid;
		char thname[20] = {0};
		snprintf(thname, sizeof(thname), "worker %d", i);
		pthread_create(&thid, NULL, thread_func, thname);
		pthread_setname_np(thid, thname);
		sleep(5);
	}
	return 0;
}
