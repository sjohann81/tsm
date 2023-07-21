main:
	PSH 40			; first 40 fibonacci numbers
	BRA fib			; call fib()
ret_fib:
	HLT			; stop program

fib:
	PSH 0			; initialize a, b and c variables
	PSH a
	STW
	PSH 1
	PSH b
	STW
	PSH 0
	PSH c
	STW
loop:
	DUP			; 40 was pushed before call
	PSH i
	LDW			; load variable i
	BEQ ret_fib		; if i == 6, return

	PSH a			; print fibonacci number
	LDW
	POP

	PSH a
	LDW			; load a
	PSH b
	LDW			; load b
	ADD			; a + b
	PSH c
	STW			; store c = a + b
	
	PSH b
	LDW			; load b
	PSH a
	STW			; store a = b
	PSH c
	LDW			; load c
	PSH b
	STW			; store b = c
	
	PSH i			; increment i
	LDW
	PSH 1
	ADD
	PSH i
	STW
	
	BRA loop

i:
	0
a:
	0
b:
	0
c:
	0
