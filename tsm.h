#define MEM_SIZE	4096

/* machine instruction set */
enum {
	HLT,						/* control */
	PSH, POP, POPB, DUP,				/* stack push / pop */
	AND, OR, XOR, ADD, SUB,				/* logical and arithmetic */
	SHL, SHR, ASR,					/* shift */
	BEQ, BNE, BLT, BGE, BRA,			/* branch */
	LDW, STW, LDB, STB				/* load / store */
};

/* machine context and data memory structure */
struct vm_s {
	int pc;
	int sp;
	int *stack;
	char *data;
	int *code;
};
