#define F_CPU 16000000UL //16MHz system clock
#define T1_PRESCALE 64
#define S_PERIOD F_CPU/(25*T1_PRESCALE) //0.04s =40ms
#define S_MAX S_PERIOD/4 // 10ms
#define S_MIN S_MAX/2 // 5ms

#include <avr/interrupt.h>

void tim_1(void);
void ADC_komp(void);
uint16_t V_adc;

int main(void){
    
    DDRB |= (1<<DDB5); //PB5 som output
    PORTD = (1<<PORTD4); //Pull-up PD4
    
    tim_1();
    ADC_komp();
    sei();
    
    
}

void tim_1(void){ //Funksjon for Timer1
    
    DDRB |= (1<<DDB2)|(1<<DDB1); //0C1A/0C1B output. 0C1A satt til compare. ICR1 så en kan bruke compare match
    TCCR1A = (1<<COM1B1)|(0<<COM1B0)|(1<<COM1A1)|(0<<COM1A0)|(1<<WGM11)|(0<<WGM10); //PMW
    TCCR1B = (1<<CS11)|(1<<WGM13)|(1<<WGM12); //ICR1 top 
    ICR1 = S_PERIOD;
    
}

void ADC_komp(void){ //Funksjon for ADC
    ADMUX =  (5<<MUX0)|(1<<REFS0)|(0<<REFS1); //AVcc Internal voltage satt som ref. ADC5 som inngangsverdi
    DIDR0 |= (1<<ADC4D); //digital input buffer deaktivert.
    ADCSRA = (1<<ADEN)|(1<<ADATE)|(1<<ADIE)|(7<<ADPS0); //ADC, auto trigger, ADC interrupt enabled. Prescaler = 8.
    ADCSRB = 0x00; //Free running mode.
    ADCSRA |= (1<<ADSC); //Starter konversjon.
}


ISR(ADC_vect){ //Avbruddsrutine for ADC
    V_adc = ADCH; //Konversjonsverdi er lagret her
    OCR1A = (S_MIN + S_MIN*(V_adc*5));
}

ISR(INT0_vect){ //Avbrudd og toggle PD5
	DDRB |= (1<<DDB5);
    PINB |= (1<<PINB5);
}
    
    