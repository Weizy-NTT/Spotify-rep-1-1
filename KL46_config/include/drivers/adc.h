#ifndef ADC_H
#define ADC_H

#include <stdint.h>

// ADC Register Map
typedef struct {
    volatile uint32_t SC1[2];
    volatile uint32_t CFG1;
    volatile uint32_t CFG2;
    volatile uint32_t R[2];
    volatile uint32_t CV1;
    volatile uint32_t CV2;
    volatile uint32_t SC2;
    volatile uint32_t SC3;
    volatile uint32_t OFS;
    volatile uint32_t PG;
    volatile uint32_t MG;
    volatile uint32_t CLPD;
    volatile uint32_t CLPS;
    volatile uint32_t CLP4;
    volatile uint32_t CLP3;
    volatile uint32_t CLP2;
    volatile uint32_t CLP1;
    volatile uint32_t CLP0;
    uint32_t RESERVED;
    volatile uint32_t CLMD;
    volatile uint32_t CLMS;
    volatile uint32_t CLM4;
    volatile uint32_t CLM3;
    volatile uint32_t CLM2;
    volatile uint32_t CLM1;
    volatile uint32_t CLM0;
} ADC_Type;

#define ADC0_BASE (0x4003B000U)
#define ADC0 ((ADC_Type *)ADC0_BASE)

// Function Prototypes
void ADC_Init(void);
uint16_t ADC_Read(uint8_t channel);

#endif // ADC_H
