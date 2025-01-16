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

#define RX_BUFFER_SIZE 4
#define UART0_RX_PIN 1U  // PTA1
#define UART0_TX_PIN 2U  // PTA2
#define PIT_CHANNEL 0
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_CoreSysClk)

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
volatile bool pause_flag = 1;
volatile bool play_flag = false;

void GPIO_Init(void);
void Enable_Interrupts(void);
void UART0_IRQHandler(void);
void init_UART0_with_interrupt(void);
void PIT_Init_NEW(void);
void PIT_IRQHandler(void);
void UART_SendByte(UART_Type *base, uint8_t data);
void UART_SendString(UART_Type *base, const char *str);
void processButtonLogic();

int main(void) {
    BOARD_InitPins();
    BOARD_BootClockRUN();
    init_UART0_with_interrupt();
    LCD_Init();
    GPIO_Init();
    Enable_Interrupts();
    PIT_Init_NEW();
    UART_SendString((UART_Type *)UART0, "System Initialized\n");
    while (1) {
        // Xử lý khi có dữ liệu từ UART
        if (pause_flag == 1) {
        // Dừng timer bằng cách tắt PIT (Peripheral Interrupt Timer)
        PIT->CHANNEL[PIT_CHANNEL].TCTRL &= ~PIT_TCTRL_TEN_MASK; // Tắt timer
        pause_flag = 0; // Reset cờ pause để tránh xử lý lại
    }

    // Nếu play_flag được đặt, tiếp tục timer
    if (play_flag == 1) {
        // Tiếp tục timer bằng cách bật PIT
        PIT->CHANNEL[PIT_CHANNEL].TCTRL |= PIT_TCTRL_TEN_MASK; // Bật timer
        play_flag = 0; // Reset cờ play để tránh xử lý lại
    }
        processButtonLogic();
    }
}


void UART0_IRQHandler(void) {
    if (UART0->S1 & UART_S1_RDRF_MASK) { // Kiểm tra cờ nhận dữ liệu (RDRF)
        char received_byte = UART0->D; // Đọc byte từ UART

        if (rx_index < RX_BUFFER_SIZE && received_byte != '\0') {
            rx_buffer[rx_index++] = received_byte; // Lưu byte nhận được vào bộ đệm
        }

        if (rx_index == 2 && (rx_buffer[0] == 'P' && (rx_buffer[1] == 'A' || rx_buffer[1] == 'L'))) {
            // Kiểm tra trường hợp nhận 2 ký tự "PA" hoặc "PL"
            if (rx_buffer[1] == 'A') {
                pause_flag = 1; // PAUSE
                play_flag = 0;
            } else if (rx_buffer[1] == 'L') {
                play_flag = 1; // PLAY
                pause_flag = 0;
            }
            rx_index = 0; // Reset bộ đệm
            memset(rx_buffer, 0, RX_BUFFER_SIZE); // Xóa dữ liệu trong bộ đệm
        } else if (rx_index == RX_BUFFER_SIZE || received_byte == '\n') {
            // Kiểm tra trường hợp nhận đủ 4 ký tự
            if (rx_index == 4) {
                minutes = 0;
                seconds = 0;
                play_flag;
            }
            rx_index = 0; // Reset bộ đệm
            memset(rx_buffer, 0, RX_BUFFER_SIZE); // Xóa dữ liệu trong bộ đệm
        }
    }
}

void PORTC_PORTD_IRQHandler(void) {
    // Xử lý SW1 (PTC3)
    if (PORTC->ISFR & (1 << 3)) {
        if (!(PTC->PDIR & (1 << 3))) { // Cạnh xuống (nhấn nút)
            sw1_pressed_state = true;  // Đặt trạng thái đang nhấn
            sw1_hold_time = 0;         // Reset thời gian giữ nút
        } else { // Cạnh lên (thả nút)
            sw1_pressed_state = false; // Bỏ trạng thái nhấn
            sw1_pressed = 1;           // Đặt cờ xử lý
        }
        PORTC->ISFR |= (1 << 3); // Xóa cờ ngắt
    }

    // Xử lý SW3 (PTC12)
    if (PORTC->ISFR & (1 << 12)) {
        if (!(PTC->PDIR & (1 << 12))) { // Cạnh xuống (nhấn nút)
            sw3_pressed_state = true;
            sw3_hold_time = 0;
        } else { // Cạnh lên (thả nút)
            sw3_pressed_state = false;
            sw3_pressed = 1;
        }
        PORTC->ISFR |= (1 << 12); // Xóa cờ ngắt
    }
}


