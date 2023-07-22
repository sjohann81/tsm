main:
	PSH 123		; push 123 to stack
	PSH 456		; push 456 to stack
	ADD		; add 123 to 456, pop 2 words and push result
	OUT		; pop and print the result
	HLT		; stop program
