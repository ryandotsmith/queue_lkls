#ifndef _LIST_H_
#define _LIST_H
#include <pthread.h>

typedef struct node {
	struct node *next;
	struct node *prev;
	void *data;
} node;

typedef struct list {
	node *head;
	node *tail;
	long length;
	pthread_mutex_t lock;
} list;

#endif
