#include <stdlib.h>
#include "list.h"

node *
createNode(void *data)
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
	list *l= malloc(sizeof(list));
	l->head = NULL;
	l->tail = NULL;
	l->length = 0;
	return l;
}

void
listAddHead(list *l, void *data)
{
	node *newNode = createNode(data);

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
	node *newNode = createNode(data);

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
