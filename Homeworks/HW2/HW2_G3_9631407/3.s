		LDR		R0,   =0xF4129FFB		;R0 = 0xF4129FFB
		LDR		R1,   =0xF635225A		;R1 = 0xF635225A
		MOV		R2,   #0x61			;R2 = 0x61
		MOV		R3,   #0xF4			;R3 = 0xF4
		ADDS		R5,   R1, R0			;R5 = 0xF4129FFB + 0xF635225A and Carry = 1
		ADC		R6,   R2, R3 			;R6 = R2 + R3 + C; = 0x61 + 0xF4 + 1 = 0x156
		END