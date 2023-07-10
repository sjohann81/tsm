#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tsm.h"


/* program memory */
const int program[] = {
	/* push 5 and 6 to stack, add both values (result in the stack), pop the result */
	PSH, 5, PSH, 6, ADD, POP,		
	PSH, 5, PSH, 6, SUB, POP,
	PSH, 123, PSH, 456, SUB, POP,
	
	/* push 'hello' in reverse order to stack then pop each byte */
	PSH, 'o', PSH, 'l', PSH, 'l', PSH, 'e', PSH, 'h', POPB, POPB, POPB, POPB, POPB, 
	PSH, 10, POP,
	
	/* test logical operations */
	PSH, 7, PSH, 3, AND, POP,
	PSH, 14, PSH, 3, OR, POP,
	PSH, 14, PSH, 3, XOR, POP,
	
	/* test shifts */
	PSH, 10, PSH, 1, SHL, POP,
	PSH, 10, PSH, 1, SHR, POP,
	PSH, -10, PSH, 3, SHR, POP,
	PSH, -10, PSH, 3, ASR, POP,
	
	/* test loads and stores, print a message stored in memory */
	LDW, 5, LDW, 6, ADD, POP,
	LDW, 5, LDW, 6, ADD, STW, 7, LDW, 7, POP,
	LDB, 10, LDB, 9, LDB, 8, LDB, 7, LDB, 6, LDB, 5, LDB, 4, LDB, 3, LDB, 2, LDB, 1, LDB, 0,
	POPB, POPB, POPB, POPB, POPB, POPB, POPB, POPB, POPB, POPB,
	
	/* print the message three times, branching to the previous test */
	LDW, 10, PSH, 1, ADD, STW, 10,
	LDW, 10, PSH, 3, BLT, -43,
	
	/* stop the virtual machine */
	HLT,
	
	PSH, 0, PSH, 1, BNE, -18,
	
	HLT
};


/* VM implementation */

int execute(struct vm_s *vm, int instr)
{
	int a, b, val;
	
	switch (instr) {
	case PSH:
		vm->sp--;
		vm->pc++;
		vm->stack[vm->sp] = program[vm->pc];
		break;
	case POP:
		val = vm->stack[vm->sp++];
		printf("%d\n", val);
		break;
	case POPB:
		val = vm->stack[vm->sp++];
		printf("%c", val);
		break;
	case AND:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		val = a & b;
		vm->sp--;
		vm->stack[vm->sp] = val;
		break;
	case OR:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		val = a | b;
		vm->sp--;
		vm->stack[vm->sp] = val;
		break;
	case XOR:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		val = a ^ b;
		vm->sp--;
		vm->stack[vm->sp] = val;
		break;
	case ADD:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		val = a + b;
		vm->sp--;
		vm->stack[vm->sp] = val;
		break;
	case SUB:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		val = a - b;
		vm->sp--;
		vm->stack[vm->sp] = val;
		break;
	case SHL:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		val = a << b;
		vm->sp--;
		vm->stack[vm->sp] = val;
		break;
	case SHR:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		val = (unsigned int)a >> b;
		vm->sp--;
		vm->stack[vm->sp] = val;
		break;
	case ASR:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		val = a >> b;
		vm->sp--;
		vm->stack[vm->sp] = val;
		break;
	case BEQ:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		vm->pc++;
		a == b ? vm->pc += program[vm->pc] : 0;
		break;
	case BNE:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		vm->pc++;
		a != b ? vm->pc += program[vm->pc] : 0;
		break;
	case BLT:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		vm->pc++;
		a < b ? vm->pc += program[vm->pc] : 0;
		break;
	case BGE:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		vm->pc++;
		a >= b ? vm->pc += program[vm->pc] : 0;
		break;
	case LDW:
		vm->sp--;
		vm->pc++;
		vm->stack[vm->sp] = vm->stack[program[vm->pc]];
		break;
	case STW:
		a = vm->stack[vm->sp++];
		vm->pc++;
		vm->stack[program[vm->pc]] = a;
		break;
	case LDB:
		vm->sp--;
		vm->pc++;
		vm->stack[vm->sp] = vm->data[program[vm->pc]];
		break;
	case STB:
		a = vm->stack[vm->sp++];
		vm->pc++;
		vm->data[program[vm->pc]] = a & 0xff;
		break;
	case HLT:
		printf("done\n");
		return 0;
	default:
		printf("opcode not implemented\n");
		return 0;
	}
	
	return 1;
}

int main()
{
	struct vm_s context;
	struct vm_s *vm = &context;
	
	vm->data = malloc(DATA_MEM_SIZE);
	vm->pc = 0;
	vm->sp = DATA_MEM_SIZE / sizeof(int);
	vm->stack = (int *)vm->data;
	
	if (!vm->data)
		return -1;
	
	/* initialize data segment with bogus values for the tests */
	memset(vm->data, 0, DATA_MEM_SIZE);
	vm->stack[5] = 44;
	vm->stack[6] = 55;
	vm->stack[10] = 0;
	strcpy(vm->data, "hey there\n");
	
	/* run! */
	while (execute(vm, program[vm->pc]))
		vm->pc++;

	free(vm->data);

	return 0;
}
