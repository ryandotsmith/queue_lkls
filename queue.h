// queue.h is an implementation of a threadsafe, lock-free queue.
// The algorithms are based on the research of Maged M. Michael and
// Michael L. Scott. For details, see their article:
// Simple, Fast, and Practical Non-Blocking and Blocking Concurrent Queue Algorithms

#ifndef _QUEUE_H_
#define _QUEUE_H
#include "list.c"

typedef struct queue {
	list *list;
	double length;
} queue;

void queueEnqueue(list* ,void*);
int queueDequeue(list*, void*);

#endif
