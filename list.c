#include <stdlib.h>
#include "list.h"

node *
nodeCreate(void *data)
{
	node *newNode = malloc(sizeof(node));
	newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

list *
listCreate(void)
{
	node *blank = nodeCreate(NULL);
	list *l= malloc(sizeof(list));
	l->head = blank;
	l->tail = blank;
	l->head->next = l->tail;
	l->length = 1;
	return l;
}

void
listAddHead(list *l, void *data)
{
	node *newNode = nodeCreate(data);

	if(l->length == 0) {
		l->head = l->tail = newNode;
	} else {
		newNode->next = l->head;
		l->head->prev = newNode;
		l->head = newNode;
	}
	l->length++;
	return;
}

void
listAddTail(list *l, void *data)
{
	if(pthread_mutex_lock(&l->lock) != 0) {
		printf("Unable to lock mutex.\n");
		return;
	}

	node *newNode = nodeCreate(data);

	if(l->length == 0) {
		l->head = l->tail = newNode;
	} else {
		newNode->prev = l->tail;
		l->tail->next = newNode;
		l->tail = newNode;
	}
	l->length++;
	if(pthread_mutex_unlock(&l->lock) != 0) {
		printf("Unable to unlock mutex.\n");
	}
	return;
}

int
listDeleteFirst(list *l)
{
	if (l->head->next == l->tail) {
		return 1;
	}

	if(pthread_mutex_lock(&l->lock) != 0) {
		printf("Unable to lock mutex.\n");
		return 2;
	}

	node *first = l->head->next;
	l->head->next = first->next;
	free(first);
	l->length--;

	if(pthread_mutex_unlock(&l->lock) != 0) {
		printf("Unable to unlock mutex.\n");
		return 2;
	}
	return 0;
}
