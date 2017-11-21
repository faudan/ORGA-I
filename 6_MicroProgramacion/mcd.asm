inicio: LOAD R0, 0x02
		LOAD R1, 0x03
ciclo:  MOV R2, R0
		MOV R3, R1
		SUB R2, R3
		JE fin
		JN otro
        SUB R0, R1
        JMP ciclo
otro:	SUB R1, R0
        JMP ciclo       ; Siguiente iteracion
fin:    STORE R0, 0x00   ; Almacenar el resultado
        HALT            ; Terminado, detener maquina
