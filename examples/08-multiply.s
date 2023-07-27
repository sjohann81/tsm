main:
	PSH 0			; push 3rd argument (return val)
	PSH 123			; push 2nd argument (b)
	PSH -456		; push 1st argument (a)
	PSHFP			; push frame pointer
	PSHSP			; push stack pointer
	PSH ret1		; push return address
	BRA mult		; call multiply routine
ret1:
	POPSP			; pop stack pointer
	POPFP			; pop frame pointer
	POP			; pop 1st argument
	POP			; pop 2nd argument
	OUT			; pop result, print return val
	HLT


; uint16_t mul(uint16_t a, uint16_t b)
; {
; 	uint16_t answer = 0;
; 
; 	while (b) {
; 		if (b & 1)
; 			answer += a;
; 		a <<= 1;
; 		b >>= 1;
; 	}
; 	
; 	return answer;
; }
	
mult:
	PSHSP
	POPFP			; set frame pointer
loop_mult:
	PSHFP
	PSH 20
	ADD			; &b (FP + 20)
	LDW			; load b
	DUP			; stash a copy of b for later use
	PSH 0
	BEQ end_mult
	
	PSH 1
	AND
	PSH 0
	BEQ skip_accu		; if !(b & 1), skip
	PSHFP
	PSH 24
	ADD			; &answer (FP + 24)
	DUP			; stash a copy of &answer for later use
	LDW			; load answer
	PSHFP
	PSH 16
	ADD			; &a
	LDW			; load a
	ADD			; answer + a
	SWAP			; get stashed &answer
	STW			; answer = answer + a
	
skip_accu:
	PSHFP
	PSH 16
	ADD			; &a
	DUP			; stash a copy of &a for later use
	LDW			; load a
	PSH 1
	SHL
	SWAP			; get stashed &a
	STW			; a = a << 1
	
	PSHFP
	PSH 20
	ADD			; &b
	DUP			; stash a copy of &b for later use
	LDW			; load b
	PSH 1
	SHR
	SWAP			; get stashed address
	STW			; b = b >> 1
	
	BRA loop_mult
	
end_mult:
	POP
	JMP
