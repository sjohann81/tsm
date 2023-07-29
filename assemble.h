/* machine instruction set */
enum {
	HLT,						/* control */
	PSH, POP,					/* stack */
	DUP, SWAP, OVER,				/* stack */
	PSHSP, POPSP, PSHFP, POPFP,			/* stack */
	AND, OR, XOR, ADD, SUB,				/* logical and arithmetic */
	SHL, SHR, ASR,					/* shift */
	BEQ, BNE, BLT, BGE, BRA, JMP,			/* branch and jump */
	LDW, STW, LDB, STB,				/* load/store */
	IN, INB, OUT, OUTB				/* input/output */
};

/* Instruction name and value */
struct inst_s {
	char name[16];
	int val;
};

/* Instruction opcode table */
struct inst_s opcodes[] = {
	{"HLT", HLT},
	{"PSH", PSH}, {"POP", POP},
	{"DUP", DUP}, {"SWAP", SWAP}, {"OVER", OVER},
	{"PSHSP", PSHSP}, {"POPSP", POPSP}, {"PSHFP", PSHFP}, {"POPFP", POPFP},
	{"AND", AND}, {"OR", OR}, {"XOR", XOR}, {"ADD", ADD}, {"SUB", SUB},
	{"SHL", SHL}, {"SHR", SHR}, {"ASR", ASR},
	{"BEQ", BEQ}, {"BNE", BNE}, {"BLT", BLT}, {"BGE", BGE}, {"BRA", BRA}, {"JMP", JMP},
	{"LDW", LDW}, {"STW", STW}, {"LDB", LDB}, {"STB", STB},
	{"IN", IN}, {"INB", INB}, {"OUT", OUT}, {"OUTB", OUTB}
};

size_t op_size = sizeof(opcodes) / sizeof(struct inst_s);
