;
; Lab_3_2.asm
; Oppgave 2
; Created: 29-Jan-20 3:15:59 PM
; Author : praga
;

ldi r16,127
ldi r17,129
adc r17,r16

/*Sum er egentlig 256/0x100, men f�r ikke plass i 8 bit.
Ser at carry blir satt*/

ldi r16,80
ldi r17,48
add r17,r16

/*F�r 0x80/128/-128. Negative flag blir satt pga bit 7. Two complement overflow
er satt siden resultatet har endret fortegn.*/

ldi r16,128
ldi r17,40
add r17,r16

/*Her f�r vi (-)168/0x80. Negativ flag satt pga bit 7. Sign flag gitt ettersom
resultatet er negativt, dersom en regner med signed (i 8-bit signed nummer, representerer
en bit signed bit) */

ldi r16,254
ldi r17,255
add r17,r16
/*F�r ikke plass i 8-bit, carry satt. Resultatet blir negativt om signed regnes med.
Half carry er p�.*/

ldi r28,low(1000)
ldi r29,low(500)
add r28,r29
ldi r29,high(1000)
ldi r30,high(500)
adc r29,r30
nop
//Her f�r vi 0x05DC, som er 1500.
adiw r29:r28, 50 //Legger direkte til en verdi p� 50 i registrene r29:r28
//F�r da 0x060e = 1550.
