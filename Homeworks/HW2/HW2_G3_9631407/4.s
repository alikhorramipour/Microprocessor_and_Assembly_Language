		MOV		R0, #12
		MOV		R1, #9
		
GCD		CMP		R0, R1		;RESULT WILL BE STORED IN R1
		SUBGT	R0, R0, R1
		SUBLT	R1, R1, R0
		BNE		GCD
		END