#include "stm32f0xx.h"

#define PRESCALER       0x5DBF;         
#define AUTO_RELOAD     0x3EF;         
#define RESET           0x0;

//--------- LED INI ----------
void led_ini() {
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
  GPIOC->MODER |= (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0);
  GPIOC->OTYPER = 0;
  GPIOC->OSPEEDR = 0;
}

//--------- TIMER INI ----------
void timer_ini(){
  RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
  TIM6->ARR = AUTO_RELOAD;                      
  TIM6->PSC = PRESCALER;                     
  TIM6->DIER = TIM_DIER_UIE;
  TIM6->CR1 = TIM_CR1_UDIS;
  NVIC_EnableIRQ(TIM6_DAC_IRQn); 
  TIM6->CR1 |= TIM_CR1_CEN;       
}


void TIM6_IRQHandler(void) {
  static uint8_t Flag = 0;
          
  if (TIM6->SR) {
    Flag = ~Flag;
      if (Flag) { 
  		GPIOC->ODR |= GPIO_ODR_8;
  		GPIOC->ODR |= GPIO_ODR_9;
  	  }
  	  else {
  		GPIOC->ODR |= GPIO_BSRR_BR_8;
  		GPIOC->ODR |= GPIO_BSRR_BR_9;
      }
      TIM6->SR = RESET;
      }
  }

int main(void) {
  timer_ini();
  led_ini();
  
	while(1){
  }
}

        
