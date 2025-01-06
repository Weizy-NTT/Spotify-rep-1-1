#ifndef SIM_H
#define SIM_H

#include <stdint.h>

// Base address for SIM module
#define SIM_BASE 0x40047000U

typedef struct {
    volatile uint32_t SOPT1;       // System Options Register 1
    volatile uint32_t SOPT1CFG;   // SOPT1 Configuration Register
    uint32_t RESERVED1[1023];     // Reserved space
    volatile uint32_t SOPT2;      // System Options Register 2
    uint32_t RESERVED2[1];        // Reserved space
    volatile uint32_t SOPT4;      // System Options Register 4
    volatile uint32_t SOPT5;      // System Options Register 5
    uint32_t RESERVED3[1];        // Reserved space
    volatile uint32_t SOPT7;      // System Options Register 7
    uint32_t RESERVED4[2];        // Reserved space
    volatile uint32_t SCGC4;      // System Clock Gating Control Register 4
    volatile uint32_t SCGC5;      // System Clock Gating Control Register 5
    volatile uint32_t SCGC6;      // System Clock Gating Control Register 6
    volatile uint32_t SCGC7;      // System Clock Gating Control Register 7
    volatile uint32_t CLKDIV1;    // Clock Divider Register 1
    volatile uint32_t FCFG1;      // Flash Configuration Register 1
    volatile uint32_t FCFG2;      // Flash Configuration Register 2
    volatile uint32_t UIDH;       // Unique Identification Register High
    volatile uint32_t UIDMH;      // Unique Identification Register Mid High
    volatile uint32_t UIDML;      // Unique Identification Register Mid Low
    volatile uint32_t UIDL;       // Unique Identification Register Low
    volatile uint32_t COPC;       // COP Control Register
    volatile uint32_t SRVCOP;     // Service COP Register
} SIM_Type;

// SIM Peripheral pointer
#define SIM ((SIM_Type *)SIM_BASE)

// Function Prototypes
void SIM_EnableClock(uint8_t module);
void SIM_DisableClock(uint8_t module);

// Module definitions for easy usage
#define SIM_CLOCK_PORTA  0x01  // Clock for PORTA
#define SIM_CLOCK_PORTB  0x02  // Clock for PORTB
#define SIM_CLOCK_PORTC  0x03  // Clock for PORTC
#define SIM_CLOCK_PORTD  0x04  // Clock for PORTD
#define SIM_CLOCK_PORTE  0x05  // Clock for PORTE
#define SIM_CLOCK_UART0  0x06  // Clock for UART0
#define SIM_CLOCK_UART1  0x07  // Clock for UART1
#define SIM_CLOCK_LCD    0x08  // Clock for LCD
#define SIM_CLOCK_TPM0   0x09  // Clock for TPM0
#define SIM_CLOCK_TPM1   0x0A  // Clock for TPM1
#define SIM_CLOCK_TPM2   0x0B  // ClocK for TPM2 

#endif 


// SIM_SCGC4 definitions
#define SIM_SCGC4_UART0_MASK (1 << 10)  // Enable clock for UART0
#define SIM_SCGC4_UART1_MASK (1 << 11)  // Enable clock for UART1

// SIM_SCGC5 definitions
#define SIM_SCGC5_PORTA_MASK (1 << 9)   // Enable clock for PORTA
#define SIM_SCGC5_PORTC_MASK (1 << 11)  // Enable clock for PORTC

// PORT_PCR definitions
#define PORT_PCR_MUX_MASK (0x7 << 8)    // MUX field mask
#define PORT_PCR_MUX(x) ((x) << 8)      // Set MUX value
