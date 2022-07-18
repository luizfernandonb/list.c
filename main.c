#include <stdio.h>

#include "list.h"

int main()
{
	list_t *l = new_list(sizeof(int));

	l->add(10);
	l->add(20);
	l->add(30);
	l->add(40);
	l->add(50);
	l->add(60);
	l->add(70);
	l->add(80);
	l->add(90);
	l->add(100);

	l->remove(60);

}