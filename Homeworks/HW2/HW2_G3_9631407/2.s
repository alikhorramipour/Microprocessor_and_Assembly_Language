		MOV		R0, #5
		BL		FCT
		END
		
FCT		MOV		R12, R0
		MOV		R10, #1			;result = R0!
		
L1		MOV		R6, R12		;start_MULTIPLY
		MOV		R7, R10
L2		ADD		R10, R10, R7
		SUB		R6, R6, #1
		CMP		R6, #1
		BNE		L2		;end_MULTIPLY
		SUB		R12, R12, #1
		CMP		R12, #1
		BNE		L1
		MOV		PC, LR
