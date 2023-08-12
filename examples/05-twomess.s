main:
	PSH mess1
	PSH ptr
	STW			; store mess1 address to ptr
	PSH ret1
	BRA print		; call print
ret1:
	PSH 10
	OUTB			; print a line break

	PSH mess2
	PSH ptr
	STW			; store mess2 address to ptr
	PSH ret2
	BRA print		; call print
ret2:
	HLT

print:
	PSH ptr
	LDW			; load pointer
	LDB			; derreference string byte
	DUP
	OUTB			; print it
	
	PSH 0
	BEQ ret_print		; if byte is a null, return
	
	PSH ptr
	LDW
	PSH 1
	ADD
	PSH ptr
	STW			; increment pointer
	BRA print		; loop to print
ret_print:
	JMP

ptr:
	0
mess1:
	"Lorem ipsum dolor"
mess2:
	"labore et dolore magna aliqua"
