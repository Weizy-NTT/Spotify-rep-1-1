#include "gpio.h"
#include "port.h"
#include "sim.h"
#include "NVIC.h"
#include "uart.h"
void setup(){
    SIM_EnableClock(SIM_CLOCK_PORTC);

    //set pin 3, 13 is GPIO
    PORTC->PCR[3] |= 1<<8;
    PORTC->PCR[13]|1<<8;

    //Config interrupt falling edge
    PORTC->PCR[3] |= (0b1010<<19);
    PORTC->PCR[13] |= (0b1010<<19);

    //set input
    GPIOC->PDDR &= ~(1<<3);
    GPIOC->PDDR &= ~(1<<13);

    //pull up
    PORTC->PCR[3]  |= 3;
    PORTC->PCR[13] |= 3;

    NVIC->ISER[0] |= (1 << 31);


    //setup UART
    UART_Init(UART0,9600,48000000);
    NVIC->ISER[0] |= (1 << 12);

    //setup LCD
    LCD_Init();

    //ADC init
    ADC_Init();


}

int main(){

    while(1){

    }

}

void UART0_IRQHandler(void){

}


void PORTC_IRQHandler(void) {
    
    if (PORTC->ISFR & (1 << 3)) {
        
        PORTC->ISFR |= (1 << 3); 

        UART0_SendString("BUTTON1_PRESSED\n");
       
    }

    if (PORTC->ISFR & (1 << 13)) {
        
        PORTC->ISFR |= (1 << 13); 

        UART0_SendString("BUTTON2_PRESSED\n");

    }
}