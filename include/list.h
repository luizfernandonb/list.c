#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>
#include <stdbool.h>

typedef struct list_t
{
	// Adds an object to the end of the list_t.
	void	     (*add)		      (const void *value);

	// Removes the element at the specified index of the list_t.
	void	     (*remove_at)     (const size_t index);
	
	// Removes the first occurrence of a specific object from the list_t.
	void	     (*remove_element)(const void *value);
	
	// Removes all elements from the list_t.
	void	     (*clear)         (void);

	// Shows all elements in the list_t in the console.
	void         (*print)         (void);

	// Reverses the order of the elements in the entire list_t.
	void		 (*reverse)       (void);

	// Determines whether the list_t contains an element.
	const bool   (*exists)        (const void *value);

	// Searches for the specified object and returns the zero-based index of the first occurrence within the entire list_t.
	const size_t (*index_of)      (const void *value);

	// Gets the number of elements contained in the list_t.
	const size_t (*count)         (void);

	// Returns the element at a specified index in a sequence.
	const void*	 (*element_at)	  (const size_t index);
} list_t;

// Initializes a new instance of the list_t struct that is empty.
const struct list_t new_list(void);
#endif