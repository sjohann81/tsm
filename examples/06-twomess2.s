main:
	PSH mess1		; push pointer to mess1 into the stack
	PSH ret1
	PSH ret_addr
	STW			; patch ret_addr to ret1
	BRA print		; call print
ret1:
	POP
	PSH 10
	OUTB			; print a line break

	PSH mess2		; push pointer to mess2 into the stack
	PSH ret2
	PSH ret_addr
	STW			; patch ret_addr to ret2
	BRA print		; call print
ret2:
	POP
	HLT

print:
	DUP			; duplicate the parameter (pointer)
	LDB			; derreference string byte
	DUP
	OUTB			; print it
	
	PSH 0
	BEQ			; if byte is a null, return (patched address)
ret_addr:
	0
	
	PSH 1
	ADD			; increment pointer
	BRA print		; loop to print

mess1:
	"Lorem ipsum dolor"
mess2:
	"labore et dolore magna aliqua"
