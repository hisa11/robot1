// // canSend.cpp
// #include "mbed.h"
// #include "firstpenguin.hpp"
// #include "canSend.hpp" // ヘッダーファイルをインクルード

// extern CAN can1; // メインファイルで定義されたグローバル変数を参照
// extern CAN can2;
// extern FirstPenguin penguin;
// extern int16_t currentSpeed;
// extern int16_t currentSpeed1;
// extern int16_t currentAnpere;
// extern int16_t currentAnpere1;
// extern int picAngle;
// extern int targetSpeedRight;
// extern int targetSpeedLeft;
// extern int targetpicSpeed;
// extern int outputpic;
// extern int joystickAngle;
// extern uint8_t DATA[8];

// // PID制御器のインスタンスを参照
// extern CANMessage msg0;
// extern CANMessage msg1;


// // extern int8_t pic;

// int16_t picAngle_d = 0;
// int16_t picSpeed_d = 0;
// // int16_t picAngle = 0; // Declare and initialize picAngle
// int tireAngle = 0;



// // void CANSend()
// // {
// //     while (1)
// //     {
        
// //         // printf("outputpic = %f\n", outputpic);
// //         // printf("outputRight = %f, outputLeft = %f, outputpic = %f\n", outputRight, outputLeft, outputpic);

// //         // if(outputpic > 11000)
// //         // {
// //         //     outputpic = 11000;
// //         // }
// //         // printf("picSpeed_d = %d, outputpic = %f\n", picSpeed_d, static_cast<double>(outputpic));

// //         // int16_t outputpicInt16 = static_cast<int16_t>(outputpic);
// //         // // printf("outputpic = %d\n", outputpicInt16);
// //         // DATA[3] = outputpicInt16 >> 8;   // MSB
// //         // DATA[4] = outputpicInt16 & 0xFF; // LSB

// //         can1.write(msg0);
// //         can2.write(msg1);
// //         penguin.send();
// //         // ThisThread::sleep_for(10ms);
// //     }
// // }
