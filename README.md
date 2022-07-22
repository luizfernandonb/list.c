# list.c
An implementation of a list in C, based on C#'s List&lt;T>.

Documentation:
- Create -> Create the list
```C
 const list_t list = new_list();
```

- Add -> Add an element to the list
```C
list.add(const void* value);
```

- Remove
	- Remove element -> Remove an element
	```C
	list.remove_element(const void *value);
	```

	- Remove at -> Remove an element from the list from the index
	```C
    list.remove_at(const size_t index);
	```

- Print -> Shows in the console all the elements of the list (if it is in a console)
```C
list.print();
```

- Clear -> Clear the list
```C
list.clear();
```

- Exists -> Checks if an element exists
```C
const bool exists = list.exists();
```

- Index Of -> Returns the index from the element
```C
const size_t index = list.index_of(const void *value);
```

- Count -> Returns the number of elements in the list
```C
const size_t count = list.count();
```

- Element At -> Returns the element of a list from index
```C
const void* elem = list.element_at(const size_t index);
```
<br>

Extra note: This implementation is not thread safe, I plan to include it in the near future.