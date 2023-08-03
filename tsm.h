#define MEM_SIZE	(1024 * 1024)

/* machine instruction set */
enum {
	HLT,						/* control */
	PSH, POP,		 			/* stack */
	DUP, SWAP, OVER,				/* stack */
	PSHSP, POPSP, PSHFP, POPFP, 			/* stack */
	AND, OR, XOR, ADD, SUB,				/* logical and arithmetic */
	SHL, SHR, ASR,					/* shift */
	BEQ, BNE, BLT, BGE, BRA, JMP,			/* branch / jump */
	LDW, STW, LDB, STB,				/* load/store */
	IN, INB, OUT, OUTB				/* input/output */
};

/* machine context and data memory structure */
struct vm_s {
	int pc;
	int sp;
	int fp;
	int *stack;
	char *data;
	int *code;
};
