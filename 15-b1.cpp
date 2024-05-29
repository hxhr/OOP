/* 2250748 �����q �Ű� */
/* 2254275 �պ��� 2251882 ��ʦ�� 2253716 ŷ���� 2151753 ������ 2050215 ����ǿ */
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
    char filename[256];
    cerr << "�ļ���������ʽ������:"<<endl;
    //˫б�ܲ�����
    cerr << "    a.txt                     : ����·����ʽ" << endl;
    cerr << "    ..\\data\\b.dat             : ���·����ʽ" << endl;
    cerr << "    C:\\Windows\\System32\\c.dat : ����·����ʽ" << endl;
    cerr << "�������ļ��� : ";
    cin.getline(filename, sizeof(filename));

    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "�����ļ�" << filename<<"��ʧ�ܣ�" << endl;
        return 1;
    }

    unsigned char ch;
    unsigned int count = 0;//������˼ int�Ͳ���
    int address = 0;
    char line[17]; // ���ڴ洢ASCII�ַ�
    line[16] = '\0'; // ȷ���ַ�����null����

    cout << hex << uppercase;
    while (file.get((char&)ch)) {//(int)(ch = file.get()) != EOF
        if (count % 16 == 0) {
            if (count > 0) {
                cout << " " << line << endl;
            }
            cout << setw(8) << setfill('0') << hex << address << ":  ";
            address += 16;
        }

        cout << setw(2) << setfill('0') << hex << static_cast<int>(ch) << " ";
        line[count % 16] = (ch >= 33 && ch <= 126) ? ch : '.'; // ֻ��ӡ�ɴ�ӡ�ַ�

        if (count % 16 == 7) {
            if (file.peek() != EOF) {
                cout << "- ";
            }
        }
        count++;
    }

    if (count % 16 != 0) {
        int padding = 3 * (16 - count % 16);
        if (count % 16 <= 8) padding += 2;
        for (int i = 0; i < padding; ++i) {
            cout << ' ';
        }
        line[count % 16] = '\0';
    }

    cout << " " << line << endl;

    file.close();
    return 0;
}
