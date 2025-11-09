; CP/M I/O SUBROUTINES  16 AUG 82

; ASCII CHARACTERS
CR      EQU     0DH             ; CARRIAGE RETURN
LF      EQU     0AH             ; LINE FEED
CTRLZ   EQU     1AH             ; OPERATOR INTERRUPT

; CP/M BDOS FUNCTIONS
RCONF   EQU     1               ; READ CON: INTO (A)
WCONF   EQU     2               ; WRITE (A) TO CON:
RBUFF   EQU     10              ; READ A CONSOLE LINE

; CP/M ADDRESSES
RBOOT   EQU     0               ; RE-BOOT CP/M SYSTEM
BDOS    EQU     5               ; SYSTEM CALL ENTRY
TPA     EQU     100H            ; TRANSIENT PROGRAM AREA

        ORG     TPA             ; ASSEMBLE PROGRAM FOR TPA

START:  LXI     SP,STAK         ; SET UP USER'S STACK

ZERO    EQU     30H

; PROGRAM GOES HERE
START1:
        CALL SPMSG
        DB 'HELLO THERE! PLEASE INPUT A NUMBER.',CR,LF,0

        CALL CIMSG
        LXI H,INBUF+2   ; POINT TO FIRST CHARACTER

        CALL PARSEINT
        CALL PRINTDE    ; PARSE AND PRINT

        TESTPRINT:
        MVI 'A' ; PRINT THE LETTER A TO CONSOLE
        CALL CO

        DCX D   ; DECREMENT COUNTER
        JNZ TESTPRINT

        CALL SPMSG
        DB 'THATS ALL, FOLKS!',0
        JMP 0   ; END OUR LIL TEST PROGRAM

; INPUT (CHAR POINTER) GOES IN HL, RESULT GOES IN DE
PARSEINT:
        PUSH B
        PUSH H
        LXI D,00H ; CLEAR DE REGISTERS IN PREPARATION
        LXI B,00H ; SAME WITH BC
        MOV A,M
        CPI '-'
        JNZ NONNEG
        LDA FLAG
        ORI 01H ; SET LSB TO INDICATE SUBTRACTION LATER
        STA FLAG
        JMP PLOOP
        NONNEG:        LDA FLAG
                        ANI FEH ; MASK OUT LSB TO INDICATE NO SUBTRACTION LATER
                        STA FLAG
        PLOOP:
                MOV A,M ; GET CHARACTER
                
                CPI A,'0'
                JNC PLOOPEND
                CPI A,'9'
                JC PLOOPEND
                SUI '0'
                ADD E
                MOV E,A
                MOV A,D
                ACI 00H ; ADD CARRY TO HIGH BYTE (REG B)
                MOV D,A
                MULTBYTEN: ; TO DO THIS WE SHIFT THE BYTES LEFT 3 TIMES, THEN ADD THE ORIGINAL VALUES TWICE
                        MOV B,D ; BACK UP THE PRE-LEFT-SHIFT TOTAL IN BC
                        MOV C,E
                        ADI 0   ; RESET CARRY. WE ONLY NEED TO DO THIS ONCE SINCE RAL-ING D SHOULD NOT PUT ANYTHING 
                                ; OTHER THAN ZERO IN THE CARRY. CONVERSELY WE COULD JC AFTER THE RAL TO DETECT AN OVERFLOW

                        MOV A,E
                        MOV E,A
                        RLC
                        MOV A,D
                        RAL
                        MOV D,A

                        MOV A,E ; REPEAT 1
                        MOV E,A
                        RLC
                        MOV A,D
                        RAL
                        MOV D,A

                        MOV A,E ; REPEAT 2
                        MOV E,A
                        RLC
                        MOV A,D
                        RAL
                        MOV D,A

                        XCHG    ; SO WE CAN DAD
                        DAD B
                        DAD B
                        DAD B
                        XCHG
                
                INX H   ; INCREMENT ADDRESS
                JMP PLOOP

        PLOOPEND:
        LDA FLAG        ; CHECK IF NEGATIVE
        ANI 01H
        CPI 01H
        SUB A           ; CLEAR ACCUMULATOR
        JZ NEGATIVE
        POPREGSRET:
        POP H
        POP B
        RET
        NEGATIVE:       ; PERFORM DOUBLE SUBTRACTION
                        SUB D
                        MOV D,A
                        MVI A,0 ; MVI INSTEAD OF SUB A BECAUSE WE DONT WANT TO TOUCH STATUS BITS
                        SBB E
                        MOV E,A
                        JMP POPREGSRET

; PRINTS A SIGNED 16-BIT INTEGER IN DE
PRINTDE:
        ; Save registers
        PUSH PSW
        PUSH B
        PUSH D
        PUSH H

        MOV A,D
        ORA E
        JZ  PZZERO

        ; Check sign
        MOV A,D
        ANI 80H
        JZ  POSITIVEDONE

        ; Negative: negate DE = -DE and print '-'
        MOV A,E
        CMA
        MOV E,A
        MOV A,D
        CMA
        MOV D,A
        INX D
        MVI A,'-'
        CALL CO

POSITIVEDONE:
        MVI B,0             ; digit count = 0

