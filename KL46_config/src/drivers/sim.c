#include "sim.h"

void SIM_EnableClock(uint8_t module) {
    switch (module) {
        case SIM_CLOCK_PORTA:
            SIM->SCGC5 |= (1 << 9);  // Enable clock for PORTA
            break;
        case SIM_CLOCK_PORTB:
            SIM->SCGC5 |= (1 << 10); // Enable clock for PORTB
            break;
        case SIM_CLOCK_PORTC:
            SIM->SCGC5 |= (1 << 11); // Enable clock for PORTC
            break;
        case SIM_CLOCK_PORTD:
            SIM->SCGC5 |= (1 << 12); // Enable clock for PORTD
            break;
        case SIM_CLOCK_PORTE:
            SIM->SCGC5 |= (1 << 13); // Enable clock for PORTE
            break;
        case SIM_CLOCK_UART0:
            SIM->SCGC4 |= (1 << 10); // Enable clock for UART0
            break;
        case SIM_CLOCK_UART1:
            SIM->SCGC4 |= (1 << 11); // Enable clock for UART1
            break;
        case SIM_CLOCK_LCD:
            SIM ->SCGC5 |= (1 << 19);  // Enable clock for LCD (Corrected)
            break;
        case SIM_CLOCK_TPM0:
            SIM->SCGC6 |= (1 << 24); // Enable clock for TPM0
            break;
        case SIM_CLOCK_TPM1:
            SIM->SCGC6 |= (1 << 25); // Enable clock for TPM1
            break;
        case SIM_CLOCK_TPM2:
            SIM->SCGC6 |= (1 << 26); // Enable clock for TPM2
            break;
        default:
            // Invalid module
            break;
    }
}

void SIM_DisableClock(uint8_t module) {
    switch (module) {
        case SIM_CLOCK_PORTA:
            SIM->SCGC5 &= ~(1 << 9);  // Disable clock for PORTA
            break;
        case SIM_CLOCK_PORTB:
            SIM->SCGC5 &= ~(1 << 10); // Disable clock for PORTB
            break;
        case SIM_CLOCK_PORTC:
            SIM->SCGC5 &= ~(1 << 11); // Disable clock for PORTC
            break;
        case SIM_CLOCK_PORTD:
            SIM->SCGC5 &= ~(1 << 12); // Disable clock for PORTD
            break;
        case SIM_CLOCK_PORTE:
            SIM->SCGC5 &= ~(1 << 13); // Disable clock for PORTE
            break;
        case SIM_CLOCK_UART0:
            SIM->SCGC4 &= ~(1 << 10); // Disable clock for UART0
            break;
        case SIM_CLOCK_UART1:
            SIM->SCGC4 &= ~(1 << 11); // Disable clock for UART1
            break;
        case SIM_CLOCK_LCD:
            SIM->SCGC5 &= ~(1 << 19);  // Disable clock for LCD (Corrected)
            break;
        case SIM_CLOCK_TPM0:
            SIM->SCGC6 &= ~(1 << 24); // Disable clock for TPM0
            break;
        case SIM_CLOCK_TPM1:
            SIM->SCGC6 &= ~(1 << 25); // Disable clock for TPM1
            break;
        case SIM_CLOCK_TPM2:
            SIM->SCGC6 &= ~(1 << 26); // Disable clock for TPM2
            break;
        default:
            // Invalid module
            break;
    }
}
