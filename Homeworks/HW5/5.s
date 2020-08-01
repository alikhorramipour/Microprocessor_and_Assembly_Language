		MOV		R12, #0x4000000	;memory address register
		MOV		R0, #0x0
		MOV		R1, #0x1000000  ;amount of delay = 1000000 cycles
TOGGLE	STR		R0, [R12]
		ORN		R0, R0, R0
		MOV		R1, #0x1000000
	AGAIN	SUBS		R1, R1, #1
			BNE		AGAIN	;repeat until loop counter(R1) is zero
	B	TOGGLE