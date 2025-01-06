#include <stdint.h>
#define PORTA_BASE 0x40049000U
#define PORTB_BASE 0x4004A000U
#define PORTC_BASE 0x4004B000U
#define PORTD_BASE 0x4004C000U
#define PORTE_BASE 0x4004D000U

typedef struct {
    volatile uint32_t PCR[32];  // Pin Control Register (32 pins)
    volatile uint32_t GPCLR;    // Global Pin Control Low Register
    volatile uint32_t GPCHR;    // Global Pin Control High Register
    uint32_t RESERVED[6];
    volatile uint32_t ISFR;     // Interrupt Status Flag Register
} PORT_Type;

#define PORTA ((PORT_Type *)PORTA_BASE)
#define PORTB ((PORT_Type *)PORTB_BASE)
#define PORTC ((PORT_Type *)PORTC_BASE)
#define PORTD ((PORT_Type *)PORTD_BASE)
#define PORTE ((PORT_Type *)PORTE_BASE)





