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
    // GPIOB için saat etkinleştirme (Mavi LED PB7'de)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    // PB7'yi çıkış olarak ayarla
    GPIOB->MODER &= ~(3 << (7 * 2)); // MODER7'i sıfırla
    GPIOB->MODER |= (1 << (7 * 2));  // MODER7'i output olarak ayarla

    // GPIOC için saat etkinleştirme (Buton PC13'te)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    // PC13'ü giriş olarak ayarla
    GPIOC->MODER &= ~(3 << (13 * 2)); // MODER13'ü sıfırla
}

void EXTI_Init(void) {
    // SYSCFG saat etkinleştirme
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // PC13'ü EXTI13'e bağla
    SYSCFG->EXTICR[3] &= ~(0xF << 4); // EXTI13'ü sıfırla
    SYSCFG->EXTICR[3] |= (2 << 4);    // EXTI13'ü GPIOC'ye bağla

    // EXTI13'ü düşen kenar tetikleme için ayarla
    EXTI->FTSR |= EXTI_FTSR_TR13;

    // EXTI13 kesmesini etkinleştir
    EXTI->IMR |= EXTI_IMR_MR13;

    // NVIC'de EXTI15_10 kesmesini etkinleştir
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI15_10_IRQHandler(void) {
    // EXTI13 kesmesi kontrolü
    if (EXTI->PR & EXTI_PR_PR13) {
        // Kesme bayrağını temizle
        EXTI->PR |= EXTI_PR_PR13;

        // Mavi LED'i toggle et
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
