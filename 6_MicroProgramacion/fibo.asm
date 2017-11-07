inicio: LOAD R0, 0x02    ; Posicion donde esta el digito a buscar
        SET R1          ; Cargando un 1 en R1
        SET R2          ; Cargando un 1 en R2
ciclo:  MOV R3, R2      ; cantParejas = ultMes
        ADD R3, R1      ; cantParejas += anteUltMes
        MOV R1, R2      ; anteUltMes = ultMes
        MOV R2, R3      ; ultMes = cantParejas
        DEC R0          ; meses = meses - 1
        JE  fin         ; Si termino ir a fin
        JMP ciclo       ; Siguiente iteracion
fin:    STORE R2, 0x00   ; Almacenar el resultado
        HALT            ; Terminado, detener maquina
