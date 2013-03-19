#ifndef _LIST_H_
#define _LIST_H

typedef struct node {
	struct node *next;
	struct node *prev;
	void *data;
} node;

typedef struct list {
	node *head;
	node *tail;
	long length;
} list;

#endif
