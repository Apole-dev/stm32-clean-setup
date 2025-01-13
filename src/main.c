/* src/main.c */

#include <stm32f722xx.h>

void SystemInit(void); 

void delay(volatile uint32_t count) {
  while (count--)
    ;

}

void LED_INIT(void);

int main(void) {
 
  void SystemInit(void); 
  
  LED_INIT();

  while (1) {
    // LED Toggle
    GPIOB->ODR ^= (1U << 0);
    delay(1000000);
  }
}

void LED_INIT(void){

  //Clock Enable
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

  /*
   * MODE SET */
  
  GPIOB->MODER &= ~(3U << (0*2));
  GPIOB->MODER |= (1U << (0*2));

}

void NMI_Handler(void) {
  while (1)
    ;
}

void HardFault_Handler(void) {
  while (1)
    ;
}
