#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tsm.h"


/* VM implementation 
 * 
 * Machine state is kept in a struct vm_s data structure (program counter,
 * stack pointer and pointers to memory. An instruction is decoded and
 * executed. In this implementation, POP and POPB instructions have popped
 * values (int and char) printed in the terminal. */

int execute(struct vm_s *vm, int instr)
{
	int a, b, val;
	char buf[20];
	
	switch (instr) {
	case HLT:
		printf("\nProgram stop (pc: %08x, fp: %08x, sp: %08x)\n", vm->pc << 2, vm->fp << 2, vm->sp << 2);
		return 0;
	case PSH:
		vm->stack[--vm->sp] = vm->code[++vm->pc];
		break;
	case POP:
		vm->sp++;
		break;
	case DUP:
		vm->stack[vm->sp - 1] = vm->stack[vm->sp];
		vm->sp--;
		break;
	case SWAP:
		val = vm->stack[vm->sp + 1];
		vm->stack[vm->sp + 1] = vm->stack[vm->sp];
		vm->stack[vm->sp] = val;
		break;
	case OVER:
		vm->stack[vm->sp - 1] = vm->stack[vm->sp + 1];
		vm->sp--;
		break;
	case PSHSP:
		vm->sp--;
		vm->stack[vm->sp] = vm->sp << 2;
		break;
	case POPSP:
		vm->sp = vm->stack[vm->sp] >> 2;
		vm->sp++;
		break;
	case PSHFP:
		vm->sp--;
		vm->stack[vm->sp] = vm->fp << 2;
		break;
	case POPFP:
		vm->fp = vm->stack[vm->sp] >> 2;
		vm->sp++;
		break;
	case AND:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		vm->stack[--vm->sp] = a & b;
		break;
	case OR:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		vm->stack[--vm->sp] = a | b;
		break;
	case XOR:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		vm->stack[--vm->sp] = a ^ b;
		break;
	case ADD:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		vm->stack[--vm->sp] = a + b;
		break;
	case SUB:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		vm->stack[--vm->sp] = a - b;
		break;
	case SHL:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		vm->stack[--vm->sp] = a << b;
		break;
	case SHR:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		vm->stack[--vm->sp] = (unsigned int)a >> b;
		break;
	case ASR:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		vm->stack[--vm->sp] = a >> b;
		break;
	case BEQ:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		vm->pc++;
		a == b ? vm->pc = vm->code[vm->pc] >> 2 : vm->pc++;
		return 1;
	case BNE:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		vm->pc++;
		a != b ? vm->pc = vm->code[vm->pc] >> 2 : vm->pc++;
		return 1;
	case BLT:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		vm->pc++;
		a < b ? vm->pc = vm->code[vm->pc] >> 2 : vm->pc++;
		return 1;
	case BGE:
		b = vm->stack[vm->sp++];
		a = vm->stack[vm->sp++];
		vm->pc++;
		a >= b ? vm->pc = vm->code[vm->pc] >> 2: vm->pc++;
		return 1;
	case BRA:
		vm->pc++;
		vm->pc = vm->code[vm->pc] >> 2;
		return 1;
	case JMP:
		vm->pc = vm->stack[vm->sp++] >> 2;
		return 1;
	case LDW:
		vm->stack[vm->sp] = vm->stack[vm->code[vm->sp] >> 2];
		break;
	case STW:
		a = vm->stack[vm->sp++] >> 2;
		vm->stack[a] = vm->stack[vm->sp++];
		break;
	case LDB:
		vm->stack[vm->sp] = vm->data[vm->code[vm->sp]];
		break;
	case STB:
		a = vm->stack[vm->sp++];
		vm->data[a] = vm->stack[vm->sp++] & 0xff;
		break;
	case IN:
		fgets(buf, sizeof(buf) - 2, stdin);
		vm->stack[--vm->sp] = atoi(buf);
		break;
	case INB:
		vm->stack[--vm->sp] = getchar();
		break;
	case OUT:
		val = vm->stack[vm->sp++];
		printf("%d\n", val);
		break;
	case OUTB:
		val = vm->stack[vm->sp++];
		printf("%c", val);
		break;
	default:
		printf("\nHalt (opcode: %08x, pc: %08x, fp: %08x, sp: %08x) - opcode not implemented\n", instr, vm->pc << 2, vm->fp << 2, vm->sp << 2);
		return 0;
	}
	
	vm->pc++;
	
	return 1;
}


int main()
{
	struct vm_s context;
	struct vm_s *vm = &context;
	int val = 0, data, pos, cycles = 0;
	
	vm->pc = 0;
	vm->fp = 0;
	vm->sp = MEM_SIZE / sizeof(int);
	vm->code = malloc(MEM_SIZE);
	vm->data = (char *)vm->code;
	vm->stack = vm->code;
	
	if (!vm->code)
		return -1;
	
	/* initialize data segment with bogus values for the tests */
	memset(vm->data, 0, MEM_SIZE);
	for (pos = 0; val != EOF; pos++) {
		val = fscanf(stdin, "%d\n", &data);
		vm->code[pos] = data;
	}
	
	printf("Running...\n");
	
	/* run! */
	while (execute(vm, vm->code[vm->pc]))
		cycles++;

	free(vm->code);
	
	printf("Cycles: %d\n", cycles);

	return 0;
}
