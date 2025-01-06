#include <stdint.h>
#define GPIOA_BASE (0x400FF000u)
#define GPIOB_BASE (0x400FF040u)
#define GPIOC_BASE (0x400FF080u)
#define GPIOD_BASE (0x400FF0C0u)
#define GPIOE_BASE (0x400FF100u)

typedef struct {
    volatile uint32_t PDOR;  // Data Output
    volatile uint32_t PSOR;  // Set Output
    volatile uint32_t PCOR;  // Clear Output
    volatile uint32_t PTOR;  // Toggle Output
    volatile uint32_t PDIR;  // Data Input
    volatile uint32_t PDDR;  // Data Direction
} GPIO_Type;

#define GPIOA ((GPIO_Type *)GPIOA_BASE)
#define GPIOB ((GPIO_Type *)GPIOB_BASE)
#define GPIOC ((GPIO_Type *)GPIOC_BASE)
#define GPIOD ((GPIO_Type *)GPIOD_BASE)
#define GPIOE ((GPIO_Type *)GPIOE_BASE)

void GPIO_Init(void);
void GPIO_SetPin(GPIO_Type *gpio, uint32_t pin);
void GPIO_ClearPin(GPIO_Type *gpio, uint32_t pin);
void GPIO_TogglePin(GPIO_Type *gpio, uint32_t pin);