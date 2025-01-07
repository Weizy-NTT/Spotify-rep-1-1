#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_uart.h"
#include "pin_mux.h"
#include "fsl_slcd.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void GPIO_Init(void);              // Initialize GPIO for switches
void Enable_Interrupts(void);      // Enable interrupts
void UART_Init_new(void);          // Custom UART initialization function
void UART_SendString(UART_Type *base, const char *str); // Function to send a string via UART
uint16_t UART_ReceiveString(char *buffer, uint16_t length);
void LCD_Init_new(void);           // Initialize the LCD
void LCD_DisplayString(const char *str); // Display a string on the LCD
void SLCD_ClearDisplay(void);
/*******************************************************************************
 * Variables
 ******************************************************************************/
#define TX_BUFFER_SIZE 64 // Size of TX buffer
#define RX_BUFFER_SIZE 64 // Size of RX buffer

volatile char txBuffer[TX_BUFFER_SIZE]; // Buffer for transmitting data
volatile uint16_t txWriteIndex = 0;    // Write pointer for TX buffer
volatile uint16_t txReadIndex = 0;     // Read pointer for TX buffer
volatile uint16_t txCount = 0;         // Number of bytes in TX buffer

volatile char rxBuffer[RX_BUFFER_SIZE]; // Buffer for receiving data
volatile uint16_t rxWriteIndex = 0;     // Write pointer for RX buffer
volatile uint16_t rxReadIndex = 0;      // Read pointer for RX buffer
volatile uint16_t rxCount = 0;          // Number of bytes in RX buffer


volatile uint8_t sw1_pressed = 0; // Flag to indicate SW1 is pressed
volatile uint8_t sw3_pressed = 0; // Flag to indicate SW3 is pressed

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    /* Initialize board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    UART_Init_new(); // Initialize UART with interrupts

    PRINTF("Program started.\r\n");

    // Initialize GPIO and enable interrupts
    GPIO_Init();
    Enable_Interrupts();

    char receivedData[64];

    while (1)
    {
        // Handle SW1 press
        if (sw1_pressed)
        {
            UART_SendString((UART_Type *)UART0, "SW1 pressed!\r\n");
            sw1_pressed = 0; // Clear flag
        }

        // Handle SW3 press
        if (sw3_pressed)
        {
            UART_SendString((UART_Type *)UART0, "SW3 pressed!\r\n");
            sw3_pressed = 0; // Clear flag
        }

        // Handle received data
        uint16_t receivedLength = UART_ReceiveString(receivedData, sizeof(receivedData) - 1);
        if (receivedLength > 0)
        {
            receivedData[receivedLength] = '\0'; // Null-terminate the string
            PRINTF("Received: %s\r\n", receivedData); // Print received data to debug console
        }
    }
}

/*!
 * @brief Initialize GPIO for switches
 */
void GPIO_Init(void)
{
    // Enable clock for Port C
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;

    // Configure SW1 (PTC3) and SW3 (PTC12) as input with pull-up resistors and falling-edge interrupts
    PORTC->PCR[3] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK | PORT_PCR_IRQC(0b1010);
    PORTC->PCR[12] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK | PORT_PCR_IRQC(0b1010);

    // Configure PTC3 and PTC12 as input
    PTC->PDDR &= ~((1 << 3) | (1 << 12));
}

/*!
 * @brief Enable interrupts for switches
 */
void Enable_Interrupts(void)
{
    NVIC_EnableIRQ(PORTC_PORTD_IRQn); // Enable interrupts for PORTC and PORTD
    __enable_irq();                   // Enable global interrupts
}

/*!
 * @brief PORTC interrupt handler
 */
void PORTC_PORTD_IRQHandler(void)
{
    // Check if the interrupt is from SW1 (PTC3)
    if (PORTC->ISFR & (1 << 3))
    {
        sw1_pressed = 1;         // Set flag to indicate SW1 is pressed
        PORTC->ISFR |= (1 << 3); // Clear interrupt flag for PTC3
    }

    // Check if the interrupt is from SW3 (PTC12)
    if (PORTC->ISFR & (1 << 12))
    {
        sw3_pressed = 1;         // Set flag to indicate SW3 is pressed
        PORTC->ISFR |= (1 << 12); // Clear interrupt flag for PTC12
    }
}

/*!
 * @brief Initialize UART
 */
/*!
 * @brief Initialize UART with interrupt-driven TX and RX
 */
void UART_Init_new(void)
{
    uart_config_t config;

    // Get default UART configuration
    UART_GetDefaultConfig(&config);
    config.baudRate_Bps = 9600; // Set baud rate to 9600
    config.enableTx = true;     // Enable UART transmission
    config.enableRx = true;     // Enable UART reception

    // Initialize UART0 with the given configuration and system clock frequency
    UART_Init((UART_Type *)UART0, &config, CLOCK_GetFreq(kCLOCK_CoreSysClk));

    // Enable UART TX and RX interrupts
    UART_EnableInterrupts((UART_Type *)UART0,
                          kUART_TxDataRegEmptyInterruptEnable | // TX interrupt
                          kUART_RxDataRegFullInterruptEnable);  // RX interrupt

    NVIC_EnableIRQ(UART0_IRQn); // Enable UART0 interrupt in NVIC
}


