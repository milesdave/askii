#include <stdlib.h>
#include "list.h"

void list_free(node_t **h)
{
	node_t *current = *h;
	while(current != NULL)
	{
		node_t *tmp = current;
		current = current->next;
		free(tmp);
	}
}

void list_loop(node_t **h, action a)
{
	node_t *current = *h;
	while(current != NULL)
	{
		a(&current->data);
		current = current->next;
	}
}

int list_add(node_t **h, sprite_t *s)
{
	// empty list
	if(*h == NULL)
	{
		*h = (node_t*)malloc(sizeof(node_t));
		(*h)->data = *s;
		(*h)->next = NULL;
		return 1;
	}

	int c = 1;
	node_t *current = *h;

	// loop to end and count
	while(current->next != NULL)
	{
		current = current->next;
		c++;
	}

	// add new node at end
	node_t *new = (node_t*)malloc(sizeof(node_t));
	new->data = *s;
	new->next = NULL;
	current->next = new;

	return ++c;
}

void list_remove(node_t **h, const int i)
{
	if(*h == NULL) return;

	node_t *current = *h;

	// remove head
	if(i == 0)
	{
		if(current->next != NULL)	// next node exists
			*h = current->next;
		else						// no next node
			*h = NULL;

		free(current);
		return;
	}

	int c = 0;
	node_t *last;

	// loop to node to delete
	while(current != NULL)
	{
		// found node to delete
		if(c == i)
		{
			if(current->next != NULL)		// next node exists
				last->next = current->next;
			else							// no next node
				last->next = NULL;

			free(current);
			return;
		}

		last = current;
		current = current->next;
		c++;
	}
}

sprite_t* list_get(node_t **h, const int i)
{
	// head passed in is 0
	if(i == 0) return &(*h)->data;

	int c = 0;
	node_t *current = *h;

	while(current != NULL)
	{
		if(c == i)
			return &current->data;

		current = current->next;
		c++;
	}

	return NULL;
}
