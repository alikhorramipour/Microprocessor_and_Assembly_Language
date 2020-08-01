MAIN		MOV		R0,  #48
		MOV		R1,  #46
		BL		Sort
		END
		
		
Sort		STR		R2, [SP, #-4]!
		CMP		R0, R1
		BLE		Done
		MOV		R2, R1
		MOV		R1, R0
		MOV		R0, R2
		
Done		LDR		R2, [SP], #4
		MOV		PC, LR