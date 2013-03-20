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
	node *newNode = nodeCreate(data);

	if(l->length == 0) {
		l->head = l->tail = newNode;
	} else {
		newNode->prev = l->tail;
		l->tail->next = newNode;
		l->tail = newNode;
	}
	l->length++;
	return;
}

void
listDelete(list *l, node *n)
{
	if(n->prev) {
		n->prev->next = n->next;
	} else {
		l->head = n->next;
	}
	if(n->next) {
		n->next->prev = n->prev;
	} else {
		l->tail = n->prev;
	}
	free(n);
	l->length--;
	return;
}
