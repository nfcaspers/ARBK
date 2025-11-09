;
; Praktikum1.asm
;
; Created: 12/10/2025 19:32:03
; Author : noelc
;

.include <m328pdef.inc>
.CSEG

.org 0x000 ;Reset Vector
rjmp start 

.org INT_VECTORS_SIZE
start:
	ldi r16, LOW(RAMEND)
	out SPL, r16
	ldi r16, HIGH(RAMEND)
	out SPH, r16

	;Pin Outputs setzen
	ldi r16, 0xFF //alle portd
	out DDRD, r16
	ldi r16, 3 //B0, B1 portb (binär)
	out DDRB, r16

main:
	;alle LEDs aus bis auf erste
	ldi r16, 0x00
	out PORTB, r16

	ldi r16, 0x01
	out PORTD, r16
	rcall delay
;Hauptprogrammschleife
loop:
	ldi r30, 0b10000000 ;Ziel
	rcall shiftleft

	rcall shift_portb

	ldi r30, 0b00000001
	rcall shiftright

	rjmp loop

;Shiftet das r16 register nach links und gibt es auf den LEDs aus
shiftleft:
	LSL r16
	out PORTD, r16
	rcall delay
	cp r30, r16 ;30-r16 ohne Speichern, wenn Z-Flag gesetzt ==
	breq slreturn
	rjmp shiftleft

;setzt letzte LED auf PortB auf aus und return zu loop
slreturn:
    ldi r17, 0
	out PORTD, r17 ;weiter mit LEDs auf PORTB
	ret

;Führt den shift für LEDs aus, die mit PortD registern gesteuert werden
;verwendet r17, da in r16 der Zustand von gespeichert ist, der danach weiterverwendet wird
shift_portb:
    ldi r17, 1
	out PORTB, r17
	rcall delay

	lsl r17
	out PORTB, r17
	rcall delay
	lsr r17
	out PORTB, r17
	rcall delay
	ldi r17, 0
	out PORTB, r17
	out PORTD, r16
	rcall delay
	ret

;Shiftet das r16 register nach rechts und gibt es auf den LEDs aus
shiftright:
	LSR r16
	out PORTD, r16
	rcall delay
	cp r30, r16
	breq srreturn
	rjmp shiftright
	
;return zu loop
srreturn:
	ret


delay:
	LDI R26, 20 ;20-160 oder 40-80 wegen 3_200_00 Cycles | 1 Takt
	L3:
       LDI R25, 160 ;1 Takt
	   ;1000 Takte
	   L1: LDI R24, 250      ;1 
	      L2:  NOP           ;1
		  DEC R24            ;1
		  BRNE L2            ;2 wenn Branch 1 wenn nicht
	   DEC R25               ;1
	   BRNE L1               ;2 wenn Branch 1 wenn nicht
	DEC R26                  ;1
	BRNE L3                  ;2 wenn Branch 1 wenn nicht
	ret                      ;4+3von rcall

;Hexenwerk welches ich nicht verstehe:

; Assembly code auto-generated
; by utility from Bret Mulvey
; Delay 3 200 000 cycles
; 200ms at 16.0 MHz
;delay:
;    ldi  r18, 17
;    ldi  r19, 60
;    ldi  r20, 204
;L1: dec  r20
;    brne L1
;    dec  r19
;    brne L1
;    dec  r18
;    brne L1
;	ret

