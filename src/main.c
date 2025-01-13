/* src/main.c */

#include <stm32f722xx.h>

void SystemInit(void); 

void delay(volatile uint32_t count) {
  while (count--)
    ;
}

int main(void) {
  //
  void SystemInit(void); 
  // LD1 LED'i (PB0)
  // RCC - Port B clock enable
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

  GPIOB->MODER &= ~(3U << (0 * 2));
  GPIOB->MODER |= (1U << (0 * 2));


  while (1) {
    // LED Toggle
    GPIOB->ODR ^= (1U << 0);
    delay(1000000);
  }
}

void NMI_Handler(void) {
  while (1)
    ;
}

void HardFault_Handler(void) {
  while (1)
    ;
}
