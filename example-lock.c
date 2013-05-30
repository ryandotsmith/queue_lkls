#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include "queue.c"

#define LOCAL_WORKERS 100
#define NUM_JOBS 10000

pthread_mutex_t lock;

void *
produce(void *arg)
{
	list *l = (list *)arg;
	for(int i = 0; i < NUM_JOBS; i++) {
		char buf[32];
		sprintf(buf, "msg.%d", i);
		pthread_mutex_lock(&lock);
		listAddTail(l, strdup(buf));
		pthread_mutex_unlock(&lock);
	}
	return 0;
}

void *
consume(void *arg)
{
	list *l = (list *)arg;
	char buf[32];
	pthread_mutex_lock(&lock);
	//listGetHead(l, &buf);
	listDelete(l, l->head);
	pthread_mutex_unlock(&lock);
	return 0;
}

int
main(int argc, char *argv[])
{
	pthread_mutex_init(&lock, NULL);
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
	pthread_mutex_destroy(&lock);
	return 0;
}
