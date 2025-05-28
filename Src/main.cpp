// main.cpp
#include "main.hpp"
#include "stm32f4xx_hal.h"
#include "UartLink.hpp"
#include "DCMotor.hpp"
#include "message.hpp"

extern UART_HandleTypeDef huart2;
UartLink uart_link(&huart2, 0);

extern TIM_HandleTypeDef htim1; // for pwm leg
extern TIM_HandleTypeDef htim2; // for pwm arm
extern TIM_HandleTypeDef htim3; // for pwm servo
extern TIM_HandleTypeDef htim5; // 割り込み(20Hz)
extern TIM_HandleTypeDef htim6; // 割り込み(100Hz)
extern TIM_HandleTypeDef htim7; // 割り込み(1000Hz)

DCMotor motor1(&htim1, TIM_CHANNEL_1, GPIOB, GPIO_PIN_1, true, 0.5f);
DCMotor motor2(&htim1, TIM_CHANNEL_2, GPIOB, GPIO_PIN_4, true, 0.5f);
DCMotor motor3(&htim1, TIM_CHANNEL_3, GPIOB, GPIO_PIN_15, true, 0.5f);

void setup()
{
    // ここに初期化処理を書く
}

void loop()
{
    // ここに繰り返し処理を書く
}
