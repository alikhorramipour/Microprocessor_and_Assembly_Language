		MOV		R12, #0x8000000	;memory address register
		MOV		R0, #0x0
		MOV		R2, #0x0			;summary
		MOV		R1, #0xA
AGAIN	STR		R0, [R12]
		ADD		R2, R2, R0
		ADD		R12, R12, #0x20
		SUBS		R1, R1, #1
		BNE		AGAIN 			;repeat until loop counter(R1) is zero
HERE		B		HERE
		END
