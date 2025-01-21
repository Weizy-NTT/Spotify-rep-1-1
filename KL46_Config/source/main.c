#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_slcd.h"
#include "fsl_clock.h"
#include "fsl_uart.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_common.h"
#include "pin_mux.h"
#include <stdio.h>
#include "lcd.h"
#include "fsl_adc16.h"

#define RX_BUFFER_SIZE 4
#define UART0_RX_PIN 1U  // PTA1
#define UART0_TX_PIN 2U  // PTA2
#define PIT_CHANNEL 0
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_CoreSysClk)
#define DEMO_ADC16_BASE ADC0                // Use ADC0
#define DEMO_ADC16_CHANNEL_GROUP 0U         // Channel group 0
#define DEMO_ADC16_USER_CHANNEL 3U          // ADC0_SE3 channel (PTE22)
#define ADC_MAX_VALUE 4095.0                // 12-bit resolution
#define VREFH 3.3                           // Reference voltage
#define AVERAGE_COUNT 2                     // Number of readings for averaging

volatile char rx_buffer[RX_BUFFER_SIZE + 1];
volatile uint8_t rx_index = 0;
volatile bool data_ready = false;
volatile uint8_t minutes = 0;
volatile uint8_t seconds = 0;
volatile uint8_t sw1_pressed = 0;
volatile uint8_t sw3_pressed = 0;
volatile uint32_t sw1_hold_time = 0;
volatile uint32_t sw3_hold_time = 0;
volatile bool sw1_pressed_state = false;
volatile bool sw3_pressed_state = false;
volatile int minutesThreshold = 0;
volatile int secondsThreshold = 0;
volatile uint16_t adcValueOld = 0;
volatile uint16_t adcValue = 0;
adc16_config_t adc16ConfigStruct;
adc16_channel_config_t adc16ChannelConfigStruct;
volatile int transfer = 0;
volatile bool lcdFlag = false;
volatile bool countInterrupt = false;
volatile int storeCounterValue = 0;
volatile bool pauseFlag = false;
volatile bool playFlag = false;
volatile uint16_t tick_counter = 0;

void Send_ADC_Value(UART_Type *base, uint16_t adc_value);
void GPIO_Init(void);
void Enable_Interrupts(void);
void UART0_IRQHandler(void);
void init_UART0_with_interrupt(void);
void PIT_Init_NEW(void);
void PIT_IRQHandler(void);
void UART_SendByte(UART_Type *base, uint8_t data);
void UART_SendString(UART_Type *base, const char *str);
void processButtonLogic();
void initADC();
void handleADC();
void PIT_Reload(uint32_t newLoadValue);

int main(void) {
    initADC();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    init_UART0_with_interrupt();
    LCD_Init();
    GPIO_Init();
    Enable_Interrupts();
    PIT_Init_NEW();
    LCD_DisplayTime(00,00);

    while (1) {
        processButtonLogic();
        if (transfer == 1) {
            handleADC();
            transfer = 0;
        }
    }
}

void UART0_IRQHandler(void) {
    if (UART0->S1 & UART_S1_RDRF_MASK) { // Check if data is ready to read (RDRF flag)

        char received_byte = UART0->D; // Read byte from UART

        if (rx_index < RX_BUFFER_SIZE && received_byte != '\0') {
            rx_buffer[rx_index++] = received_byte; // Store received byte in buffer
        }
        if (rx_index == 2 && (rx_buffer[0] == 'P' && (rx_buffer[1] == 'A' || rx_buffer[1] == 'L'))) {
            // Check for "PA" or "PL" command
            if (rx_buffer[1] == 'A') {
                if (playFlag == true) {
                    storeCounterValue = PIT->CHANNEL[PIT_CHANNEL].LDVAL;
                    lcdFlag = false;
                    pauseFlag = true;
                    playFlag = false;
                }
            } else if (rx_buffer[1] == 'L') {
                if (pauseFlag == true) {
                    PIT_Reload(storeCounterValue);
                    lcdFlag = true;
                    pauseFlag = false;
                    playFlag = true;
                }
            }
            rx_index = 0; // Reset buffer index
            memset(rx_buffer, 0, RX_BUFFER_SIZE); // Clear buffer
        } else if (rx_index == RX_BUFFER_SIZE || received_byte == '\n') {
            // Check if 4 bytes of data are received
            if (rx_index == 4) {
                tick_counter = 0;
                PIT_Reload((PIT_SOURCE_CLOCK / 200) - 1);
                minutes = 0;
                seconds = 0;
                minutesThreshold = (rx_buffer[0] - '0') * 10 + (rx_buffer[1] - '0'); // Convert string to number
                secondsThreshold = (rx_buffer[2] - '0') * 10 + (rx_buffer[3] - '0'); // Convert string to number
                lcdFlag = true;
                playFlag = true;
            }
            rx_index = 0; // Reset buffer index
            memset(rx_buffer, 0, RX_BUFFER_SIZE); // Clear buffer
        }
    }
}

