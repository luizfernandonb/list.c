#include <stdio.h>

#include "list.h"

int main()
{
	list_t l = new_list(sizeof(int));

	l.add(10);
	l.add(20);
	l.add(30);
	l.add(40);
	l.add(50);
	
	l.print();

	l.remove_at(2);

	l.print();

	l.remove_at(0);

	l.print();

	l.remove_element(50);
	
	l.print();
}