#include <string.h>

#include "list.h"

#define DEFAULT_SIZE								 8
#define VALUE_OR_DEFAULT(value, default_value)		 value ? value : default_value

/*
 * =======================
 * |    PRIVATE STUFF    |
 * =======================
 */

typedef struct
{
	void *value;

	// Indicates that this memory is allocated to this struct, more precisely when this field is 0 (after using memset)
	char *this_memory_is_allocated_by_other;
} list_object_t;

list_t *current_list = NULL;
list_object_t *objects = NULL;

const size_t get_count()
{
	list_object_t *objs = objects;

	size_t counter = 0;

	while (objs->this_memory_is_allocated_by_other == 0)
	{
		++objs;
		++counter;
	}

	return counter;
}

/*
 * ======================
 * |	PUBLIC STUFF    |
 * ======================
 */

void add(const void *value)
{
	list_object_t *objs = objects;

	while (objs->this_memory_is_allocated_by_other == 0)
	{
		if (!objs->value)
		{
			objs->value = value;

			break;
		}

		++objs;
	}
}

void remove(const void *value)
{
	size_t counter = get_count() - 1; // You can only remove one element at a time
	list_object_t *new_objs = calloc(counter, sizeof(list_object_t));

	for (size_t i = 0; i < counter + 1; i++)
	{
		list_object_t *old_obj = objects + i;
		list_object_t *new_obj = new_objs + i;

		if (new_obj->this_memory_is_allocated_by_other)
		{
			return;
		}

		if (old_obj->value != value)
		{
			new_obj->value = old_obj->value;
		}
		else
		{
			new_obj->value = (objects + i + 1)->value;
			++i;
		}
	}
}

list_t *new_list()
{	 
	list_t *list = calloc(DEFAULT_SIZE, sizeof(list_t));
	list->add    = &add;
	list->remove = &remove;

	objects = calloc(DEFAULT_SIZE, sizeof(list_object_t));

	return current_list = list;
}