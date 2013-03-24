#include <stdlib.h>
#include <stdint.h>
#include "queue.h"

void
queueEnqueue(list *l, void *data)
{
	node *newNode = nodeCreate(data);
	node *tail, *next;
	while(1) {
		tail = l->tail;
		next = tail->next;
		if(tail == l->tail) {
			if(!next) {
				int cas = 0;
				//We can only set tail->next to our new node
				//if we are certain no other thread has already
				//added their node to tail->next.
				cas = __sync_bool_compare_and_swap(&tail->next,
					next, newNode);
				if(cas) {
					//We were able to put our node
					//on the end of the list. Recall
					//last->next was null. Break the loop
					//and attempt to update the tail of
					//the list.
					break;
				}
			} else {
				// The tail was not really the tail as
				// there is a nother node following tail.
				// Let's update tail and try again.
				__sync_bool_compare_and_swap(&l->tail,
					tail, next);
			}
		}
	}
	//If we don't update the list->tail, that is OK because
	//we can be sure that we have not broken the list since
	//we CAS and change to tail->next.
	//This implies that we have a FUZZYFIFO queue. Dequeuers may not
	//be garunteed to dequeue the tail.
	__sync_bool_compare_and_swap(&l->tail, tail, newNode);
}

int
queueDequeue(list *l, void *buf)
{
	node *head, *tail, *next;
	while(1) {
		head = l->head;
		tail = l->tail;
		next = head->next;
		if(head == l->head) {
			if(head == tail) {
				//We initialize our list with a blank node
				//that has next = NULL. When there is nothing
				//but this node, the list is assumed empty.
				if(!next) {
					return 0;
				}
				//The tail pointer is invalid. Since our head
				//pointer knows another valid node, we will set
				//the tail to that node and try again.
				__sync_bool_compare_and_swap(&l->tail,
					tail, next);
			} else {
				//TODO(ryandotsmith):
				// Support multiple data types.
				*(char *)buf = *(char *)next->data;

				//We can only be sure that a dequeue is safe
				//if we can move the head to the next node.
				int cas = 0;
				cas = __sync_bool_compare_and_swap(&l->head,
					head, next);
				if(cas) {
					break;
				}
			}
		}
	}
	free(head);
	return 1;
}
