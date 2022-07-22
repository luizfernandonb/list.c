#include <stdio.h>
#include <string.h>

#include "list.h"

#define VALUE_OR_DEFAULT(value, default_value)  value ? value : default_value
#define NO_MEMORY_CHECK(allocated_object)       if (!allocated_object)              \
										        {                                   \
                                                    printf("No memory available."); \
                                                                                    \
                                                    system("pause");                \
										        }                                   \
											    
#define THROW_ERROR(error)                      printf(error);                      \
                                                                                    \
                                                system("pause");                    \
											    
#define FOREACH_LIST_OBJECT(counter_name)       for (list_object_t *counter_name = objects; counter_name->this_memory_space_is_allocated_by_other == NULL; counter_name++)

/*
 * =======================
 * |    PRIVATE STUFF    |
 * =======================
 */

typedef struct
{
	void *value;

	// Indicates that this memory is allocated to this struct, more precisely when this field is 0
	char *this_memory_space_is_allocated_by_other;
} list_object_t;

list_t        current_list = { 0 };
list_object_t *objects     = NULL;

size_t get_index_counter()
{
	list_object_t *objs = objects;

	size_t counter = 0;

	while (objs->this_memory_space_is_allocated_by_other == NULL)
	{
		++objs;
		++counter;
	}

	return counter;
}

size_t get_count_of_objects_to_allocate_in_add()
{
	return get_index_counter() + 1;
}

size_t get_count_of_objects_to_allocate_in_remove()
{
	return get_index_counter() - 1;
}

list_object_t *malloc_list_object(const size_t count)
{
	list_object_t *object = calloc(count, sizeof(list_object_t));
	NO_MEMORY_CHECK(object);

	return object;
}

void memcpy_list_object(const void* destination, const void *source)
{
	memcpy(destination, source, sizeof(list_object_t));
}

/*
 * ======================
 * |	PUBLIC STUFF    |
 * ======================
 */

void add(const void *value)
{
	if (!objects) // First add()
	{
		list_object_t *object = malloc_list_object(1);
		object->value = value;

		objects = object;

		return;
	}

	list_object_t *new_objects = malloc_list_object(get_count_of_objects_to_allocate_in_add());

	memcpy(new_objects, objects, sizeof(list_object_t) * get_index_counter());

	(new_objects + (
		/*
		 * Pointers always start with the index 0, so if we decrease the last_index, we get the last empty object this pointer
		 * know it's confusing, but this was the only way I found it viable
		 */
		get_index_counter()))->value = value;

	free(objects);

	objects = new_objects;
}

void remove_at(const size_t index)
{
	if (objects)
	{
		list_object_t *local_objects = objects;

		list_object_t *new_objects = malloc_list_object(get_count_of_objects_to_allocate_in_remove());

		for (size_t i = 0; i < get_index_counter(); i++)
		{
			if (i >= index)
			{
				memcpy_list_object(new_objects + i, local_objects + i + 1);

				continue;
			}

			memcpy_list_object(new_objects + i, local_objects + i);
		}

		free(objects);

		objects = new_objects;
	}
	else
	{
		THROW_ERROR("Cannot remove something from a list that has no elements ;)");
	}
}

void remove_element(const void *value)
{
	FOREACH_LIST_OBJECT(local_objects)
	{
		if (local_objects->value == value)
		{
			remove_at(local_objects - objects); // Difference = index
		}
	}
}

void print()
{
	size_t i = 0;
	for (; i < get_index_counter(); i++)
	{
		printf("The value in index \"%zu\" is: %p\n", i, (objects + i)->value);
	}

	printf("Count: %zu elements\n\n", i);
}

void clear()
{
	free(objects);
}

const bool exists(const void *value)
{
	FOREACH_LIST_OBJECT(local_objects)
	{
		if (local_objects->value == value)
		{
			return true;
		}
	}

	return false;
}

const size_t index_of(const void *value)
{
	FOREACH_LIST_OBJECT(local_objects)
	{
		if (local_objects->value == value)
		{
			return local_objects - objects;
		}
	}
}

const size_t count()
{
	return get_index_counter() + 1;
}

const void *element_at(const size_t index)
{
	size_t counter = 0;

	FOREACH_LIST_OBJECT(local_objects)
	{
		if (counter == index)
		{
			return local_objects->value;
		}

		++counter;
	}

	return NULL;
}

const list_t new_list()
{	 
	list_t list =
	{
		.add            = add,
		.remove_at      = remove_at,
		.remove_element = remove_element,
		.print          = print,
		.clear          = clear,
		.exists         = exists,
		.index_of       = index_of,
		//.reverse		= reverse,
		.count			= count,
		.element_at     = element_at
	};
	
	return current_list = list;
}