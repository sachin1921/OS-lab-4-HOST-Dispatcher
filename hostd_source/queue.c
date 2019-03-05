/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Define your FIFO queue functions here, these will most likely be the
// push and pop functions that you declared in your header file

node_t *push(node_t *tail, proc process);
{
	if (tail == NULL){	//if tail is empty, push process into queue
		tail = malloc(sizeof(node_t));
		tail->p = process;
		tail->next NULL;
	} else if (tail != NULL){	//if tail is not empty push a node at the end of the list
		node_t *cur_head = tail;
		while (cur_head->next != NULL)
			cur_head = current->next;
		cur_head->next = malloc(sizeof(node_t));
		cur_head->next->p = process;
		cur_head->next->next = NULL;
	}
}

// Pop process from queue
node_t *pop(node_t *tail);
{
	node_t *temporary = tail->next;
	node_t ret = tail;
	
	free(tail);
	
	tail = temporary;
	
	return ret;
}