void GPIO_Init(void) {
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;

    // Cấu hình SW1 và SW3
    PORTC->PCR[3] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK | PORT_PCR_IRQC(0b1011); // Ngắt cạnh lên & xuống
    PORTC->PCR[12] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK | PORT_PCR_IRQC(0b1011); // Ngắt cạnh lên & xuống


    PTC->PDDR &= ~((1 << 3) | (1 << 12));
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
    while (!(base->S1 & UART_S1_TDRE_MASK)); // Chờ khi bộ truyền (TX) sẵn sàng
    base->D = data; // Gửi byte
}

void UART_SendString(UART_Type *base, const char *str) {
    while (*str != '\0') { // Lặp qua từng ký tự của chuỗi cho đến khi gặp ký tự null '\0'
        UART_SendByte(base, *str); // Gửi từng ký tự qua UART
        str++; // Chuyển sang ký tự tiếp theo
    }
    while (!(base->S1&UART_S1_TC_MASK));
}

void PIT_Init_NEW(void)
{
    // Enable PIT clock
	 SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;

    // Enable PIT module
    PIT->MCR = 0x00; // Enable PIT timer

    // Calculate load value for 1-second interval
    uint32_t load_value = (PIT_SOURCE_CLOCK / 200) - 1; // Core clock determines the interval
    PIT->CHANNEL[PIT_CHANNEL].LDVAL = load_value;

    // Enable timer and interrupt
    PIT->CHANNEL[PIT_CHANNEL].TCTRL = PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;

    // Enable PIT interrupt in NVIC
    NVIC_EnableIRQ(PIT_IRQn);
}

void PIT_IRQHandler(void) {
    // Kiểm tra cờ ngắt
    if (PIT->CHANNEL[PIT_CHANNEL].TFLG & PIT_TFLG_TIF_MASK) {
        PIT->CHANNEL[PIT_CHANNEL].TFLG = PIT_TFLG_TIF_MASK; // Xóa cờ ngắt

        static uint16_t tick_counter = 0; // Bộ đếm tick để đo 1 giây
        tick_counter++;

        if (sw1_pressed_state) {
                sw1_hold_time++;
            }
            if (sw3_pressed_state) {
                sw3_hold_time++;
            }

        // Cập nhật thời gian (giữ nguyên logic hiện tại)
        if (tick_counter >= 100)
        {
            tick_counter = 0;
            seconds++;
            if (seconds == 60) {
                seconds = 0;
                minutes++;
                if (minutes == 60) {
                    minutes = 0;
                }
            }

            LCD_DisplayTime( minutes, seconds);
        }
    }
}

void processButtonLogic(void) {
	if (sw1_pressed) {
        if (sw1_hold_time < 30) { // Giữ dưới 300ms
            UART_SendByte(UART0, '1');
            minutes = 0;
            seconds = 0;
            play_flag = 1;
        } else if (sw1_hold_time < 100) { // Giữ từ 300ms đến 1s
            UART_SendByte(UART0, '2');
        } else { // Giữ trên 1s
            UART_SendByte(UART0, '3');
            play_flag = 1;
        }
        sw1_pressed = 0; // Reset cờ
    }

    // Nếu SW3 được nhấn
    if (sw3_pressed) {
        if (sw3_hold_time < 30) { // Giữ dưới 300ms
            UART_SendByte(UART0, '4');
            minutes = 0;
            seconds = 0;
            play_flag = 1;
        } else if (sw3_hold_time < 100) { // Giữ từ 300ms đến 1s
            UART_SendByte(UART0, '5');
        } else { // Giữ trên 1s
            UART_SendByte(UART0, '6');
            pause_flag = 1;
        }
        sw3_pressed = 0; // Reset cờ
    }
}
