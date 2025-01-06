#include "port.h"
#include "adc.h"
#include "sim.h"

void ADC_Init(void) {
    // Bật clock cho ADC0 và PORTB
    SIM->SCGC6 |= (1 << 27);  // Bật clock cho ADC0 (bit 27 trong SCGC6)
    SIM->SCGC5 |= (1 << 10);  // Bật clock cho PORTB (bit 10 trong SCGC5)

    // Cấu hình PTB2 làm chức năng ADC (MUX = 0)
    PORTB->PCR[2] &= ~(7 << 8);  // Xóa các bit MUX (10-8)

    // Cấu hình ADC0
    ADC0->CFG1 = (2 << 5)        // Chia tần số ADC clock /4 (ADIV = 2)
               | (1 << 2)        // Độ phân giải 12-bit (MODE = 1)
               | (1 << 4)        // Lấy mẫu dài (ADLSMP = 1)
               | (0 << 0);       // Clock nguồn từ bus clock (ADICLK = 0)

    ADC0->SC2 &= ~(1 << 6);      // Chế độ phần mềm (ADTRG = 0)
}

uint16_t ADC_Read(uint8_t channel) {
    // Chọn channel ADC
    ADC0->SC1[0] = channel;

    // Chờ cho đến khi quá trình chuyển đổi hoàn tất (COCO = 1)
    while (!(ADC0->SC1[0] & (1 << 7)));

    // Trả về giá trị ADC (12-bit)
    return ADC0->R[0];
}