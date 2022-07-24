# list.c
An implementation of a list in C, based on C#'s List&lt;T>.

## Compiling
- In Windows
    - Install Visual Studio (IDE) with "Development with C++" workload, open the project and compile using `Ctrl` + `Shift` + `B`.

## Documentation
- Create -> Create the `list_t`.
```C
 const list_t list = new_list();
```

- Add -> Adds an object to the end of the `list_t`.
```C
list.add(const void* value);
```

- Remove
	- Remove at -> Removes the element at the specified index of the `list_t`.
	```C
    list.remove_at(const size_t index);
	```

	- Remove element -> Removes the first occurrence of a specific object from the `list_t`.
	```C
	list.remove_element(const void *value);
	```

- Clear -> Removes all elements from the `list_t`.
```C
list.clear();
```

- Print -> Shows all elements in the `list_t` in the console.
```C
list.print();
```

- Reverse -> Reverses the order of the elements in the entire `list_t`.
```C
list.reverse();
```

- Exists -> Determines whether the `list_t` contains an element.
```C
const bool exists = list.exists(const void *value);
```

- Index Of -> Searches for the specified object and returns the zero-based index of the first occurrence within the entire `list_t`.
```C
const size_t index = list.index_of(const void *value);
```

- Count -> Gets the number of elements contained in the `list_t`.
```C
const size_t count = list.count();
```

- Element At -> Returns the element at a specified index in a sequence.
```C
const void* elem = list.element_at(const size_t index);
```
<br>

Extra note: This implementation is not thread safe, I plan to include it in the near future.