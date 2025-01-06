#ifndef LCD_H
#define LCD_H

#include <stdint.h>
#include "sim.h"
#include "port.h"
// LCD Base Address
#define LCD_BASE 0x40053000U

// LCD Register Map
typedef struct {
    volatile uint32_t GCR;   // General Control Register
    volatile uint32_t AR;    // Auxiliary Register
    volatile uint32_t FDSR;  // Fault Detection Status Register
    volatile uint32_t RESERVED1;
    volatile uint32_t PEN[2]; // Pin Enable Register
    volatile uint32_t BPEN[2]; // Backplane Enable Register
    volatile uint32_t WF[32];  // Waveform Register
} LCD_Type;

// Define LCD instance
#define LCD ((LCD_Type *)LCD_BASE)



// Function Prototypes
void LCD_Init(void);
void LCD_Clear(void);
void LCD_DisplayChar(uint8_t position, char character);
void LCD_DisplayString(const char *str);

#endif // LCD_H