/*!
 * @brief Send a string via UART
 * @param base UART base address
 * @param str Pointer to the string to be sent
 */
void UART_SendString(UART_Type *base, const char *str)
{
    while (*str)
    {
        // Wait if buffer is full
        while (txCount >= TX_BUFFER_SIZE)
        {
        }

        // Add character to TX buffer
        txBuffer[txWriteIndex] = *str++;
        txWriteIndex = (txWriteIndex + 1) % TX_BUFFER_SIZE;

        // Update TX buffer count
        __disable_irq();
        txCount++;
        __enable_irq();

        // Enable TX interrupt to start sending
        UART_EnableInterrupts(base, kUART_TxDataRegEmptyInterruptEnable);
    }
}


/*!
 * @brief Get a received string from the UART RX buffer
 * @param buffer Pointer to a buffer to store the string
 * @param length Maximum number of bytes to read
 * @return Number of bytes read
 */
uint16_t UART_ReceiveString(char *buffer, uint16_t length)
{
    uint16_t bytesRead = 0;

    while (rxCount > 0 && bytesRead < length)
    {
        buffer[bytesRead++] = rxBuffer[rxReadIndex];
        rxReadIndex = (rxReadIndex + 1) % RX_BUFFER_SIZE;

        __disable_irq();
        rxCount--;
        __enable_irq();
    }

    return bytesRead;
}

/*!
 * @brief UART0 interrupt handler
 */
void UART0_IRQHandler(void)
{
    UART_Type *base = (UART_Type *)UART0;

    // Handle RX interrupt
    if (UART_GetStatusFlags(base) & kUART_RxDataRegFullFlag)
    {
        // Read received byte
        char receivedByte = UART_ReadByte(base);

        // Add to RX buffer
        if (rxCount < RX_BUFFER_SIZE) // Check for buffer overflow
        {
            rxBuffer[rxWriteIndex] = receivedByte;
            rxWriteIndex = (rxWriteIndex + 1) % RX_BUFFER_SIZE;
            rxCount++;
        }
    }

    // Handle TX interrupt
    if ((UART_GetStatusFlags(base) & kUART_TxDataRegEmptyFlag) && txCount > 0)
    {
        // Write next byte from TX buffer
        UART_WriteByte(base, txBuffer[txReadIndex]);
        txReadIndex = (txReadIndex + 1) % TX_BUFFER_SIZE;
        txCount--;

        // If no more data, disable TX interrupt
        if (txCount == 0)
        {
            UART_DisableInterrupts(base, kUART_TxDataRegEmptyInterruptEnable);
        }
    }
}

void SLCD_Init_new(void)
{
    slcd_config_t config;

    // Get default SLCD configuration
    SLCD_GetDefaultConfig(&config);

    // Enable SLCD clock
    CLOCK_EnableClock(kCLOCK_Slcd0);

    // Customize configuration
    config.powerSupply = kSLCD_InternalVll3UseChargePump;
    config.dutyCycle = kSLCD_1Div4DutyCycle; // Example: 1/4 duty cycle for 4 backplanes
    config.lowPowerBehavior = kSLCD_EnabledInWaitStop;

    // Initialize SLCD module
    SLCD_Init(LCD, &config);

    // Enable LCD
    SLCD_StartDisplay(LCD);
}

/*!
 * @brief Clear SLCD display by disabling all segments
 */
void SLCD_ClearDisplay(void)
{
    for (uint8_t i = 0; i < 32; i++) // Adjust for your SLCD pins
    {
        SLCD_SetFrontPlaneSegments(LCD, i, 0x00); // Clear all segments
    }
}

/*!
 * @brief Display a string on the SLCD
 * @param str Pointer to the string to display
 */
void LCD_DisplayString(const char *str)
{
    // Maximum number of characters to display (6 for KL46Z)
    const uint8_t maxDigits = 6;

    // Mapping table for characters to segment patterns (ABCDEFG)
    const uint8_t segmentMap[16] = {
        0b0111111, // '0'
        0b0000110, // '1'
        0b1011011, // '2'
        0b1001111, // '3'
        0b1100110, // '4'
        0b1101101, // '5'
        0b1111101, // '6'
        0b0000111, // '7'
        0b1111111, // '8'
        0b1101111, // '9'
        0b1110111, // 'A'
        0b1111100, // 'B'
        0b0111001, // 'C'
        0b1011110, // 'D'
        0b1111001, // 'E'
        0b1110001, // 'F'
    };

    // Clear the SLCD display
    SLCD_ClearDisplay();

    for (uint8_t i = 0; i < maxDigits; i++)
    {
        if (str[i] == '\0')
        {
            break; // End of string
        }

        uint8_t charPattern = 0b0000000; // Default pattern for unsupported characters

        // Map character to segment pattern
        if (str[i] >= '0' && str[i] <= '9')
        {
            charPattern = segmentMap[str[i] - '0']; // Map '0'-'9'
        }
        else if (str[i] >= 'A' && str[i] <= 'F')
        {
            charPattern = segmentMap[str[i] - 'A' + 10]; // Map 'A'-'F'
        }

        // Set the segment pattern for the current digit (adjust pin configuration as necessary)
        SLCD_SetFrontPlaneSegments(LCD, i, charPattern);
    }
}
