/* 2250748 王渝鹮 信安 */
/* 2254275 陶鸿周 2252086 孙靖贻 2252536 范颖佳 2151753 彭坤宇 2254298 范潇 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



//demo的适配性好高啊，即使跟c++版本的差了空格的格式也能正确转换，猜测读取方式是遇到空格跳？怎么做到的
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
    return (unsigned char)((highVal << 4) | lowVal);
}

void print_usage(const char* name) 
{
    fprintf(stderr, "Usage : %s --infile hex格式文件 --outfile bin格式文件\n", name);
    fprintf(stderr, "        %s --infile a.hex --outfile a.bin\n", name);
}

int main(int argc, char* argv[])
{
    if (argc != 5) {
        print_usage(argv[0]);
        return -1;
    }

    char* input_filename = NULL;
    char* output_filename = NULL;
    //输入顺序依然不计较，可以先输out后输in

    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "--infile") == 0) {
            input_filename = argv[i + 1];
        }
        else if (strcmp(argv[i], "--outfile") == 0) {
            output_filename = argv[i + 1];
        }
    }

    if (input_filename == NULL || output_filename == NULL) {
        print_usage(argv[0]);
        return -1;
    }


    FILE* file = fopen(input_filename, "r");
    if (!file) {
        fprintf(stderr, "输入文件%s打开失败！\n", input_filename);
        return -1;
    }

    FILE* outFile = fopen(output_filename, "wb");
    if (!outFile) {
        fprintf(stderr, "无法创建输出文件 %s\n", output_filename);
        fclose(file);
        return -1;
    }


    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char* ptr = line + 8; // 因为之前可靠冒号查找，c这版：改成空格了，所以直接跳
        if (!ptr) continue;

        ptr += 2; // 跳过2个空格

        for (int i = 0; i < 16; ++i) {
            if (!isxdigit((unsigned char)ptr[0]) || !isxdigit((unsigned char)ptr[1])) {
                break; // 确保有两个有效的十六进制字符
            }

            unsigned char ch = hexCharsToByte(ptr[0], ptr[1]);
            fputc(ch, outFile);

            ptr += (i == 7) ? 5 : 3; // 在中间的破折号处多跳过两个空格
        }
    }

    fclose(file);
    fclose(outFile);

    return 0;
}
