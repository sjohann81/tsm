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
	PSH ret1		; push return address
	PSHSP			; push stack pointer
	BRA func1		; call func1
ret1:
	PSH 16			; pop 4 arguments (4 * 4 bytes)
	ADD
	POPSP			; update stack pointer
	HLT
	
func1:
	DUP
	PSH 8
	ADD
	LDW			; load 1st argument
	OUT
	DUP
	PSH 12
	ADD
	LDW			; load 2nd argument
	OUT
	DUP
	PSH 16
	ADD
	LDW			; load 3rd argument
	OUT
	OVER			; get return address
	JMP			; return
