/* machine instruction set */
enum {
	HLT,						/* control */
	PSH, POP, POPB,	DUP,				/* stack push / pop */
	AND, OR, XOR, ADD, SUB,				/* logical and arithmetic */
	SHL, SHR, ASR,					/* shift */
	BEQ, BNE, BLT, BGE, BRA,			/* branch */
	LDW, STW, LDB, STB				/* load / store */
};

/* Instruction name and value */
struct inst_s {
	char name[16];
	int val;
};

/* Instruction opcode table */
struct inst_s opcodes[] = {
	{"HLT", HLT},
	{"PSH", PSH}, {"POP", POP}, {"POPB", POPB}, {"DUP", DUP},
	{"AND", AND}, {"OR", OR}, {"XOR", XOR},
	{"ADD", ADD}, {"SUB", SUB},
	{"SHL", SHL}, {"SHR", SHR}, {"ASR", ASR},
	{"BEQ", BEQ}, {"BNE", BNE}, {"BLT", BLT}, {"BGE", BGE}, {"BRA", BRA},
	{"LDW", LDW}, {"STW", STW}, {"LDB", LDB}, {"STB", STB}
};

size_t op_size = sizeof(opcodes) / sizeof(struct inst_s);
