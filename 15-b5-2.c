///* 信安 2250748 王渝鹮 */
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//// 检查文件格式
//int check_form(const char* filename) 
//{
//    FILE* file = fopen(filename, "rb");
//    if (!file) {
//        return 4; // 无法打开文件
//    }
//
//    int flag_l = 1; // Linux格式标志
//    int flag_w = 1; // Windows格式标志
//    int ch;
//    int prev = EOF; // 存储前一个字符，初始为EOF
//
//    while ((ch = fgetc(file)) != EOF) {
//        if (ch == '\n') {
//            if (prev == '\r') {
//                flag_l = 0; // 置Linux格式标志为false
//            }
//            else {
//                flag_w = 0; // 置Windows格式标志为false
//            }
//        }
//        prev = ch;
//    }
//
//    fclose(file);
//
//    if (flag_l && flag_w) return 3;
//    if (flag_l) return 1;
//    if (flag_w) return 2;
//    return 3;
//}
//
//// Windows格式转Linux格式
//int wtol(const char* inputFile, const char* outputFile) 
//{
//    FILE* in = fopen(inputFile, "rb");
//    FILE* out = fopen(outputFile, "wb");
//
//    if (!in || !out) {
//        if (in) fclose(in);
//        if (out) fclose(out);
//        return -1; // 文件打开失败
//    }
//
//    int num = 0; // 记录转换的次数
//    int ch;
//    while ((ch = fgetc(in)) != EOF) {
//        if (ch != '\r') {
//            fputc(ch, out);
//        }
//        else {
//            num++; // 统计转换次数
//        }
//    }
//
//    fclose(in);
//    fclose(out);
//    return num;
//}
//
//// Linux格式转Windows格式
//int ltow(const char* inputFile, const char* outputFile) 
//{
//    FILE* in = fopen(inputFile, "rb");
//    FILE* out = fopen(outputFile, "wb");
//
//    if (!in || !out) {
//        if (in) fclose(in);
//        if (out) fclose(out);
//        return -1; // 文件打开失败
//    }
//
//    int num = 0; // 记录转换的次数
//    int ch;
//    while ((ch = fgetc(in)) != EOF) {
//        if (ch == '\n') {
//            fputc('\r', out);
//            num++; // 统计转换次数
//        }
//        fputc(ch, out);
//    }
//
//    fclose(in);
//    fclose(out);
//    return num;
//}
//
//// 打印使用方法
//void print_usage(const char* name) 
//{
//    printf("Usage : %s --check 文件名 | --convert { wtol|ltow } 源文件名 目标文件名\n", name);
//    printf("        %s --check a.txt\n", name);
//    printf("        %s --convert wtol a.win.txt a.linux.txt\n", name);
//    printf("        %s --convert ltow a.linux.txt a.win.txt\n", name);
//}
//
//int main(int argc, char* argv[]) 
//{
//    if (argc != 3 && argc != 5) {
//        print_usage(argv[0]);
//        return -1;
//    }
//
//    if (argc == 3) {
//        // 如果命令是--check
//        if (strcmp(argv[1], "--check") == 0) {
//            int result = check_form(argv[2]);
//            switch (result) {
//                case 1:
//                    printf("Linux格式\n");
//                    break;
//                case 2:
//                    printf("Windows格式\n");
//                    break;
//                case 3:
//                    printf("文件格式无法识别\n");
//                    break;
//                case 4:
//                    printf("文件打开失败\n");
//                    break;
//            }
//        }
//        else {
//            print_usage(argv[0]);
//            return -1;
//        }
//    }
//    else {
//        // 如果命令是--convert
//        if (strcmp(argv[1], "--convert") == 0) {
//            int result = check_form(argv[3]);
//            if (result == 4) {
//                printf("文件打开失败\n");
//            }
//            else if (result == 3 || (strcmp(argv[2], "wtol") == 0 && result == 1) || (strcmp(argv[2], "ltow") == 0 && result == 2)) {
//                printf("文件格式无法识别\n");
//            }
//            else {
//                if (strcmp(argv[2], "wtol") == 0) {
//                    int num = wtol(argv[3], argv[4]);
//                    printf("转换完成，去除%d个0x0D\n", num);
//                }
//                else if (strcmp(argv[2], "ltow") == 0) {
//                    int num = ltow(argv[3], argv[4]);
//                    printf("转换完成，加入%d个0x0D\n", num);
//                }
//                else {
//                    print_usage(argv[0]);
//                    return -1;
//                }
//            }
//        }
//        else {
//            print_usage(argv[0]);
//            return -1;
//        }
//    }
//
//    return 0;
//}
