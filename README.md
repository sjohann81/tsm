# Tiny Stack Machine

## What is this?

This is a quick implementation of a stack based cpu virtual machine. In this virtual machine two memory regions are defined: the program memory, used to store opcodes and immediate values and the data memory, used to store initialized data, variables and the stack. Implemented opcodes in this machine are divided in 6 classes:

- Stack: PSH (push value to stack), POP (pop value from stack), POPB (pop byte from stack)
- Logical and arithmetic: AND (logical and), OR (logical or), XOR (logical exclusive or), ADD (arithmetic add), SUB (arithmetic subtract)
- Shift: SHL (logical shift left), SHR (logical shift right), ASR (arithmetic shift right)
- Branch: BEQ (branch if equal), BNE (branch if not equal), BLT (branch if less than), BGE (branch if greater or equal)
- Load and store: LDW (load word), STW (store word), LDB (load byte), STB (store byte)
- Control: HLT (halt execution)
