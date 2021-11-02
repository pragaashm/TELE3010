;
; oving3_oppg4.asm
;
; Created: 06.05.2019 12:49:19
; Author : rksni
;


ldi r25, 181
// LDI Rd,K
// 1110 KKKK dddd KKKK
// Rd = 24, => d=0b1001, K = 181 = 1010 0101
// 1110 1010 0000 0101 = 0xEB95

sbi PINB,PINB5
// SBI A,b
// 1001 1010 AAAA Abbb
// A = 0x03 = 0b00011, b=5=0b101
// 1001 1010 0001 1101 = 0x9A1D

// For location in Flash/Atmel Studio see .png file in project folder


; Replace with your application code
start:
    rjmp start
