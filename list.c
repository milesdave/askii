#include <stdlib.h>
#include "list.h"

node_t* list_init(sprite_t *s)
{
	node_t *n;
	n = (node_t*)malloc(sizeof(node_t));
	n->data = *s;
	n->next = NULL;
	return n;
}

void list_free(node_t *h)
{
	node_t *current = h;
	while(current != NULL)
	{
		node_t *tmp = current;
		current = current->next;
		free(tmp);
	}
}

void list_loop(node_t *h, action a)
{
	node_t *current = h;
	while(current != NULL)
	{
		a(&current->data);
		current = current->next;
	}
}

int list_push(node_t *h, sprite_t *s)
{
	int size = 0;
	node_t *current = h;

	while(current->next != NULL)
	{
		current = current->next;
		size++;
	}

	node_t *new = (node_t*)malloc(sizeof(node_t));
	new->data = *s;
	new->next = NULL;
	current->next = new;

	return size++;
}
