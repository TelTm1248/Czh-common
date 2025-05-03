#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool Switch_on = false;

class MotorController
{
public:
    float speed;
    int direction;

public:
    MotorController()
    {
        speed = 2.0;
        direction = 1;
    }
};

void panel()
{
    cout << "---------------------------------------------" << endl;
    cout << "请输入数字选择你的模式：" << endl;
    cout << "0 开启电机" << endl;
    cout << "1 关闭电机" << endl;
    cout << "2 修改电机速度" << endl;
    cout << "3 查看当前电机速度" << endl;
    cout << "4 修改电机转动方向（顺势针 or 逆时针）" << endl;
    cout << "5 查看当前电机转动方向（顺势针 or 逆时针）" << endl;
    cout << "---------------------------------------------" << endl;
}

int main(void)
{
    int choice;
    MotorController motor;
    for (;;)
    {
        panel();
        cin >> choice;
        if (choice == 0)
        {
            Switch_on = true;
            cout << endl
                 << "Please go on: " << endl;
        }
        else if (choice == 1)
        {
            Switch_on = false;
            break;
            system("pause");
        }
        else if (choice == 2 && Switch_on == true)
        {
            float rate;
            cout << "输入预修改数值：";
            cin >> rate;
            motor.speed = rate;
            cout << endl
                 << "Please go on: " << endl;
        }
        else if (choice == 3 && Switch_on == true)
        {
            cout << "现在的速度是：" << motor.speed << endl;
        }
        else if (choice == 4 && Switch_on == true)
        {
            int rot;
            cout << "输入预修改方向（0代表逆时针，1代表顺时针）：";
            cin >> rot;
            if (rot == 1 || rot == 0)
            {
                motor.direction = rot;
                cout << endl
                     << "Please go on: " << endl;
            }
            else
            {
                cout << "输入数字无效，请重新选择：";
            }
        }
        else if (choice == 5 && Switch_on == true)
        {
            cout << "现在的转动方向是：";
            if (motor.direction == 1)
            {
                cout << "顺时针" << endl;
            }
            else
            {
                cout << "逆时针" << endl;
            }
            cout << endl
                 << "Please go on: " << endl;
        }
        else
        {
            cout << "这不是一个有效指令！" << endl;
        }
    }
}
