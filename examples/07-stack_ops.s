main:
	PSH 123
	PSH 456
	SWAP
	SUB
	OUT
	PSH 6666
	PSH 9999
	OVER
	PSH 1111
	ADD
	OUT
	OUT
	OUT

	PSH 999			; push 3rd argument
	PSH 888			; push 2nd argument
	PSH 777			; push 1st argument
	PSHFP			; push frame pointer
	PSHSP			; push stack pointer
	PSH ret1		; push return address
	PSHSP
	PSH 16
	ADD
	POPFP			; set frame pointer
	BRA func1		; call func1
ret1:
	POPSP			; restore stack pointer
	POPFP			; restore frame pointer
	POP			; pop 1st argument
	POP			; pop 2nd argument
	POP			; pop 3rd argument
	HLT

; arguments in stack: RA, SP, FP, 777, 888, 999
func1:
	PSHFP
	PSH 0
	ADD
	LDW			; load 1st argument (FP + 0)
	OUT
	
	PSHFP
	PSH 4
	ADD
	LDW			; load 2nd argument (FP + 4)
	OUT

	PSHFP
	PSH 8
	ADD
	LDW			; load 3rd argument (FP + 8)
	OUT

	JMP			; return (RA in stack)
