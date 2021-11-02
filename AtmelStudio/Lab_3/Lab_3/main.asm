;
; Lab_3.asm
; Oppgave 1
; Created: 29-Jan-20 12:33:57 PM
; Author : praga

ldi r17,3

ldi r18,5

mov r0,r18

out DDRB,r17

in r0,DDRB

sts 0x0100,r18

lds r1,0x0100

st X+,r18

ld r16,x

push r16

lds r16,99

pop r16
nop