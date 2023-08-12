main:
	PSH mess1		; push pointer to mess1 into the stack
	PSH ret1
	BRA print		; call print
ret1:
	POP
	PSH 10
	OUTB			; print a line break

	PSH mess2		; push pointer to mess2 into the stack
	PSH ret2
	BRA print		; call print
ret2:
	POP
	HLT

print:
	OVER
print_loop:
	DUP			; duplicate the parameter (pointer)
	LDB			; derreference string byte
	DUP
	OUTB			; print it
	
	PSH 0
	BEQ ret_print		; if byte is a null, return
	
	PSH 1
	ADD			; increment pointer
	BRA print_loop		; loop to print
ret_print:
	POP
	JMP

mess1:
	"Lorem ipsum dolor"
mess2:
	"labore et dolore magna aliqua"
