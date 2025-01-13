/* src/main.c */

#include <stm32f722xx.h>

void SystemInit(void); // Fon:ksiyon deklarasyonu
// Basit gecikme fonksiyonu
void delay(volatile uint32_t count) {
  while (count--)
    ;
}

int main(void) {
  //
  void SystemInit(void); // Fonksiyon deklarasyonu
  // LD1 LED'i (PB0)
  // RCC - Port B clock enable
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

  // GPIO B Pin 0 çıkış olarak ayarla
  GPIOB->MODER &= ~(3U << (0 * 2));
  GPIOB->MODER |= (1U << (0 * 2));


  while (1) {
    // LED Toggle
    GPIOB->ODR ^= (1U << 0);
    delay(1000000);
  }
}

// Kesme işleyicileri
void NMI_Handler(void) {
  while (1)
    ;
}

void HardFault_Handler(void) {
  while (1)
    ;
}
