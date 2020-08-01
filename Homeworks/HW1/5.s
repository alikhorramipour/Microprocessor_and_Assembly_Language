		MOV		R12, #0x100
		MOV		R0, #0x0
		MOV		R1, #0x9
AGAIN	ADD		R0, R0, #0x1
		STR		R0, [R12]
		ADD		R12, R12, #0x4
		SUBS		R1, R1, #1
		BNE		AGAIN ;repeat until loop counter(R1) is zero
HERE		B		HERE
		END
