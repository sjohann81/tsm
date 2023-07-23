# Tiny Stack Machine VM and Assembler

## What is this?

This is a quick implementation of a stack based cpu virtual machine and a simple toolchain, composed by an assembler. In this virtual machine one memory region (address space) is shared between the program, data and the stack. Implemented opcodes in this machine are divided in 6 classes:

- Control: HLT (halt execution)
- Stack: PSH (push value to stack), POP (pop value from stack), DUP (duplicate value on stack), SWAP (swap two top values on stack), OVER (push second top value to top of stack)
- Logical and arithmetic: AND (logical and), OR (logical or), XOR (logical exclusive or), ADD (arithmetic add), SUB (arithmetic subtract)
- Shift: SHL (logical shift left), SHR (logical shift right), ASR (arithmetic shift right)
- Branch: BEQ (branch if equal), BNE (branch if not equal), BLT (branch if less than), BGE (branch if greater or equal), BRA (branch always), JMP (jump unconditionally)
- Load and store: LDW (load word), STW (store word), LDB (load byte), STB (store byte)
- Input and output: IN (read stdin integer and push to stack), INB (read stdin char and push to stack), OUT (pop integer from stack and write to stdout), OUTB (pop char from stack and write to stdout)

Programs are loaded directly from stdin. Machine code generated from the assembler (opcodes and data) is composed by integers, represented as strings. Each word is placed in a single line of text.

## Instruction set

(TODO)

## Assembler

(TODO)

## Examples / Usage

To run the examples, both the VM and assembler have to be compiled first. To to this, just type *make* in the project directory and two binaries (*tsm* and *assemble*) will be generated. The assembler and VM read and write data to and from stdin/stdout, so the usual way to run an example is:

```
$ ./assemble < examples/02-hello.s > objects/02-hello.tsm
loop: addr 0000
end: addr 0054
m_ptr: addr 0058
text: addr 005c
Pass 1 ok.
0000	PSH 88
0008	LDW
000c	LDB
0010	DUP
0014	POPB
0018	PSH 0
0020	BEQ 84
0028	PSH 88
0030	LDW
0034	PSH 1
003c	ADD
0040	PSH 88
0048	STW
004c	BRA 0
0054	HLT
0058	92
005c	"hello world!"
Pass 2 ok.

$ ./tsm < objects/02-hello.tsm 
Running...
hello world!
Program stop (pc: 00000054, sp: 00001000)
Cycles: 175
```

This can be done in just one command, piping the output from the assembler directly to the VM input:

```
$ ./assemble < examples/01-add.s | ./tsm
```
