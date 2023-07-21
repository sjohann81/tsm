main:
	PSH mess1
	PSH ptr
	STW			; store mess1 address to ptr
	PSH ret1
	PSH ret_addr
	STW			; patch ret_addr to ret1
	BRA print		; call print
ret1:
	PSH 10
	POPB			; print a line break

	PSH mess2
	PSH ptr
	STW			; store mess2 address to ptr
	PSH ret2
	PSH ret_addr
	STW			; patch ret_addr to ret2
	BRA print		; call print
ret2:
	HLT

print:
	PSH ptr
	LDW			; load pointer
	LDB			; derreference string byte
	DUP
	POPB			; print it
	
	PSH 0
	BEQ			; if byte is a null, return (patched address)
ret_addr:
	0
	
	PSH ptr
	LDW
	PSH 1
	ADD
	PSH ptr
	STW			; increment pointer
	BRA print		; loop to print

ptr:
	0
mess1:
	"Lorem ipsum dolor"
mess2:
	"labore et dolore magna aliqua"
