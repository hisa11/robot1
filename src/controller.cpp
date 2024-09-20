#include "controller.hpp"
#include "firstpenguin.hpp"

// extern FirstPenguin penguin; // 外部変数の宣言
int leftJoystickX = 0;
int leftJoystickY = 0;
int rightJoystickX = 0;
int lefts = 0;
int rigts = 0;
int AIred = 0;q
int AIblue = 0;
int syudouAI = 0;
bool AIchenge = 0;
bool syudouAIchenge = 0;

// CANインスタンスの定義
extern CAN can2; // CANインスタンスの外部宣言

// FirstPenguinクラスのインスタンスの定義
FirstPenguin penguin(30, can2);
void processInput(char *output_buf)
{
    if (strncmp(output_buf, "L3_x:", 5) == 0) // "L3_x:"という文字列で始まるかどうかを確認します
    {
        char *dataPointer = output_buf + 5; // "L3_x:"の後の文字列の先頭ポインタを取得
        // 数字部分を読み取る
        leftJoystickX = atoi(dataPointer);
        // 数字を使って何かをする（ここでは単にPCに出力）
        // printf("Left Joystick X: %d\n", leftJoystickX);
    }
    else if (strncmp(output_buf, "L3_y:", 5) == 0) // "L3_y:"という文字列で始まるかどうかを確認します
    {
        char *dataPointer = output_buf + 5; // "L3_y:"の後の文字列の先頭ポインタを取得
        // 数字部分を読み取る
        leftJoystickY = atoi(dataPointer);
        // 数字を使って何かをする（ここでは単にPCに出力）
        // printf("Left Joystick Y: %d\n", leftJoystickY);
    }
    else if (strncmp(output_buf, "R3_x:", 5) == 0) // "R3_x:"という文字列で始まるかどうかを確認します
    {
        char *dataPointer = output_buf + 5; // "R3_x:"の後の文字列の先頭ポインタを取得
        // 数字部分を読み取る
        rightJoystickX = atoi(dataPointer);
        // 数字を使って何かをする（ここでは単にPCに出力）
        // printf("Right Joystick X: %d\n", rightJoystickX);
        rightJoystickX = rightJoystickX / 5;
    }
    else if (strncmp(output_buf, "red: ", 5) == 0)
    {
        char *dataPointer = output_buf + 5;
        AIred = atoi(dataPointer);
    }
    else if (strncmp(output_buf, "blue: ", 6) == 0)
    {
        char *dataPointer = output_buf + 6;
        AIblue = atoi(dataPointer);
    }
    else if (strncmp(output_buf, "L1ON", 4) == 0) // "L1ON"という文字列で始まるかどうかを確認します
    {
        // penguin.pwm[0] = -10000;
        // penguin.pwm[1] = -10000;
        // penguin.pwm[2] = -10000;
        // penguin.pwm[3] = -10000;
        // penguin.send();
    }
    else if (strncmp(output_buf, "L1OFF", 5) == 0 || strncmp(output_buf, "R1OFF", 5) == 0) // "L1OFF"または"R1OFF"という文字列で始まるかどうかを確認します
    {
        // penguin.pwm[0] = 0;
        // penguin.pwm[1] = 0;
        // penguin.pwm[2] = 0;
        // penguin.pwm[3] = 0;
        // penguin.send();
    }
    else if (strncmp(output_buf, "R1ON", 4) == 0) // "R1ON"という文字列で始まるかどうかを確認します
    {
    }
    else if (strncmp(output_buf, "cross", 5) == 0)
    {
        lefts = 16380;
    }
    else if (strncmp(output_buf, "triangle", 8) == 0)
    {
        lefts = 0;
    }
    else if (strncmp(output_buf, "circle", 6) == 0)
    {
        rigts = -16380;
    }
    else if (strncmp(output_buf, "square", 6) == 0)
    {
        rigts = 0;
    }
    else if (strncmp(output_buf, "L2ON", 4) == 0)
    {
    }
    else if (strncmp(output_buf, "L2OFF", 5) == 0)
    {
    }
    else if (strncmp(output_buf, "R2ON", 4) == 0)
    {
    }
    else if (strncmp(output_buf, "R2OFF", 5) == 0)
    {
    }
    else if (strncmp(output_buf, "select", 6) == 0)
    {
    }
    else if (strncmp(output_buf, "start", 5) == 0)
    {
    }
    else if (strncmp(output_buf, "L3", 2) == 0)
    {
    }
    else if (strncmp(output_buf, "R3", 2) == 0)
    {
    }
    else if (strncmp(output_buf, "L1", 2) == 0)
    {
    }
    else if (strncmp(output_buf, "R1", 2) == 0)
    {
    }
    else if (strncmp(output_buf, "cross", 5) == 0)
    {
    }
    else if (strncmp(output_buf, "triangle", 8) == 0)
    {
    }
    else if (strncmp(output_buf, "circle", 6) == 0)
    {
    }
    else if (strncmp(output_buf, "square", 6) == 0)
    {
    }
    else if (strncmp(output_buf, "L2", 2) == 0)
    {
    }
    else if (strncmp(output_buf, "R2", 2) == 0)
    {
    }
    else if (strncmp(output_buf, "select", 6) == 0)
    {
    }
    else if (strncmp(output_buf, "start", 5) == 0)
    {
    }
    else if (strncmp(output_buf, "L3", 2) == 0)
    {
    }
    else if (strncmp(output_buf, "R3", 2) == 0)
    {
    }
    else if (strncmp(output_buf, "go", 2) == 0)
    {
    }
    else if (strncmp(output_buf, "back", 4) == 0)
    {
    }
    else if (strncmp(output_buf, "left", 4) == 0)
    {
        syudouAIchenge = 1;
        syudouAI = -7000;
    }
    else if (strncmp(output_buf, "right", 5) == 0)
    {
        syudouAIchenge = 1;
        syudouAI = 7000;
    }
    else if (strncmp(output_buf, "stop", 4) == 0)
    {
        syudouAIchenge = 1;
        syudouAI = 0;
    }
    else if(strncmp(output_buf,"AImode",6) == 0){
        if (AIchenge == 0) {
            AIchenge = 1;
        } else {
            AIchenge = 0;
        }
    }
    else if (strncmp(output_buf,"restart",7) == 0){
        syudouAIchenge = 0;
    }
    else if (strncasecmp(output_buf,"nothing",7)==0){
        AIred = 320;
        AIblue = 320;
        // printf("AIred = %d, AIblue = %d\n", AIred, AIblue);
    }
    
    
    
}