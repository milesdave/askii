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

void list_remove(node_t **h, int i)
{
	// TODO
}

sprite_t* list_get(node_t **h, int i)
{
	// head passed in is 0
	if(i == 0)
		return &(*h)->data;

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
