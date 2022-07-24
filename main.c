#include <stdio.h>

#include "list.h"

int main()
{
	// Ignore C4022, C4311 warnings in MSVC

	const list_t l = new_list();
	
	l.add(10);
	l.add(20);
	l.add(30);
	l.add(40);
	l.add(50);
	
	//l.print();

	//l.remove_at(2);

	//l.print();

	//l.remove_at(0);

	l.print();

	l.reverse();

	l.print();

	//l.remove_element(50);
	
	//l.print();

	//l.clear();

	//l.print();

	int elem = (int)l.element_at(3);

	printf("%d\n", elem);

	system("pause");
}