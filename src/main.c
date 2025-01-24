/* src/main.c */

#include <stm32f722xx.h>

/*
 * USER-BUTTON PC13
 * BLUE-LED PB7
 */
void SystemInit(void); 

void delay(volatile uint32_t count) {
  while (count--)
    ;

}

void LED_INIT(void);
void GPIO_Init(void);
void EXTI_Init(void);

int main(void) {
 
  void SystemInit(void); 
  
  GPIO_Init();
  EXTI_Init();

  //LED_INIT();
  while (1) {
    // LED Toggle
   // GPIOB->ODR ^= (1U << 0);

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

void GPIO_Init(void) {
    // Clock enable for GPIOB (Blue LED on PB7)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    // Set PB7 as output
    GPIOB->MODER &= ~(3 << (7 * 2)); 
    GPIOB->MODER |= (1 << (7 * 2));  

    // GPIOC clock enable (Buton PC13'te)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    // SET PC13 as a input
    GPIOC->MODER &= ~(3 << (13 * 2)); =
}

void EXTI_Init(void) {
    // SYSCFG clock enable
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // Connect PC13 to EXTI13
    SYSCFG->EXTICR[3] &= ~(0xF << 4); 
    SYSCFG->EXTICR[3] |= (2 << 4);    // Connect EXTI13 to GPIOC

    // Set EXTI13 for falling edge triggering
    EXTI->FTSR |= EXTI_FTSR_TR13;

    // Enable EXTI13 interrupt
    EXTI->IMR |= EXTI_IMR_MR13;

    // Enable EXTI15_10 interrupt in NVIC
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI15_10_IRQHandler(void) {
   
    if (EXTI->PR & EXTI_PR_PR13) {
        // Clear interrupt flag
        EXTI->PR |= EXTI_PR_PR13;

        // Toggle blue LED
        GPIOB->ODR ^= (1 << 7);
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
