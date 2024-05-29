/* 2250748 王渝鹮 信安 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

//我第一遍写的太差了，不能满足后续修改的快捷性。因为是顺着写下来的。
//第二遍用结构体来存放，便于代码的维护




struct CmdOption 
{
    const char* name;      // 如"-l"
    int defaultValue;      // 默认值
    int minValue;          // 最小值
    int maxValue;          // 最大值
    int value;             // 实际值，初始化为默认值
    bool isFlag;           // 是否是开关，如"-t"
};

CmdOption options[] =
{
    {"-l", 64, 32, 64000, 64, false},
    {"-n", 4, 1, 1024, 4, false},
    {"-t", 0, 0, 1, 0, true},
    // 添加其他参数...
};
const int optionsCount = sizeof(options) / sizeof(CmdOption);

int usage(const char* const procname) 
{
    cout << "Usage: "<<procname<<"[-l 大小][-n 数量][-t] IP地址" << endl;
    cout << "       ==================================" << endl;
    cout << "        参数 附加参数 范围        默认值" << endl;
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
                        cout << "参数" << options[j].name << "没有后续参数" << endl;
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
                cout << "参数" << argv[i] << "不存在" << endl;
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
    //先看IP
    char ip[16];
    strcpy(ip, argv[argc - 1]);//最后一个参数一定是ip
    int flag = 0;//统计.的个数
    int sign[3] = { 0 };//三个点的位置
    for (int i = 0; ip[i] != '\0'; i++) {
        if (ip[i] == '.') {
            sign[flag] = i;
            flag++;
        }
    }
    if (flag != 3) {
        cout << "IP地址错误" << endl;
        return 0;
    }
    //四段数字
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
        cout << "IP地址错误" << endl;
        return 0;
    }


    //别的
    parseArgs(argc, argv);


    // 输出参数值
    for (int i = 0; i < optionsCount; i++) {
        cout << options[i].name << " 参数：" << options[i].value << endl;
    }

    cout << "IP地址：" << ip << endl;

    return 0;
}
