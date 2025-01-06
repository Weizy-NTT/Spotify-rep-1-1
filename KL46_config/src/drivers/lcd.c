#include "lcd.h"
#include "sim.h"

void LCD_Init(void) {
    // Bật clock cho PORTB, PORTE, và LCD module
    SIM_EnableClock(SIM_CLOCK_PORTB);
    SIM_EnableClock(SIM_CLOCK_PORTE);
    SIM_EnableClock(SIM_CLOCK_LCD);

    // Cấu hình các chân PORTB[0-3] làm chức năng LCD (MUX = 0b001)
    for (int i = 0; i <= 3; i++) {
        PORTB->PCR[i] = (PORTB->PCR[i] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(0b001);
    }

    // Cấu hình các chân PORTE[20-23] làm chức năng LCD (MUX = 0b001)
    for (int i = 20; i <= 23; i++) {
        PORTE->PCR[i] = (PORTE->PCR[i] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(0b001);
    }

    // Bật module LCD
    LCD->GCR |= (1<<7);    // Bật LCD
    LCD->GCR |= (1<<23);  // Bật Charge Pump (nguồn cho LCD)
    //LCD->GCR |= LCD_GCR_LADJ(3);     // Tăng độ sáng (Load Adjust)

    // Xóa các thanh ghi WF để đảm bảo LCD ở trạng thái ban đầu
    for (int i = 0; i < 32; i++) {
        LCD->WF[i] = 0;
    }
}

void LCD_Clear(void) {
    // Xóa tất cả các segment trên LCD
    for (int i = 0; i < 32; i++) {
        LCD->WF[i] = 0;
    }
}

void LCD_DisplayChar(uint8_t position, char character) {
    // Bảng ánh xạ ký tự sang segment
    const uint8_t char_map[10] = {
        0x3F, // 0
        0x06, // 1
        0x5B, // 2
        0x4F, // 3
        0x66, // 4
        0x6D, // 5
        0x7D, // 6
        0x07, // 7
        0x7F, // 8
        0x6F  // 9
    };

    if (character >= '0' && character <= '9') {
        LCD->WF[position] = char_map[character - '0'];
    }
}

void LCD_DisplayString(const char *str) {
    uint8_t position = 0;
    while (*str && position < 8) {
        LCD_DisplayChar(position, *str);
        str++;
        position++;
    }
}
