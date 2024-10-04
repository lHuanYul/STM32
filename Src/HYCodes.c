/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    HYCodes.c
  * @brief   HY Codes file
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"
#include "tim.h"
/* Global Var ----------------------------------------------------------------*/
int frequency = MNote_C4;
int duty_ratio = 50;
int selecter[6];
int sheet[6];
int timflag;
int test;
/* Init ----------------------------------------------------------------------*/
void HYCodes_Init(void){
    frequency = MNote_C4;
    duty_ratio = 50;
    test = 87;
}
/* Main ----------------------------------------------------------------------*/
void HYCodes_Main(void){
    HAL_TIM_Base_Start_IT(&htim1);
    int music_sheet[] = {MNote_C4, MNote_D4, MNote_E4, MNote_F4, MNote_G4, MNote_A4, MNote_B4};
    while(true){
        for(int i = 0; i < 7; i+=1){
            /*
            GPIOB->ODR = (15<<i);
            timflag = 1;
            while(timflag) HAL_Delay(1);
            */

            frequency = music_sheet[i];
            uint32_t frequency_c1 = 1000000 / frequency;
            TIM2->CNT = 0;
            TIM2->ARR = frequency_c1;
            TIM2->CCR1 = frequency_c1 * duty_ratio / 100;
            HAL_Delay(200);
        }
        /*uint16_t input = (GPIOB->IDR >> 6) & 0x0007;
        uint16_t output = GPIOB->ODR & 0xFFC0;
        output |= Motor(input);
        GPIOB->ODR = output;*/
    }
}
/* Interrupt -----------------------------------------------------------------*/
void HYCodes_ItButtonPC13(void){
    //HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

    if (TIM2->CR1 & TIM_CR1_CEN) {
        HAL_TIM_PWM_Stop_IT(&htim2,TIM_CHANNEL_1);
        //TIM2->CR1 &= ~TIM_CR1_CEN;

    } else {
        HAL_TIM_PWM_Start_IT(&htim2,TIM_CHANNEL_1);
        //TIM2->CR1 |= TIM_CR1_CEN;
    }
    
}
void HYCodes_ItTim1(void){
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
void HYCodes_ItTim2(void){

}
/* Function ------------------------------------------------------------------*/
uint16_t Motor(uint16_t input){
    /*
    uint16_t input = (GPIOB->IDR >> 6) & 0x0007;
    uint16_t output = GPIOB->ODR & 0xFFC0;
    output |= Motor(input);
    GPIOB->ODR = output;
    */
    switch (input)
    {
    case 0:
        return 0x30;
    case 1:
        return 0x18;
    case 2:
        return 0x0C;
    case 3:
        return 0x06;
    case 4:
        return 0x03;
    case 5:
        return 0x21;
    default:
        return 0x00;
    }
}