CONVERT:
        MOV A,D
        ORA E
        JZ  POPPRINT       ; stop when quotient = 0

        MVI H,0
        MVI L,0

DIVLOOP:
        MOV A,D
        ORA A
        JNZ SUB10
        MOV A,E
        CPI 10
        JC  DIVDONE
SUB10:
        MOV A,E
        SUI 10
        MOV E,A
        JC  DECD
        JMP INCQL
DECD:
        DCR D
INCQL:
        INX H
        JMP DIVLOOP

DIVDONE:
        MOV A,E
        ADI '0'
        PUSH PSW
        INR B
        MOV D,H
        MOV E,L
        JMP CONVERT

POPPRINT:
        MOV C,B
PRINTLOOP:
        POP PSW
        CALL CO
        DCR C
        JNZ PRINTLOOP
        JMP DONE

PZZERO:
        MVI A,'0'
        CALL CO

DONE:
        ; Restore registers
        POP H
        POP D
        POP B
        POP PSW
        RET



; CONSOLE CHARACTER INTO REGISTER A MASKED TO 7 BITS
CI:     PUSH    B               ; SAVE REGISTERS
        PUSH    D
        PUSH    H
        MVI     C,RCONF         ; READ FUNCTION
        CALL    BDOS
        ANI     7FH             ; MASK TO 7 BITS
        POP     H               ; RESTORE REGISTERS
        POP     D
        POP     B
        RET

; CHARACTER IN REGISTER A OUTPUT TO CONSOLE
CO:     PUSH    B               ; SAVE REGISTERS
        PUSH    D
        PUSH    H
        MVI     C,WCONF         ; SELECT FUNCTION
        MOV     E,A             ; CHARACTER TO E
        CALL    BDOS            ; OUTPUT BY CP/M
        POP     H               ; RESTORE REGISTERS
        POP     D
        POP     B
        RET

        ; SET UP STACK SPACE
DS      64              ; 40H LOCATIONS
STAK:   DB      0               ; TOP OF STACK

; CARRIAGE RETURN, LINE FEED TO CONSOLE
TWOCR:  CALL    CCRLF           ; DOUBLE SPACE LINES
CCRLF:  MVI     A,CR
        CALL    CO
        MVI     A,LF
        JMP     CO

; MESSAGE POINTED TO BY HL OUT TO CONSOLE
COMSG:  MOV     A,M             ; GET A CHARACTER
        ORA     A               ; ZERO IS THE TERMINATOR
        RZ                      ; RETURN ON ZERO
        CALL    CO              ; ELSE OUTPUT THE CHARACTER
        INX     H               ; POINT TO THE NEXT ONE
        JMP     COMSG           ; AND CONTINUE

; MESSAGE POINTED TO BY STACK OUT TO CONSOLE
SPMSG:  XTHL                    ; GET "RETURN ADDRESS" TO HL
        XRA     A               ; CLEAR FLAGS AND ACCUMULATOR
        ADD     M               ; GET ONE MESSAGE CHARACTER
        INX     H               ; POINT TO NEXT
        XTHL                    ; RESTORE STACK FOR
        RZ                      ; RETURN IF DONE
        CALL    CO              ; ELSE DISPLAY CHARACTER
        JMP     SPMSG           ; AND DO ANOTHER

; INPUT CONSOLE MESSAGE INTO BUFFER
CIMSG:  PUSH    B               ; SAVE REGISTERS
        PUSH    D
        PUSH    H
        LXI     H,INBUF+1       ; ZERO CHARACTER COUNTER
        MVI     M,0
        DCX     H               ; SET MAXIMUM LINE LENGTH
        MVI     M,80
        XCHG                    ; INBUF POINTER TO DE REGISTERS
        MVI     C,RBUFF         ; SET UP READ BUFFER FUNCTION
        CALL    BDOS            ; INPUT A LINE
        LXI     H,INBUF+1       ; GET CHARACTER COUNTER
        MOV     E,M             ; INTO LSB OF DE REGISTER PAIR
        MVI     D,0             ; ZERO MSB
        DAD     D               ; ADD LENGTH TO START
        INX     H               ; PLUS ONE POINTS TO END
        MVI     M,0             ; INSERT TERMINATOR AT END
        POP     H               ; RESTORE ALL REGISTERS
        POP     D
        POP     B
        RET

; GET YES OR NO FROM CONSOLE
GETYN:  CALL    SPMSG
        DB      ' (Y/N)?: ',0
        CALL    CIMSG           ; GET INPUT LINE
        CALL    CCRLF           ; ECHO CARRIAGE RETURN
        LDA     INBUF+2         ; FIRST CHARACTER ONLY
        ANI     01011111B       ; CONVERT LOWER CASE TO UPPER
        CPI     'Y'             ; RETURN WITH ZERO = YES
        RZ
        CPI     'N'             ; NON-ZERO = NO
        JNZ     GETYN           ; ELSE TRY AGAIN
        CPI     0               ; RESET ZERO FLAG
        RET                     ; AND ALL DONE

INBUF:  DS      83              ; LINE INPUT BUFFER
FLAG: DS 1 ; FLAG BYTE FOR USE BY THE PROGRAM

        END