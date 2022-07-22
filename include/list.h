#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
	void	     (*add)		      (const void *value);
	void	     (*remove_element)(const void *value);
	void	     (*remove_at)     (const size_t index);
	void         (*print)         ();
	void	     (*add_range)     (const void *arr);
	/*void	     (*clear)         ();
	const bool   (*exists)        (const void *value);
	const size_t (*index_of)      (const void *value);
	const list_t (*reverse)       ();
	const void * (*to_array)      ();
	const size_t (*count)         ();*/
} list_t;

const list_t new_list();
