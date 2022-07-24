#include <stdio.h>
#include <string.h>

#include "list.h"
									    
#define FOREACH_LIST_OBJECT(counter_name, list_objects) for (list_object_t *counter_name = list_objects; counter_name->this_memory_space_is_allocated_by_other == NULL; ++counter_name)

#if defined(__GNUC__) || defined(__clang__)
#define INLINE __attribute__((always_inline))
#else
#define INLINE __forceinline
#endif

// PRIVATE STUFF

typedef struct
{
	void *value;

	// Indicates that this memory is allocated to this struct, more precisely when this field is 0
	char *this_memory_space_is_allocated_by_other;
} list_object_t;

list_t        current_list = { 0 };
list_object_t *objects     = NULL;

INLINE void throw_error(const char *message)
{
	printf(message);

	while (true);
}

INLINE void throw_if_null(const void *object, const char* message)
{
	if (!object)
	{
		throw_error(message);
	}
}

INLINE void check_list_in_memory()
{
	throw_if_null(current_list.add, "Call the new_list method to create the list_t in memory.");
	throw_if_null(objects, "Call the new_list method to create the list_t in memory.");
}

INLINE void memcpy_list_object(const list_object_t *destination, const list_object_t *source)
{
	memcpy((const void*)destination, (const void*)source, sizeof(list_object_t));
}

INLINE void check_index_out_of_limit(const size_t index)
{
	if (index > current_list.count())
	{
		throw_error("This index is outside the limits of the list_t.");
	}
}

INLINE list_object_t *malloc_list_object(const size_t count)
{
	list_object_t *object = calloc(count, sizeof(*object));
	throw_if_null(object, "Not enough memory to allocate list_t objects.");

	return object;
}

INLINE size_t get_count_of_objects_to_allocate_in_add()
{
	// One more element is always added
	return current_list.count() + 1;
}

INLINE size_t get_count_of_objects_to_allocate_in_remove()
{
	// One more element is always removed
	return current_list.count() - 1;
}

size_t get_count(void)
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


// PUBLIC STUFF

void add(const void *value)
{
	check_list_in_memory();

	throw_if_null(value, "Cannot add \"NULL\" to list_t.");

	list_object_t *new_objects = malloc_list_object(get_count_of_objects_to_allocate_in_add());

	memcpy(new_objects, objects, sizeof(*new_objects) * get_count());

	(new_objects + (
		/*
		 * Pointers always start with the index 0, so if we decrease the last_index, we get the last empty object this pointer
		 * know it's confusing, but this was the only way I found it viable
		 */
		get_count()))->value = value;

	free(objects);

	objects = new_objects;
}

void remove_at(const size_t index)
{
	check_list_in_memory();
	check_index_out_of_limit(index);
	
	list_object_t *local_objects = objects;

	list_object_t *new_objects = malloc_list_object(get_count_of_objects_to_allocate_in_remove());

	for (size_t i = 0; i < get_count(); i++)
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

void remove_element(const void *value)
{
	check_list_in_memory();

	throw_if_null(value, "Cannot remove \"NULL\" in list_t.");

	FOREACH_LIST_OBJECT(local_objects, objects)
	{
		if (local_objects->value == value)
		{
			remove_at(local_objects - objects); // Difference = index
		}
	}

	throw_error("This value does not exist in the list_t.");
}

INLINE void clear(void)
{
	free(objects);
}

void print(void)
{
	check_list_in_memory();

	size_t counter = 0;

	FOREACH_LIST_OBJECT(local_objects, objects)
	{
		printf("%zu = %p\n", counter, local_objects->value);

		++counter;
	}

	printf("Count: %zu elements\n\n", counter);
}

void reverse(void)
{
	check_list_in_memory();

	list_object_t *last_object = objects + get_count() - 1;

	list_object_t *new_objects = malloc_list_object(get_count());

	size_t counter = 0;

	for (list_object_t *new_object = new_objects; new_object->this_memory_space_is_allocated_by_other == NULL; ++new_object)
	{
		*(new_objects + counter) = *(last_object - counter);

		++counter;
	}

	free(objects);

	objects = new_objects;
}

const bool exists(const void *value)
{
	check_list_in_memory();

	throw_if_null(value, "Cannot check \"NULL\" in list_t.");

	FOREACH_LIST_OBJECT(local_objects, objects)
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
	check_list_in_memory();

	throw_if_null(value, "Cannot check \"NULL\" in list_t.");

	FOREACH_LIST_OBJECT(local_objects, objects)
	{
		if (local_objects->value == value)
		{
			return local_objects - objects;
		}
	}

	return -1;
}

INLINE const size_t count(void)
{
	check_list_in_memory();

	return get_count();
}

const void *element_at(const size_t index)
{
	check_list_in_memory();
	check_index_out_of_limit(index);

	size_t counter = 0;

	FOREACH_LIST_OBJECT(local_objects, objects)
	{
		if (counter == index)
		{
			return local_objects->value;
		}

		++counter;
	}

	return NULL;
}

const list_t new_list(void)
{	 
	list_t list =
	{
		.add            = add,
		.remove_at      = remove_at,
		.remove_element = remove_element,
		.clear          = clear,
		.print          = print,
		.reverse		= reverse,
		.exists         = exists,
		.index_of       = index_of,
		.count			= count,
		.element_at     = element_at
	};
	
	objects = malloc_list_object(0);

	return current_list = list;
}