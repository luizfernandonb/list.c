#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef struct list_t
{
	void	            (*add)		     (const void *value);
	void	            (*remove_at)     (const size_t index);
	void	            (*remove_element)(const void *value);
	void                (*print)         ();
	void	            (*clear)         ();
	const bool          (*exists)        (const void *value);
	const size_t        (*index_of)      (const void *value);
	//const struct list_t (*reverse)       ();
	//const struct list_t (*dereverse)     ();
	const size_t        (*count)         ();
} list_t;

const struct list_t new_list();
