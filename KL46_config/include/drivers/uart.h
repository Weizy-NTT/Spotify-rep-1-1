#ifndef UART_H
#define UART_H

#include <stdint.h>

// Base addresses for UART modules
#define UART0_BASE 0x4006A000U
#define UART1_BASE 0x4006B000U

// UART Register Map
typedef struct {
    volatile uint8_t BDH;     // Baud Rate Register High
    volatile uint8_t BDL;     // Baud Rate Register Low
    volatile uint8_t C1;      // Control Register 1
    volatile uint8_t C2;      // Control Register 2
    volatile uint8_t S1;      // Status Register 1
    volatile uint8_t S2;      // Status Register 2
    volatile uint8_t C3;      // Control Register 3
    volatile uint8_t D;       // Data Register
    volatile uint8_t MA1;     // Match Address Register 1
    volatile uint8_t MA2;     // Match Address Register 2
    volatile uint8_t C4;      // Control Register 4
    volatile uint8_t C5;      // Control Register 5 (UART0 only)
} UART_Type;

// UART instance definitions
#define UART0 ((UART_Type *)UART0_BASE)
#define UART1 ((UART_Type *)UART1_BASE)

// Function Prototypes
void UART_Init(UART_Type *uart, uint32_t baud_rate, uint32_t module_clock);
void UART_SendChar(UART_Type *uart, char ch);
char UART_ReceiveChar(UART_Type *uart);
void UART_SendString(UART_Type *uart, const char *str);

#endif // UART_H
