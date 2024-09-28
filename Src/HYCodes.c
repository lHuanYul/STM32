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
int freq;
int timflag;
int test;
/* Init ----------------------------------------------------------------------*/
void HYCodes_Init(void){
    freq = MNote_C4;
    test = 87;
}
/* Main ----------------------------------------------------------------------*/
void HYCodes_Main(void){
    HAL_TIM_Base_Start_IT(&htim1);
    HAL_TIM_PWM_Start_IT(&htim2,TIM_CHANNEL_1);
    int sheet[] = {MNote_C4, MNote_D4, MNote_E4, MNote_F4, MNote_G4, MNote_A4, MNote_B4};
    while(true){
        for(int i = 0; i < 7; i+=1){
            /*GPIOB->ODR = (15<<i);
            timflag = 1;
            while(timflag) HAL_Delay(1);*/
            freq = sheet[i];
            uint32_t temp = 1000000 / freq;
            TIM2->CNT = 0;
            TIM2->ARR = temp;
            TIM2->CCR1 = temp / 2;
            HAL_Delay(200);
        }
    }
}
/* Interrupt -----------------------------------------------------------------*/
void HYCodes_ItButtonPC3(void){
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    if (TIM2->CR1 & TIM_CR1_CEN) {
        HAL_TIM_PWM_Stop_IT(&htim2,TIM_CHANNEL_1);
    } else {
        HAL_TIM_PWM_Start_IT(&htim2,TIM_CHANNEL_1);
    }
}
void HYCodes_ItTim1(void){
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
void HYCodes_ItTim2(void){

}
