#include "stm32f0xx.h"

#define PRESCALER 23999;         // делитель 24 000 -1
#define AUTO_RELOAD 500;          // 1000 тактов
#define RESET 0x0;

  //--------- LED INI ----------
  void led_ini() 
  {
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
  GPIOC->MODER |= (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0);
	GPIOC->OTYPER = 0;
	GPIOC->OSPEEDR = 0;
	}

  //--------- TIMER INI ----------
  void timer_ini()
  {
  RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
  TIM6->PSC = PRESCALER;
  TIM6->ARR = AUTO_RELOAD; 
  TIM6->DIER |= TIM_DIER_UIE;
  NVIC_EnableIRQ(TIM6_DAC_IRQn);
  TIM6->CR1 |= TIM_CR1_CEN;         
  }

  void TIM6_DAC_IRQHandler(void)
  {
    if ((GPIOC->ODR & GPIO_ODR_8)&(GPIOC->ODR & GPIO_ODR_9)) 
    { 
      GPIOC->ODR |= GPIO_ODR_8;
      GPIOC->ODR |= GPIO_ODR_9;
    }
    else 
    {
      GPIOC->BRR |= GPIO_BRR_BR_8;  // 0x100
      GPIOC->BRR |= GPIO_BRR_BR_9;  // 0x200
    }
    TIM6->SR &= ~TIM_SR_UIF;
  }

  int main(void)
  {  
    timer_ini();
    led_ini();        

    while(1)
    {
    }
  }

        
