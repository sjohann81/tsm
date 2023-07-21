struct symbol_s {
	struct symbol_s *next;
	char name[16];
	int addr;
};

struct symbol_s *sym_append(struct symbol_s *lst, char *name, int addr);
int sym_count(struct symbol_s *lst);
struct symbol_s *sym_insert(struct symbol_s *lst, char *name, int addr, unsigned int pos);
struct symbol_s *sym_remove(struct symbol_s *lst, unsigned int pos);
struct symbol_s *sym_find(struct symbol_s *lst, char *name);
