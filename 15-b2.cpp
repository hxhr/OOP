/* 2250748 �����q �Ű� */
/* 2254275 �պ��� 2251882 ��ʦ�� 2253716 ŷ���� 2151753 ������ 2050215 ����ǿ */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;
int hexCharToInt(char ch)
{
    if (ch >= '0' && ch <= '9') {
        return ch - '0';
    }
    else if (ch >= 'a' && ch <= 'f') {
        return 10 + ch - 'a';
    }
    else if (ch >= 'A' && ch <= 'F') {
        return 10 + ch - 'A';
    }
    else {
        return -1; // �Ƿ���ʮ�������ַ�
    }
}

unsigned char hexCharsToByte(char high, char low)
{
    int highVal = hexCharToInt(high);
    int lowVal = hexCharToInt(low);
    if (highVal == -1 || lowVal == -1) {
        return 0; // ���ߴ������
    }
    return static_cast<unsigned char>((highVal << 4) | lowVal);
}

int main() 
{
    char filename1[256];
    cerr << "�ļ���������ʽ������:" << endl;
    //˫б�ܲ�����
    cerr << "    a.hex                     : ����·����ʽ" << endl;
    cerr << "    ..\\data\\b.txt             : ���·����ʽ" << endl;
    cerr << "    C:\\Windows\\System32\\c.hex : �������·����ʽ" << endl;
    cerr << "������Ҫת����hex��ʽ�ļ��� : ";
    cin.getline(filename1, sizeof(filename1));

    ifstream file(filename1);
    if (!file) {
        cerr << "�����ļ�" << filename1 << "��ʧ�ܣ�" << endl;
        return 1;
    }

    cout << "������ת������ļ���        : ";
    char filename2[256];
    cin.getline(filename2, sizeof(filename2));
    ofstream outFile(filename2, ios::binary);
    if (!outFile) {
        cerr << "�޷���������ļ�" << endl;
        file.close();
        return 1;
    }

    char line[256];
    while (file.getline(line, sizeof(line))) {
        char* ptr = strchr(line, ':'); // ����ð��
        if (!ptr) continue;

        ptr += 3; // ����ð�ź������ո�

        for (int i = 0; i < 16; ++i) {
            if (!isxdigit(ptr[0]) || !isxdigit(ptr[1])) {
                break; // ȷ����������Ч��ʮ�������ַ�
            }

            char ch = hexCharsToByte(ptr[0], ptr[1]);
            outFile.put(ch);
            ptr += (i == 7) ? 5 : 3; // ���м�����ۺŴ�������һ���ո�
        }
    }

    file.close();
    outFile.close();



    return 0;
}


//�ѳ�����������һ�飬������ĩβ��ʲô��Ϊʲô�ܳ�
//�ܼ򵥵�26��ĸ��Ϊʲô���ܳ�
//��pdf Ϊʲô���ܳ�

    //char line[256];
    //while (file.getline(line, sizeof(line))) {
    //    char* ptr = strchr(line, ':'); // ����ð��
    //    if (!ptr) continue;

    //    ptr += 3; // ����ð�ź������ո�

    //    for (int i = 0; i < 16; ++i) {
    //        unsigned int value;
    //        if (sscanf(ptr, "%2x", &value) != 1) break; // ��ȡ�����ַ�Ϊһ��ʮ��������.����ʱ��ȡû����
    //        char ch = static_cast<char>(value);
    //        //if (!(ch >= 33 && ch <= 126)) {
    //        //    break;
    //        //}
    //        outFile.put(ch);
    //        ptr += (i == 7) ? 5 : 3; // ���м�����ۺŴ�������һ���ո�
    //    }
    //}

//Ϊʲô������ɨpdf�������һ���жϲ�����