/* �Ű� 2250748 �����q */
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
    return *a == *b;  // ȷ�������ַ���������
}

int main()
{
    short light = 0x0000;
    cout << "��ʼ״̬��" << "0x" << setw(4) << setfill('0') << hex << light << endl;
    cout << "A   B   C   D   E   F   G   H   I   J   " << endl;
    light_print(light);

    char command[10]; //�������������
    cout << "����(\"A On / J Off\"��ʽ���룬����\"Q on / off\"�˳�)" << endl; //˫����ת��
    while (cin >> command) {
        if (same(command, "Q")) {
            char action[5];
            cin >> action;
            if (same(action, "on") || same(action, "off")) {
                break;
            }
        }

        // ���ƵƵ�״̬
        char action[5];
        cin >> action;
        int bit_position = command[0] - 'A'; // �õ��Ƶ�λ�ã���A=0��J=9
        if (same(action, "On")) {
            light |= (1 << bit_position); // ��ָ��λ�õĵ�
        }
        else if (same(action, "Off")) {
            light &= ~(1 << bit_position); // �ر�ָ��λ�õĵ�
        }
        else {
            cout << "����(\"A On / J Off\"��ʽ���룬����\"Q on / off\"�˳�)" << endl; //˫����ת��
            continue;
        }

        // ��ӡ��ǰ״̬
        cout << "��ǰ״̬��" << "0x" << setw(4) << setfill('0') << hex << light << endl;
        cout << "A   B   C   D   E   F   G   H   I   J   " << endl;
        light_print(light);
        cout << "����(\"A On / J Off\"��ʽ���룬����\"Q on / off\"�˳�)" << endl; //˫����ת��
    }

    return 0;
}
