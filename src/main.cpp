#include "mbed.h"
#include "controller.hpp"
// #include "canSend.hpp"
#include "firstpenguin.hpp"

extern int leftJoystickX;
extern int leftJoystickY;
extern int rightJoystickX;
extern int lefts;
extern int rigts;
extern int AIred;
extern int AIblue;
extern int syudouAI;
extern bool AIchenge;
extern bool syudouAIchenge;
extern FirstPenguin penguin; // FirstPenguinクラスのインスタンス
extern FirstPenguin penguin_ball;
int16_t output;
int AIoutput;

DigitalIn color(PA_0);

CANMessage msg0;
CANMessage msg1;

BufferedSerial pc(USBTX, USBRX, 250000); // Serial communication with the PC
BufferedSerial neopixcel(PB_6, PA_10, 9600);  // Serial communication with the PC
// CAN can1(PA_11, PA_12, (int)1e6);
CAN can1(PA_11, PA_12, (int)1e6);
CAN can2(PB_12, PB_13, (int)1e6);
uint8_t DATAleft[8] = {};
uint8_t DATAright[8] = {};
constexpr uint32_t can_id = 30;

int maxspeed = 10000; // maxspeedをグローバル変数として宣言

void readUntilPipe(char *output_buf, int output_buf_size)
{
    char buf[20];
    int output_buf_index = 0;
    while (1)
    {
        if (pc.readable())
        {
            ssize_t num = pc.read(buf, sizeof(buf) - 1); // -1 to leave space for null terminator
            buf[num] = '\0';
            for (int i = 0; i < num; i++)
            {
                if (buf[i] == '|')
                {
                    output_buf[output_buf_index] = '\0';
                    return;
                }
                else if (buf[i] != '\n' && output_buf_index < output_buf_size - 1)
                {
                    output_buf[output_buf_index++] = buf[i];
                }
            }
        }
    }
}

void CANSend()
{
    color.mode(PullDown);
    while (1)
    {
        output = lefts;
        DATAleft[0] = output >> 8; // Big-endian conversion
        DATAleft[1] = output;
        DATAleft[2] = output >> 8; // Big-endian conversion
        DATAleft[3] = output;
        DATAleft[4] = -output >> 8; // Big-endian conversion
        DATAleft[5] = -output;
        DATAleft[6] = -output >> 8; // Big-endian conversion
        DATAleft[7] = -output;
        CANMessage msg0(0x200, DATAleft, 8);

        output = rigts;
        DATAright[0] = output >> 8; // Big-endian conversion
        DATAright[1] = output;
        DATAright[2] = output >> 8; // Big-endian conversion
        DATAright[3] = output;
        DATAright[4] = -output >> 8; // Big-endian conversion
        DATAright[5] = -output;
        DATAright[6] = -output >> 8; // Big-endian conversion
        DATAright[7] = -output;
        CANMessage msg1(0x1FF, DATAright, 8);

        if (AIchenge == 0)
        {
            penguin.pwm[0] = -leftJoystickX * 0.4 - leftJoystickY * 0.4 - rightJoystickX;
            penguin.pwm[1] = leftJoystickX * 0.4 - leftJoystickY * 0.4 - rightJoystickX;
            penguin.pwm[2] = leftJoystickX * 0.4 + leftJoystickY * 0.4 - rightJoystickX;
            penguin.pwm[3] = leftJoystickY * 0.4 - leftJoystickX * 0.4 - rightJoystickX;
            if(hanten == 1)
            {
                penguin.pwm[0] = -penguin.pwm[0];
                penguin.pwm[1] = -penguin.pwm[1];
                penguin.pwm[2] = -penguin.pwm[2];
                penguin.pwm[3] = -penguin.pwm[3];
            }
        }
        else
        {
            if (syudouAIchenge == 0)
            {
                if(color.read() == 1)
                {
                    AIoutput = AIred;

                }else{
                    AIoutput = AIblue;
                }
                printf("AIoutput = %d\n", AIoutput);
                penguin.pwm[0] = (320 - AIoutput) * 30;
                penguin.pwm[1] = -(320 - AIoutput) * 30;
                penguin.pwm[2] = -(320 - AIoutput) * 30;
                penguin.pwm[3] = (320 - AIoutput) * 30;
            }
            else
            {
                penguin.pwm[0] = -syudouAI;
                penguin.pwm[1] = syudouAI;
                penguin.pwm[2] = syudouAI;
                penguin.pwm[3] = -syudouAI;
            }
        }

        if (penguin.pwm[0] > maxspeed)
            penguin.pwm[0] = maxspeed;
        if (penguin.pwm[1] > maxspeed)
            penguin.pwm[1] = maxspeed;
        if (penguin.pwm[2] > maxspeed)
            penguin.pwm[2] = maxspeed;
        if (penguin.pwm[3] > maxspeed)
            penguin.pwm[3] = maxspeed;
        // printf("penguin.pwm[0] = %d, penguin.pwm[1] = %d, penguin.pwm[2] = %d, penguin.pwm[3] = %d\n", penguin.pwm[0], penguin.pwm[1], penguin.pwm[2], penguin.pwm[3]);

        can1.write(msg0);
        can1.write(msg1);
        penguin.send();
        penguin_ball.send();
        ThisThread::sleep_for(10ms);
    // neopixcel.write("blue\n", 6);
    // printf("red\n");
    }
}

int main()
{
    // printf("aaa\n");
    Thread thread1;         // Threadインスタンスの宣言
    thread1.start(CANSend); // thread1をCANSend関数で開始
    while (1)
    {
        char output_buf[20];                           // 出力用のバッファを作成します
        readUntilPipe(output_buf, sizeof(output_buf)); // '|'が受け取られるまでデータを読み込みます
        processInput(output_buf);
    }
}

// ##asimawari*4
// 1 2
// 4 3
// hennsuu:maxspeed

// ##kaisyuu*1

// ##hassya1*4
// hensuu:lefts
// ##hassya2*4
// hensuu:rigts

// 逆回転プログラムなし

//    else if (strncmp(output_buf, "cross", 5) == 0)
//     {
//         lefts = 16380;
//     }
//     else if (strncmp(output_buf, "triangle", 8) == 0)
//     {
//         lefts = 0;
//     }
//     else if (strncmp(output_buf, "circle", 6) == 0)
//     {
//         rigts = 16380;
//     }
//     else if (strncmp(output_buf, "square", 6) == 0)
//     {
//         rigts = 0;
//     }
