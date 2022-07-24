#include "list.h"

list_t list;

int main()
{
	list_t l = new_list();
	l.add((void*)10);
	l.print();
}
