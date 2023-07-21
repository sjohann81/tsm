#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "assemble.h"
#include "operand.h"
#include "symbol.h"


int opcode_find(struct inst_s *opcodes, int op_size, char *opcode)
{
	struct inst_s *inst;
	
	for (int i = 0; i < op_size; i++) {
		inst = &opcodes[i];
		
		if (strncmp(inst->name, opcode, sizeof(inst->name)) == 0)
			return inst->val;
	}
	
	return -1;
}


/* pass 1
 * 
 * a) skip blank lines and comments
 * b) tokenize and interpret opcodes, data words and labels
 * c) determine addresses for labels and build the symbol lookup list */

int pass1(char *code, int org, struct inst_s *opcodes, int op_size, struct symbol_s *sym_table)
{
	char *line, *line_store, *word, *word_store;
	int pc = org;
	int val, wc, lc = 0, i;
	
	line = strtok_r(code, "\n", &line_store);
	while (line) {
		lc++;
		word = strtok_r(line, " \t", &word_store);
		if (word == 0 || *word == ';') {
			line = strtok_r(0, "\n", &line_store);
			continue;
		}
		wc = 0;
		
		while (word) {
			val = opcode_find(opcodes, op_size, word);
			
			if (is_number(word) || sym_find(sym_table, word)) {
				pc += 4;
			} else {
				if (val >= 0) {
					pc += 4;
				} else {
					if (*word == ';') break;
					
					if (*word == '"') {
						word++;
						while (*word != '"') {
							for (i = 0; i < sizeof(int); i++)
								if (*word != '"')
									word++;
							pc += 4;
						}
						if (i % sizeof(int) == 0)
							pc += 4;
						break;
					}
					
					if (wc == 0) {
						if (word[strlen(word) - 1] != ':') {
							pc += 4;
						} else {
							fprintf(stderr, "%s addr %04x\n", word, pc);
							word = strtok(word, ":");
							sym_append(sym_table, word, pc);
						}
					} else {
						pc += 4;
					}
				}
			}
			
			word = strtok_r(0, " \t", &word_store);
			wc++;
		}
		
		line = strtok_r(0, "\n", &line_store);
	}
	
	return 0;
}


/* pass 2
 * 
 * a) skip blank lines and comments
 * b) tokenize and interpret opcodes, data words and labels
 * c) patch referenced symbols with addresses
 * d) translate assembly program to machine code */

int pass2(char *code, int org, struct inst_s *opcodes, int op_size, struct symbol_s *sym_table)
{
	char *line, *line_store, *word, *word_store;
	int pc = org;
	int val, wc, lc = 0, i;
	struct symbol_s *sptr;
	
	line = strtok_r(code, "\n", &line_store);
	while (line) {
		lc++;
		word = strtok_r(line, " \t", &word_store);
		if (word == 0 || *word == ';') {
			line = strtok_r(0, "\n", &line_store);
			continue;
		}
		wc = 0;
		
		while (word) {
			val = opcode_find(opcodes, op_size, word);
			
			if (is_number(word)) {
				if (wc == 0)
					fprintf(stderr, "%04x\t%d", pc, to_number(word));
				else
					fprintf(stderr, " %d", to_number(word));
				printf("%d\n", to_number(word));
				pc += 4;
			} else {
				if (val >= 0) {
					fprintf(stderr, "%04x\t%s", pc, word);
					printf("%d\n", val);
					pc += 4;
				} else {
					if (*word == ';') break;
					
					if (*word == '"') {
						word[strlen(word)] = ' ';
						fprintf(stderr, "%04x\t%s\n", pc, word);
						word++;
						while (*word != '"') {
							val = 0;
							for (i = 0; i < sizeof(int); i++) {
//								val <<= 8;
								val >>= 8;
								if (*word != '"') {
//									val |= *word & 0xff;
									val |= (*word & 0xff) << ((sizeof(int) - 1) * 8);
									word++;
								}
							}
							printf("%d\n", val);
							pc += 4;
						}
						if (i % sizeof(int) == 0) {
							printf("0\n");
							pc += 4;
						}
						break;
					}
					
					if (wc == 0) {
						sptr = sym_find(sym_table, word);
						if (!sptr) {
							if (word[strlen(word) - 1] != ':') {
								fprintf(stderr, "\nError (line %d) - unknown mnemonic: %s\n", lc, word);
							
								return -1;
							}
							break;
						} else {
							fprintf(stderr, "%04x\t%d", pc, sptr->addr);
							printf("%d\n", sptr->addr);
							pc += 4;
						}
					} else {
						sptr = sym_find(sym_table, word);
						if (!sptr) {
							fprintf(stderr, " %s", word);
							fprintf(stderr, "\nError (line %d) - undefined symbol: %s\n", lc, word);
							
							return -1;
						}
						
						fprintf(stderr, " %d", sptr->addr);
						printf("%d\n", sptr->addr);
						pc += 4;
					}
				}
			}
			
			word = strtok_r(0, " \t", &word_store);
			wc++;
		}
		
		line = strtok_r(0, "\n", &line_store);
		
		if (wc > 0)
			fprintf(stderr, "\n");
	}
	
	return 0;
}


int main(void)
{
	char *p1buf, *p2buf;
	size_t msize = 4096;
	int val, pass = 1;
	struct symbol_s sym_table;
	struct symbol_s *sptr = &sym_table;
	
	sptr->next = 0;
	sptr->name[0] = 0;
	sptr->addr = 0;
	
	p1buf = malloc(msize);
	if (!p1buf)
		return -1;
	
	for (size_t i = 0; ; i++) {
		if (i >= msize) {
			msize *= 2;
			p1buf = realloc(p1buf, msize);	
			if (!p1buf)
				return -1;
		}
		
		p1buf[i] = getchar();
		if (p1buf[i] == EOF) {
			p1buf[i] = 0;
			break;
		}
	}
	
	p2buf = malloc(msize);
	strcpy(p2buf, p1buf);
	
	val = pass1(p1buf, 0, opcodes, op_size, sptr);
	if (val) goto fail;
	fprintf(stderr, "Pass %d ok.\n", pass++);
		
	val = pass2(p2buf, 0, opcodes, op_size, sptr);
	if (val) goto fail;
	fprintf(stderr, "Pass %d ok.\n", pass++);
	
	free(p1buf);
	free(p2buf);
	
	while (sym_count(sptr))
		sym_remove(sptr, 0);
		
	return 0;
fail:
	fprintf(stderr, "Failed on pass %d.\n", pass);
	free(p1buf);
	free(p2buf);

	while (sym_count(sptr))
		sym_remove(sptr, 0);
	
	return -1;
}