void PORTC_PORTD_IRQHandler(void) {
    // Clear all interrupt flags when entering the handler
    uint32_t interruptFlags = PORTC->ISFR;
    PORTC->ISFR = interruptFlags; // Clear all interrupt flags
    if (countInterrupt == true) {
        // Handle SW1 (PTC3)
        if (interruptFlags & (1 << 3)) {
            if (!(PTC->PDIR & (1 << 3))) { // Falling edge (button pressed)
                sw1_pressed_state = true;  // Set pressed state
                sw1_hold_time = 0;         // Reset hold time
            } else { // Rising edge (button released)
                sw1_pressed_state = false; // Clear pressed state
                sw1_pressed = 1;           // Set flag for processing
            }
        }

        // Handle SW3 (PTC12)
        if (interruptFlags & (1 << 12)) {
            if (!(PTC->PDIR & (1 << 12))) { // Falling edge (button pressed)
                sw3_pressed_state = true;
                sw3_hold_time = 0;
            } else { // Rising edge (button released)
                sw3_pressed_state = false;
                sw3_pressed = 1;
            }
        }
    } else {
        countInterrupt = true;
    }
}

void GPIO_Init(void) {
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;

    // Configure SW1 and SW3
    PORTC->PCR[3] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK | PORT_PCR_IRQC(0b1011); // Interrupt on both edges
    PORTC->PCR[12] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK | PORT_PCR_IRQC(0b1011); // Interrupt on both edges

    PTC->PDDR &= ~((1 << 3) | (1 << 12)); // Set as input
}

void Enable_Interrupts(void) {
    NVIC_EnableIRQ(PORTC_PORTD_IRQn);
    NVIC_EnableIRQ(UART0_IRQn);
    __enable_irq();
}

void init_UART0_with_interrupt(void) {
    SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
    SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;

    PORTA->PCR[UART0_RX_PIN] = PORT_PCR_MUX(2);
    PORTA->PCR[UART0_TX_PIN] = PORT_PCR_MUX(2);

    uint32_t uartClkFreq = CLOCK_GetFreq(kCLOCK_CoreSysClk);
    uint16_t sbr = uartClkFreq / (9600 * 16);

    UART0->BDH = (sbr >> 8) & UART_BDH_SBR_MASK;
    UART0->BDL = (sbr & UART_BDL_SBR_MASK);

    UART0->C1 = 0x00;
    UART0->C2 = UART_C2_TE_MASK | UART_C2_RE_MASK | UART_C2_RIE_MASK;
}

void UART_SendByte(UART_Type *base, uint8_t data) {
    while (!(base->S1 & UART_S1_TDRE_MASK)); // Wait until transmission is ready
    base->D = data; // Send byte
}

void UART_SendString(UART_Type *base, const char *str) {
    while (*str != '\0') { // Iterate through each character of the string until the null terminator is reached
        UART_SendByte(base, *str); // Send each character via UART
        str++; // Move to the next character
    }
    while (!(base->S1 & UART_S1_TC_MASK)); // Wait for transmission to complete
}

void PIT_Init_NEW(void) {
    // Enable PIT clock
    SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;

    // Enable PIT module
    PIT->MCR = 0x00; // Enable PIT timer

    // Calculate load value for a 1-second interval
    uint32_t load_value = (PIT_SOURCE_CLOCK / 200) - 1; // Core clock determines the interval
    PIT->CHANNEL[PIT_CHANNEL].LDVAL = load_value;

    // Enable timer and interrupt
    PIT->CHANNEL[PIT_CHANNEL].TCTRL = PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;

    // Enable PIT interrupt in NVIC
    NVIC_EnableIRQ(PIT_IRQn);
}

void PIT_IRQHandler(void) {
    // Check interrupt flag
    if (PIT->CHANNEL[PIT_CHANNEL].TFLG & PIT_TFLG_TIF_MASK) {
        PIT->CHANNEL[PIT_CHANNEL].TFLG = PIT_TFLG_TIF_MASK; // Clear interrupt flag
        static uint16_t transfer_counter = 0;
        tick_counter++;
        transfer_counter++;
        if (sw1_pressed_state) {
            sw1_hold_time++;
        }
        if (sw3_pressed_state) {
            sw3_hold_time++;
        }
        if (transfer_counter >= 3) {
            transfer_counter = 0;
            transfer = 1;
        }
        // Update time (keep the existing logic)
        if (tick_counter >= 100 && lcdFlag == true) {
            tick_counter = 0;
            seconds++;
            if (seconds == 60) {
                seconds = 0;
                minutes++;
                if (minutes == 60) {
                    minutes = 0;
                }
            }

            if (seconds == secondsThreshold && minutes == minutesThreshold) {
                seconds = 0;
                minutes = 0;
            }
            LCD_DisplayTime(minutes, seconds);
        }
    }
}

