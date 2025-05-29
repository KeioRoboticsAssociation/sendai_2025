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

// Callback function for motor control
void motor_control_callback(float val1, float val2, float val3)
{
    motor1.setDuty(val1 * 0.5f);
    motor2.setDuty(val2 * 0.5f);
    motor3.setDuty(val3 * 0.5f);
}

// UartLinkSubscriber instance for motor control
UartLinkSubscriber<float, float, float> motor_subscriber(&uart_link, messages::reception::STEER, &motor_control_callback);

void setup()
{
    // ここに初期化処理を書く
    motor1.start();
    motor2.start();
    motor3.start();
    uart_link.start();
}

void loop()
{
    // ここに繰り返し処理を書く
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART2) // Check instance directly for safety
  {
    // Forward to the UartLink interrupt handler
    // Ensure uart_link is accessible here (it's global in main.cpp)
    uart_link.interrupt();
  }
}
