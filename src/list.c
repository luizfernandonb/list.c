#include <string.h>

#include "list.h"

#define DEFAULT_SIZE								 4
#define VALUE_OR_DEFAULT(value, default_value)		 value ? value : default_value
#define SIZE_OF_POINTER_TO_POINTER(array, type_size) (sizeof(array) * type_size)

// Private methods

typedef struct list_node_t
{
	size_t			   value_size;
	void			   *value;

	struct list_node_t *next;
} list_node_t;

size_t      _count           = 0;
size_t      _count_allocated = 0;
list_t      *_current_list   = NULL;
list_node_t *current_node    = NULL;

void set_node_default_value_size(list_node_t *nodes, size_t value_size, size_t node_count)
{
	for (size_t counter = 0; counter < node_count; counter++)
	{
		(nodes + counter)->value_size = value_size;
	}
}

void set_node_next_node(list_node_t *nodes, size_t node_count)
{
	for (size_t counter = 0; counter < node_count; counter++)
	{
		if (counter == 0)
		{
			continue;
		}

		list_node_t *actual_node = nodes + counter;
		list_node_t *previous_node = actual_node - 1;

		previous_node->next = actual_node;
	}
}

// Public methods

void add(const void *value)
{
	if (_count == 0) // First value
	{
		current_node->value = value;
	}
	else
	{
		if (_count < _count_allocated) // Free space
		{
			(current_node + _count)->value = value;
		}
		else // Not free space, realloc list
		{
			_count_allocated = _count_allocated + 4; // Why 4? IDK
			list_node_t *new_nodes = realloc(current_node, sizeof(list_node_t) * _count_allocated);
			set_node_default_value_size(new_nodes, current_node->value_size, _count_allocated);
			set_node_next_node(new_nodes, _count_allocated);

			current_node = new_nodes;
		}
	}

	++_count;
}

void remove(const void *value)
{
	for (size_t counter = 0; counter < _count_allocated; ++counter)
	{
		list_node_t *actual_node = current_node + counter;
		if (actual_node->value == value)
		{
			if (counter == 0)
			{
				// TODO
			}
			else
			{
				list_node_t *previous_node = actual_node - 1;
				list_node_t *next_node     = actual_node + 1;

				previous_node->next = next_node;

				free(actual_node);
			}
		}
	}

	--_count;
}

list_t *new_list(size_t size)
{	 
	_current_list = malloc(sizeof(list_t));
	if (_current_list)
	{
		_current_list->add	 = &add;
		_current_list->remove = &remove;

		_count = 0;
	}

	current_node = malloc(sizeof(list_node_t) * DEFAULT_SIZE);
	set_node_default_value_size(current_node, size, DEFAULT_SIZE);
	set_node_next_node(current_node, DEFAULT_SIZE);
	_count_allocated = DEFAULT_SIZE;

	return _current_list;
}