#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include "queue.c"

#define LOCAL_WORKERS 1000
#define NUM_JOBS 10000

void *
produce(void *arg)
{
	list *l = (list *)arg;
	for(int i = 0; i < NUM_JOBS; i++) {
		char buf[32];
		sprintf(buf, "msg.%d", i);
		queueEnqueue(l, strdup(buf));
	}
	return 0;
}

void *
consume(void *arg)
{
	list *l = (list *)arg;
	while(1) {
		char buf[32];
		int success;
		success = queueDequeue(l, &buf);
		if(!success) {
			break;
		}
	}
	return 0;
}

int
main(int argc, char *argv[])
{
	list *l = listCreate();
	pthread_t producers[LOCAL_WORKERS];
	pthread_t consumers[LOCAL_WORKERS];
	for(int i = 0; i < LOCAL_WORKERS; i++) {
		pthread_create(&producers[i], NULL, &produce, l);
		pthread_create(&consumers[i], NULL, &consume, l);
	}
	for(int i = 0; i < LOCAL_WORKERS; i++) {
		pthread_join(producers[i], NULL);
		pthread_join(consumers[i], NULL);
	}
	return 0;
}
