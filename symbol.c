#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"


struct symbol_s *sym_append(struct symbol_s *lst, char *name, int addr)
{
	struct symbol_s *t1;

	if (lst->next == 0) {
		t1 = malloc(sizeof(struct symbol_s));
		
		if (t1) {
			strcpy(t1->name, name);
			t1->addr = addr;
			t1->next = 0;
			lst->next = t1;
			
			return t1;
		} else
			return 0;
	}
	
	return sym_append(lst->next, name, addr);
}


int sym_count(struct symbol_s *lst)
{
	if (lst->next == 0)
		return 0;
	
	return sym_count(lst->next) + 1;
}


struct symbol_s *sym_insert(struct symbol_s *lst, char *name, int addr, unsigned int pos)
{
	struct symbol_s *t1;

	if (pos == -1) {
		t1 = malloc(sizeof(struct symbol_s));
		
		if (t1) {
			strcpy(t1->name, name);
			t1->addr = addr;
			t1->next = lst;
			lst = t1;
		} else
			return 0;
	} else
		lst->next = sym_insert(lst->next, name, addr, pos - 1);
	
	return lst;
}


struct symbol_s *sym_remove(struct symbol_s *lst, unsigned int pos)
{
	struct symbol_s *t1;	

	if (pos == -1) {
		t1 = lst->next;
		free(lst);
		lst = t1;
	} else
		lst->next = sym_remove(lst->next, pos - 1);
	
	return lst;
}


struct symbol_s *sym_find(struct symbol_s *lst, char *name)
{
	if (strcmp(lst->name, name) == 0)
		return lst;

	if (lst->next == 0)
		return 0;
		
	return sym_find(lst->next, name);
}