void processButtonLogic(void) {
    // If SW1 is pressed
    if (sw1_pressed) {
        if (sw1_hold_time < 50) { // Held for less than 500ms
            UART_SendString((UART_Type *)UART0, "A\n");
            tick_counter = 0;
            PIT_Reload((PIT_SOURCE_CLOCK / 200) - 1);
            minutes = 0;
            seconds = 0;
            lcdFlag = true;
            playFlag = true;
        } else { // Held for more than 500ms
            UART_SendString((UART_Type *)UART0, "C\n");
            PIT_Reload(storeCounterValue);
            lcdFlag = true;
            pauseFlag = false;
            playFlag = true;
        }
        sw1_pressed = 0; // Reset flag
    }

    // If SW3 is pressed
    if (sw3_pressed) {
        if (sw3_hold_time < 50) { // Held for less than 500ms
            UART_SendString((UART_Type *)UART0, "B\n");
            tick_counter = 0;
            PIT_Reload((PIT_SOURCE_CLOCK / 200) - 1);
            minutes = 0;
            seconds = 0;
            lcdFlag = true;
            playFlag = true;
        } else { // Held for more than 500ms
            UART_SendString((UART_Type *)UART0, "D\n");
            storeCounterValue = PIT->CHANNEL[PIT_CHANNEL].LDVAL;
            lcdFlag = false;
            pauseFlag = true;
            playFlag = false;
        }
        sw3_pressed = 0; // Reset flag
    }
}

void Send_ADC_Value(UART_Type *base, uint16_t adc_value) {
    char buffer[10]; // Create a string large enough to hold the ADC value (max 5 digits) and null terminator

    // Convert the ADC value from integer to string
    sprintf(buffer, "%03u\n", adc_value); // Use %u to convert an unsigned integer to a string

    // Send the string via UART
    UART_SendString(base, buffer);
}

void handleADC() {
    ADC16_SetChannelConfig(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP, &adc16ChannelConfigStruct);

    // Wait for conversion to complete
    while (0U == (kADC16_ChannelConversionDoneFlag &
                  ADC16_GetChannelStatusFlags(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP))) {
    }

    // Get the ADC value
    adcValue = ADC16_GetChannelConversionValue(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP);
    if (abs(adcValueOld - adcValue) > 2 * 32) {
        Send_ADC_Value((UART_Type *)UART0, adcValue / 32);
    }else if(adcValue/32<2){
    	Send_ADC_Value((UART_Type *)UART0, 0);
    }
    else if(adcValue/32>126){
    	Send_ADC_Value((UART_Type *)UART0, 128);
    }
}

void initADC() {
    BOARD_InitPins();                         // Configure pins
    PORT_SetPinMux(PORTE, 22U, kPORT_PinDisabledOrAnalog); // Use PTE22 for ADC
    BOARD_BootClockRUN();                     // Configure clock

    /* Configure ADC */
    ADC16_GetDefaultConfig(&adc16ConfigStruct);
    adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceVref; // VREFH = 3.3V
    adc16ConfigStruct.resolution = kADC16_ResolutionSE12Bit;                      // 12-bit resolution
    ADC16_Init(DEMO_ADC16_BASE, &adc16ConfigStruct);
    ADC16_EnableHardwareTrigger(DEMO_ADC16_BASE, false);                          // Use software trigger
    adc16ChannelConfigStruct.channelNumber = DEMO_ADC16_USER_CHANNEL;             // PTE22 (ADC0_SE3)
    adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false;
}

void PIT_Reload(uint32_t newLoadValue) {
    // Disable PIT interrupts before changing LDVAL
    PIT->CHANNEL[PIT_CHANNEL].TCTRL &= ~PIT_TCTRL_TIE_MASK; // Disable PIT interrupts

    // Check PIT status to ensure no changes while counting down
    if (PIT->CHANNEL[PIT_CHANNEL].TFLG & PIT_TFLG_TIF_MASK) {
        PIT->CHANNEL[PIT_CHANNEL].TFLG = PIT_TFLG_TIF_MASK; // Clear interrupt flag if set
    }

    // Update LDVAL with the new value
    PIT->CHANNEL[PIT_CHANNEL].LDVAL = newLoadValue;

    // Re-enable PIT interrupts after changing LDVAL
    PIT->CHANNEL[PIT_CHANNEL].TCTRL |= PIT_TCTRL_TIE_MASK; // Enable PIT interrupts

    // Optional: Reset or adjust additional values here if needed
}


