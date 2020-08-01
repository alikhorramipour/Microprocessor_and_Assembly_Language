		LDR		R10, =9631407			;9631407 = 0100100101111011010101111
		MOV		R0, #5
		MOV		R1, #7
		MOV		R3, #0
		MOV		R4, #0						;result = 5
		MOV		R2, #29						;loop counter
AGAIN	AND		R3, R1, R10			;repeat until loop counter(R2) is zero
		CMP		R0, R3
		ADDEQ	R4, R4, #1
		MOVS		R0, R0, LSL #1
		MOVS		R1, R1, LSL #1
		SUBS		R2, R2, #1
		BNE		AGAIN
		END