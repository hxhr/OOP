/* 信安 2250748 王渝鹮 */
#include <iostream>
#include <iomanip>
using namespace std;

void light_print(int light)
{
    for (int i = 0; i < 10; i++) {
        cout << ((light & (1 << i)) ? "ON  " : "OFF ");
    }
    cout << endl;
    cout << endl;
}

bool same(const char* a, const char* b) {
    while (*a && *b) {
        if (*a != *b) return false;
        a++;
        b++;
    }
    return *a == *b;  // 确保两个字符串都结束
}

int main()
{
    short light = 0x0000;
    cout << "初始状态：" << "0x" << setw(4) << setfill('0') << hex << light << endl;
    cout << "A   B   C   D   E   F   G   H   I   J   " << endl;
    light_print(light);

    char command[10]; //储存输入的命令
    cout << "请以(\"A On / J Off\"形式输入，输入\"Q on / off\"退出)" << endl; //双引号转义
    while (cin >> command) {
        if (same(command, "Q")) {
            char action[5];
            cin >> action;
            if (same(action, "on") || same(action, "off")) {
                break;
            }
        }

        // 控制灯的状态
        char action[5];
        cin >> action;
        int bit_position = command[0] - 'A'; // 得到灯的位置，从A=0到J=9
        if (same(action, "On")) {
            light |= (1 << bit_position); // 打开指定位置的灯
        }
        else if (same(action, "Off")) {
            light &= ~(1 << bit_position); // 关闭指定位置的灯
        }
        else {
            cout << "请以(\"A On / J Off\"形式输入，输入\"Q on / off\"退出)" << endl; //双引号转义
            continue;
        }

        // 打印当前状态
        cout << "当前状态：" << "0x" << setw(4) << setfill('0') << hex << light << endl;
        cout << "A   B   C   D   E   F   G   H   I   J   " << endl;
        light_print(light);
        cout << "请以(\"A On / J Off\"形式输入，输入\"Q on / off\"退出)" << endl; //双引号转义
    }

    return 0;
}
