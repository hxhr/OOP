/* 2250748 王渝鹮 信安 */
/* 2254275 陶鸿周 2252086 孙靖贻 2252536 范颖佳 2151753 彭坤宇 2254298 范潇 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 16

void print_hex(FILE* out, const unsigned char* buffer, int length, int address)
{
    char line[LINE_SIZE + 1];
    line[LINE_SIZE] = '\0'; // 确保字符串以null结束

    for (int i = 0; i < length; ++i) {
        if (i % LINE_SIZE == 0) {
            if (i > 0) {
                fprintf(out, "    %s\n", line);
            }
            fprintf(out, "%08x  ", address + i);
        }

        fprintf(out, "%02x ", buffer[i]);
        line[i % LINE_SIZE] = (buffer[i] >= 33 && buffer[i] <= 126) ? buffer[i] : '.';

        if (i % LINE_SIZE == 7) {
            if (length % LINE_SIZE != 8) {
                fprintf(out, "- ");
            }
        }


    }

    // 处理最后一行可能不足16个字符的情况
    if (length % LINE_SIZE != 0) {
        for (int i = length; i < LINE_SIZE; ++i) {
            fprintf(out, "   ");
            line[i % LINE_SIZE] = '\0';//不要写成打印空格，不然就会在结尾有多余的空格。15-b1还没查
        }

        if (length <= 8) {
            fprintf(out, "  ");
        }
    }

    fprintf(out, "    %s\n", line);
}

//打印使用方法提示的函数
void print_usage(const char* name) 
{
    fprintf(stdout, "Usage : %s --infile 原始文件 [ --outfile hex格式文件 ]\n", name);
    fprintf(stdout, "        %s --infile a.docx\n", name);
    fprintf(stdout, "        %s --infile a.docx --outfile a.hex\n", name);
}


int main(int argc, char* argv[]) 
{
    if (argc != 3 && argc != 5) {
        print_usage(argv[0]);
        return -1;
    }

    char* input_filename = NULL;
    char* output_filename = NULL;

    //两个标志记录是否已经读过input、output，如果重复则直接错误
    int flag_1 = 0;//input
    int flag_2 = 0;//output
    // 解析命令行参数
    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "--infile") == 0) {
            if (flag_1) {
                print_usage(argv[0]);
                return -1;
            }
            input_filename = argv[i + 1];
            flag_1 = 1;
        }
        else if (strcmp(argv[i], "--outfile") == 0) {
            if (flag_2) {
                print_usage(argv[0]);
                return -1;
            }
            output_filename = argv[i + 1];
            flag_2 = 1;
        }
    }

    if (argc == 3) {
        if (!flag_1) {
            print_usage(argv[0]);
            return -1;
        }
    }
    if (argc == 5) {
        if (!flag_1 || !flag_2) {
            print_usage(argv[0]);
            return -1;
        }
    }


    FILE* infile = fopen(input_filename, "rb");//二进制方式读取
    if (!infile) {
        fprintf(stdout, "输入文件%s打开失败!\n", input_filename);
        return -1;
    }

    FILE* outfile = NULL;
    if (output_filename) {
        outfile = fopen(output_filename, "w");//覆盖式写入
        if (!outfile) {
            fprintf(stdout, "输出文件%s打开失败!\n", output_filename);
            fclose(infile);
            return 1;
        }
    }

    unsigned char buffer[LINE_SIZE];
    int address = 0;
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, LINE_SIZE, infile)) > 0) {
        print_hex(outfile ? outfile : stdout, buffer, bytes_read, address);
        address += LINE_SIZE;
    }

    fclose(infile);
    if (outfile) {
        fclose(outfile);
    }

    return 0;
}
