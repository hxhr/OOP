/* 2250748 王渝鹮 信安 */
/* 2254275 陶鸿周 2251882 聂师扬 2253716 欧佳音 2151753 彭坤宇 2050215 吴樾强 */
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
        return -1; // 非法的十六进制字符
    }
}

unsigned char hexCharsToByte(char high, char low)
{
    int highVal = hexCharToInt(high);
    int lowVal = hexCharToInt(low);
    if (highVal == -1 || lowVal == -1) {
        return 0; // 或者处理错误
    }
    return static_cast<unsigned char>((highVal << 4) | lowVal);
}

int main() 
{
    char filename1[256];
    cerr << "文件名以下形式均可以:" << endl;
    //双斜杠才能用
    cerr << "    a.hex                     : 不带路径形式" << endl;
    cerr << "    ..\\data\\b.txt             : 相对路径形式" << endl;
    cerr << "    C:\\Windows\\System32\\c.hex : 绝对相对路径形式" << endl;
    cerr << "请输入要转换的hex格式文件名 : ";
    cin.getline(filename1, sizeof(filename1));

    ifstream file(filename1);
    if (!file) {
        cerr << "输入文件" << filename1 << "打开失败！" << endl;
        return 1;
    }

    cout << "请输入转换后的文件名        : ";
    char filename2[256];
    cin.getline(filename2, sizeof(filename2));
    ofstream outFile(filename2, ios::binary);
    if (!outFile) {
        cerr << "无法创建输出文件" << endl;
        file.close();
        return 1;
    }

    char line[256];
    while (file.getline(line, sizeof(line))) {
        char* ptr = strchr(line, ':'); // 查找冒号
        if (!ptr) continue;

        ptr += 3; // 跳过冒号和两个空格

        for (int i = 0; i < 16; ++i) {
            if (!isxdigit(ptr[0]) || !isxdigit(ptr[1])) {
                break; // 确保有两个有效的十六进制字符
            }

            char ch = hexCharsToByte(ptr[0], ptr[1]);
            outFile.put(ch);
            ptr += (i == 7) ? 5 : 3; // 在中间的破折号处多跳过一个空格
        }
    }

    file.close();
    outFile.close();



    return 0;
}


//把长汉语文字跑一遍，看它的末尾是什么，为什么能成
//跑简单的26字母，为什么不能成
//跑pdf 为什么不能成

    //char line[256];
    //while (file.getline(line, sizeof(line))) {
    //    char* ptr = strchr(line, ':'); // 查找冒号
    //    if (!ptr) continue;

    //    ptr += 3; // 跳过冒号和两个空格

    //    for (int i = 0; i < 16; ++i) {
    //        unsigned int value;
    //        if (sscanf(ptr, "%2x", &value) != 1) break; // 读取两个字符为一个十六进制数.汉字时读取没问题
    //        char ch = static_cast<char>(value);
    //        //if (!(ch >= 33 && ch <= 126)) {
    //        //    break;
    //        //}
    //        outFile.put(ch);
    //        ptr += (i == 7) ? 5 : 3; // 在中间的破折号处多跳过一个空格
    //    }
    //}

//为什么我这种扫pdf会在最后一行判断不出来