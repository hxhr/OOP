/* 2250748 �����q �Ű� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

//�ҵ�һ��д��̫���ˣ�������������޸ĵĿ���ԡ���Ϊ��˳��д�����ġ�
//�ڶ����ýṹ������ţ����ڴ����ά��




struct CmdOption 
{
    const char* name;      // ��"-l"
    int defaultValue;      // Ĭ��ֵ
    int minValue;          // ��Сֵ
    int maxValue;          // ���ֵ
    int value;             // ʵ��ֵ����ʼ��ΪĬ��ֵ
    bool isFlag;           // �Ƿ��ǿ��أ���"-t"
};

CmdOption options[] =
{
    {"-l", 64, 32, 64000, 64, false},
    {"-n", 4, 1, 1024, 4, false},
    {"-t", 0, 0, 1, 0, true},
    // �����������...
};
const int optionsCount = sizeof(options) / sizeof(CmdOption);

int usage(const char* const procname) 
{
    cout << "Usage: "<<procname<<"[-l ��С][-n ����][-t] IP��ַ" << endl;
    cout << "       ==================================" << endl;
    cout << "        ���� ���Ӳ��� ��Χ        Ĭ��ֵ" << endl;
    cout << "       ==================================" << endl;
    cout << "        -l   1        [32..64000] 64" << endl;
    cout << "        -n   1        [1..1024]   4" << endl;
    cout << "        -t   0        [0..1]      0" << endl;
    cout << "       ==================================" << endl;
    return 0;
}

void parseArgs(int argc, char* argv[]) 
{
    for (int i = 1; i < argc - 1; i++) {
        bool isOptionFound = false;
        for (int j = 0; j < optionsCount; j++) {
            if (strcmp(argv[i], options[j].name) == 0) {
                isOptionFound = true;
                if (!options[j].isFlag) {
                    i++;
                    if (i < argc - 1 && argv[i][0] != '-') {
                        int val = atoi(argv[i]);
                        if (val >= options[j].minValue && val <= options[j].maxValue) {
                            options[j].value = val;
                        }
                    }
                    else {
                        cout << "����" << options[j].name << "û�к�������" << endl;
                        exit(1);
                    }
                }
                else {
                    options[j].value = 1;
                }
                break;
            }
        }
        if (!isOptionFound) {
            if (i == argc - 1) {
            }
            else {
                cout << "����" << argv[i] << "������" << endl;
                exit(1);
            }
        }
    }
}

int main(int argc, char* argv[]) 
{
    if (argc == 1) {
        usage(argv[0]);
        return 0;
    }
    //�ȿ�IP
    char ip[16];
    strcpy(ip, argv[argc - 1]);//���һ������һ����ip
    int flag = 0;//ͳ��.�ĸ���
    int sign[3] = { 0 };//�������λ��
    for (int i = 0; ip[i] != '\0'; i++) {
        if (ip[i] == '.') {
            sign[flag] = i;
            flag++;
        }
    }
    if (flag != 3) {
        cout << "IP��ַ����" << endl;
        return 0;
    }
    //�Ķ�����
    char seg_1[4];
    char seg_2[4];
    char seg_3[4];
    char seg_4[4];

    int j = 0;
    //1
    for (int i = 0; i < sign[0]; i++) {
        seg_1[i] = ip[i];
    }
    seg_1[sign[0]] = '\0';
    //2
    j = 0;
    for (int i = sign[0] + 1; i < sign[1]; i++, j++) {
        seg_2[j] = ip[i];
    }
    seg_2[j] = '\0';
    //3
    j = 0;
    for (int i = sign[1] + 1; i < sign[2]; i++, j++) {
        seg_3[j] = ip[i];
    }
    seg_3[j] = '\0';
    //4
    j = 0;
    for (int i = sign[2] + 1; ip[i] != '\0'; i++, j++) {
        seg_4[j] = ip[i];
    }
    seg_4[j] = '\0';

    if ((atoi(seg_1) >= 0 && atoi(seg_1) <= 255) && (atoi(seg_2) >= 0 && atoi(seg_2) <= 255) && (atoi(seg_3) >= 0 && atoi(seg_3) <= 255) && (atoi(seg_4) >= 0 && atoi(seg_4) <= 255)) {}
    else {
        cout << "IP��ַ����" << endl;
        return 0;
    }


    //���
    parseArgs(argc, argv);


    // �������ֵ
    for (int i = 0; i < optionsCount; i++) {
        cout << options[i].name << " ������" << options[i].value << endl;
    }

    cout << "IP��ַ��" << ip << endl;

    return 0;
}
