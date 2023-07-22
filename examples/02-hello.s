loop:
	PSH m_ptr	; push pointer address
	LDW		; load pointer value
	LDB		; derreference pointer, access byte in 'text'
	DUP		; duplicate value
	OUTB		; pop and print byte
	
	PSH 0		; push 0 (null)
	BEQ end		; if last byte is a null, branch to end
	
	PSH m_ptr	; push pointer address
	LDW		; load pointer value
	PSH 1		; push 1
	ADD		; add pointer value + 1
	PSH m_ptr	; push pointer address
	STW		; update pointer
	
	BRA loop	; branch (unconditionally) to loop
end:
	HLT		; stop program

m_ptr:
	text		; pointer to text

text:
	"hello world!"
