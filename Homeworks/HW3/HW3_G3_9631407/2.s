			MOV		R0, #9
fillStack		STR		R0, [R13, #4]!
			SUBS		R0, R0, #1
			BNE		fillStack 		;filling the stack with numbers 1-9
			
			MOV		R1, #9
			STR		R1, [R13, #4]!
			BL		initMaxMin
			LDR		R10, [R13], #-4
			LDR		R11, [R13], #-4
			END
			
initMaxMin	LDR		R2, [R13], #-4
			LDR		R10, =0x80000000	;minimum
			LDR		R11, =0x7FFFFFFF	;maximum
			
findMaxMin	LDR		R3, [R13], #-4
			CMP		R3, R10
			MOVGE	R10, R3
			CMP		R3, R11
			MOVLT	R11, R3
			SUBS		R2, R2, #1
			BNE		findMaxMin		;repeat until loop counter(R2) is zero
			
			STR		R10, [R13, #4]!
			STR		R11, [R13, #4]!
			MOV		PC, LR
