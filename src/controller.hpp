#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <mbed.h>
#include "firstpenguin.hpp"

// グローバル変数の宣言
extern int leftJoystickX;
extern int leftJoystickY;
extern int rightJoystickX;
extern int targetSpeedRight;
extern int targetSpeedLeft;
extern int8_t pic;
extern int targetSpeedRight_M;
extern int targetSpeedLeft_M;
extern int lefts;
extern int rigts;
extern int AIred;
extern int AIblue;
extern int syudouAI;
extern bool AIchenge;
extern bool syudouAIchenge;

extern const uint32_t penguinID;

extern CAN can;
extern CAN can2;

extern FirstPenguin penguin;

void processInput(char *output_buf);

#endif // CONTROLLER_HPP