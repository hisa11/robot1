#include "controller.hpp"
#include "firstpenguin.hpp"

// extern FirstPenguin penguin; // 外部変数の宣言
int leftJoystickX = 0;
int leftJoystickY = 0;
int rightJoystickX = 0;
int lefts = 0;
int rigts = 0;
int AIred = 0;
int AIblue = 0;
int syudouAI = 0;
bool AIchenge = 0;
bool syudouAIchenge = 0;
bool ball = 0;
int user = 0;
bool hanten = 0;

// CANインスタンスの定義
extern CAN can2; // CANインスタンスの外部宣言

// FirstPenguinクラスのインスタンスの定義
FirstPenguin penguin(30, can2);
FirstPenguin penguin_ball(35, can2);

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
        rightJoystickX = rightJoystickX / 4;
    }
    else if (strncmp(output_buf, "L3ON", 4) == 0)
    {
        neopixcel.write("hanten\n", 6);
        printf("hanten\n");
    }
    else if (strncmp(output_buf, "blue: nothing", 13) == 0)
    {
        AIblue = 320;
    }
    else if (strncmp(output_buf, "red: nothing", 12) == 0)
    {
        AIred = 320;
    }

    else if (strncmp(output_buf, "red: ", 5) == 0)
    {
        char *dataPointer = output_buf + 5;
        AIred = atoi(dataPointer);
        // printf("AIred = %d\n", AIred);
    }
    else if (strncmp(output_buf, "blue: ", 6) == 0)
    {
        char *dataPointer = output_buf + 6;
        AIblue = atoi(dataPointer);
    }
    // else if (strncmp(output_buf, "L1ON", 4) == 0) // "L1ON"という文字列で始まるかどうかを確認します
    // {
    //     // penguin.pwm[0] = -10000;
    //     // penguin.pwm[1] = -10000;
    //     // penguin.pwm[2] = -10000;
    //     // penguin.pwm[3] = -10000;
    //     // penguin.send();
    // }
    // else if (strncmp(output_buf, "L1OFF", 5) == 0 || strncmp(output_buf, "R1OFF", 5) == 0) // "L1OFF"または"R1OFF"という文字列で始まるかどうかを確認します
    // {
    //     // penguin.pwm[0] = 0;
    //     // penguin.pwm[1] = 0;
    //     // penguin.pwm[2] = 0;
    //     // penguin.pwm[3] = 0;
    //     // penguin.send();
    // }

    else if (strncmp(output_buf, "circle", 6) == 0) // "circle"という文字列で始まるかどうかを確認します
    {
        if (ball == 0)
        {
            ball = 1;
            penguin_ball.pwm[0] = 10000;
        }
        else
        {
            ball = 0;
            penguin_ball.pwm[0] = 0;
        }
    }

    else if (strncmp(output_buf, "L1ON", 4) == 0)
    {
        lefts = 16380;
    }
    else if (strncmp(output_buf, "L1OFF", 5) == 0)
    {
        lefts = 0;
    }
    else if (strncmp(output_buf, "R1ON", 4) == 0)
    {
        rigts = -16380;
    }
    else if (strncmp(output_buf, "R1OFF", 5) == 0)
    {
        rigts = 0;
    }

    else if (strncmp(output_buf, "square", 6) == 0)
    {
        if (AIchenge == 0)
        {
            AIchenge = 1;
            neopixcel.write("green\n", 5);
        }
        else
        {
            AIchenge = 0;
            if (user == 1)
            {
                neopixcel.write("blue\n", 5);
            }
            else if (user == 2)
            {
                neopixcel.write("white\n", 6);
            }
            else
            {
                neopixcel.write("purple\n", 6);
            }
        }
    }

    else if (strncasecmp(output_buf, "nari", 4) == 0)
    {
        AIchenge = 0;
        if (user == 1)
        {
            neopixcel.write("blue\n", 5);
        }
        else if (user == 2)
        {
            neopixcel.write("white\n", 6);
        }
        else
        {
            neopixcel.write("purple\n", 6);
        }
        user = 1;
    }
    else if (strncasecmp(output_buf, "iseki", 5) == 0)
    {
        AIchenge = 0;
        if (user == 1)
        {
            neopixcel.write("blue\n", 5);
        }
        else if (user == 2)
        {
            neopixcel.write("white\n", 6);
        }
        else
        {
            neopixcel.write("purple\n", 6);
        }
        user = 2;
    }
    else if (strncasecmp(output_buf, "finish", 6) == 0)
    {
        neopixcel.write("purple\n", 6);
    }
}