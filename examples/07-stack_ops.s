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
	BRA func1		; call func1
ret1:
	POPSP
	POPFP
	POP
	POP
	POP
	HLT

; arguments in stack: RA, SP, FP, 777, 888, 999
func1:
	PSHSP
	POPFP			; set frame pointer
	
	PSHFP
	PSH 16
	ADD
	LDW			; load 1st argument (SP + 16)
	OUT
	
	PSHFP
	PSH 20
	ADD
	LDW			; load 2nd argument (SP + 20)
	OUT

	PSHFP
	PSH 24
	ADD
	LDW			; load 3rd argument (SP + 24)
	OUT

	JMP			; return (RA in stack)
