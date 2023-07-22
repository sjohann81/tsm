main:
	PSH val1		; test if va1 < val 2
	LDW
	PSH val2
	LDW
	BLT less_than
	PSH 0
	OUT
	BRA end
less_than:
	PSH 'a'
	OUTB
	
	PSH val2		; test if val2 >= val1
	LDW
	PSH val1
	LDW
	BGE gre_equal1
	PSH 0
	OUT
	BRA end
gre_equal1:
	PSH 'b'
	OUTB
	
	PSH val1		; test if val2 >= val1
	LDW
	PSH val1
	LDW
	BGE gre_equal2
	PSH 0
	OUT
	BRA end
gre_equal2:
	PSH 'c'
	OUTB
	
	PSH val1		; test if val1 != val2
	LDW
	PSH val2
	LDW
	BNE not_equal
	PSH 0
	OUT
	BRA end
not_equal:
	PSH 'd'
	OUTB
	
	PSH val2		; test if val1 == val2
	LDW
	PSH val2
	LDW
	BEQ equal
	PSH 0
	OUT
	BRA end
equal:
	PSH 'e'
	OUTB
	
	PSH val1		; test if val1 < -23456 || val2 == 555
	LDW
	PSH -23456
	BLT less_than_or
	PSH val2
	LDW
	PSH 555
	BEQ less_than_or
	PSH 0
	OUT
	BRA end
less_than_or:
	PSH 'f'
	OUTB
end:
	HLT

val1:
	-12345
val2:
	555
