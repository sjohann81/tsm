#define DATA_MEM_SIZE	4096

/* machine instruction set */
enum {	PSH, POP, POPB,					/* stack push / pop */
	AND, OR, XOR, ADD, SUB,				/* logical and arithmetic */
	SHL, SHR, ASR,					/* shift */
	BEQ, BNE, BLT, BGE,				/* branch */
	LDW, STW, LDB, STB,				/* load / store */
	HLT						/* control */
};

/* machine context and data memory structure */
struct vm_s {
	int pc;
	int sp;
	int *stack;
	char *data;
};
