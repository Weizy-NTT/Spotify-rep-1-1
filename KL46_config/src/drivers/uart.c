#include "uart.h"
#include "sim.h" // Cần thiết để định nghĩa SIM và clock
#include "GPIO.h"
#include "port.h"
void UART_Init(UART_Type *uart, uint32_t baud_rate, uint32_t module_clock) {
    uint16_t sbr = module_clock / (baud_rate * 16);

    // Bật clock cho UART và PORTA (cho UART0)
    if (uart == UART0) {
        SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
        SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
        PORTA->PCR[1] = PORT_PCR_MUX(2); // PTA1 RX
        PORTA->PCR[2] = PORT_PCR_MUX(2); // PTA2 TX
    } else if (uart == UART1) {
        SIM->SCGC4 |= SIM_SCGC4_UART1_MASK;
        SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
        PORTC->PCR[3] = PORT_PCR_MUX(3); // PTC3 RX
        PORTC->PCR[4] = PORT_PCR_MUX(3); // PTC4 TX
    }

    // Ghi giá trị SBR
    uart->BDH = (sbr >> 8) & 0x1F;
    uart->BDL = sbr & 0xFF;

    // Bật bộ truyền và nhận
    uart->C2 |= (1 << 3); // TE: Transmitter Enable
    uart->C2 |= (1 << 2); // RE: Receiver Enable
}

void UART_SendChar(UART_Type *uart, char ch) {
    while (!(uart->S1 & (1 << 7))); // Chờ buffer truyền rỗng (TDRE)
    uart->D = ch;
}

char UART_ReceiveChar(UART_Type *uart) {
    while (!(uart->S1 & (1 << 5))); // Chờ dữ liệu sẵn sàng (RDRF)
    return uart->D;
}

void UART_SendString(UART_Type *uart, const char *str) {
    while (*str) {
        UART_SendChar(uart, *str++);
    }
}
