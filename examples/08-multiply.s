main:
	PSH 0			; push 3rd argument (return val)
	PSH 123			; push 2nd argument (b)
	PSH -456		; push 1st argument (a)
	PSHFP			; push frame pointer
	PSHSP			; push stack pointer
	PSH ret1		; push return address
	PSHSP
	PSH 16
	ADD
	POPFP			; set frame pointer
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
	PSHFP
	PSH 4
	ADD			; &b (FP + 4)
	LDW			; load b
	DUP			; stash a copy of b for later use
	PSH 0
	BEQ end_mult
	
	PSH 1
	AND
	PSH 0
	BEQ skip_accu		; if !(b & 1), skip
	PSHFP
	PSH 8
	ADD			; &answer (FP + 8)
	DUP			; stash a copy of &answer for later use
	LDW			; load answer
	PSHFP			; &a (FP + 0)
	LDW			; load a
	ADD			; answer + a
	SWAP			; get stashed &answer
	STW			; answer = answer + a
	
skip_accu:
	PSHFP			; &a
	DUP			; stash a copy of &a for later use
	LDW			; load a
	PSH 1
	SHL
	SWAP			; get stashed &a
	STW			; a = a << 1
	PSHFP
	PSH 4
	ADD			; &b
	DUP			; stash a copy of &b for later use
	LDW			; load b
	PSH 1
	SHR
	SWAP			; get stashed address
	STW			; b = b >> 1
	
	BRA mult
	
end_mult:
	POP
	JMP
