;
; Lab_3_3.asm
;
; Created: 04-Feb-20 4:01:17 PM
; Author : praga
;



//	Oppgave 3 - løkke 
	sbi  DDRB,DDB5  
		

main_loop:
	ldi  r18,4     
outer_loop:
	ldi  r17,249   
middle_loop:
	ldi  r16,250   
inner_loop:
	nop            
	dec  r16      
	brne inner_loop  

	nop            
	dec  r17       
	brne middle_loop 

	nop            
	dec  r18      
	brne outer_loop 

	sbi  PINB,PINB5  
rjmp main_loop


