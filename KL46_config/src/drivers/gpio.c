#include "sim.h"
#include "GPIO.h"
void GPIO_Init(){
    SIM_EnableClock(SIM_CLOCK_PORTA);
    SIM_EnableClock(SIM_CLOCK_PORTB);
    SIM_EnableClock(SIM_CLOCK_PORTC);
    SIM_EnableClock(SIM_CLOCK_PORTD);
    SIM_EnableClock(SIM_CLOCK_PORTE);
}

void GPIO_SetPin(GPIO_Type *gpio, uint32_t pin) {
    gpio->PSOR = (1 << pin); // Set pin to HIGH
}

void GPIO_ClearPin(GPIO_Type *gpio, uint32_t pin) {
    gpio->PCOR = (1 << pin); // Set pin to LOW
}

void GPIO_TogglePin(GPIO_Type *gpio, uint32_t pin) {
    gpio->PTOR = (1 << pin); // Toggle pin state
}