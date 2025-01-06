#include <stdint.h>
typedef struct {
    volatile uint32_t ISER[1];    // Interrupt Set Enable Register
    uint32_t RESERVED0[31];
    volatile uint32_t ICER[1];    // Interrupt Clear Enable Register
    uint32_t RESERVED1[31];
    volatile uint32_t ISPR[1];    // Interrupt Set Pending Register
    uint32_t RESERVED2[31];
    volatile uint32_t ICPR[1];    // Interrupt Clear Pending Register
    uint32_t RESERVED3[95];
    volatile uint32_t IPR[8];     // Interrupt Priority Register
} NVIC_Type;

#define NVIC ((NVIC_Type *)0xE000E100U)