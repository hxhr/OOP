///* �Ű� 2250748 �����q */
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//// ����ļ���ʽ
//int check_form(const char* filename) 
//{
//    FILE* file = fopen(filename, "rb");
//    if (!file) {
//        return 4; // �޷����ļ�
//    }
//
//    int flag_l = 1; // Linux��ʽ��־
//    int flag_w = 1; // Windows��ʽ��־
//    int ch;
//    int prev = EOF; // �洢ǰһ���ַ�����ʼΪEOF
//
//    while ((ch = fgetc(file)) != EOF) {
//        if (ch == '\n') {
//            if (prev == '\r') {
//                flag_l = 0; // ��Linux��ʽ��־Ϊfalse
//            }
//            else {
//                flag_w = 0; // ��Windows��ʽ��־Ϊfalse
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
//// Windows��ʽתLinux��ʽ
//int wtol(const char* inputFile, const char* outputFile) 
//{
//    FILE* in = fopen(inputFile, "rb");
//    FILE* out = fopen(outputFile, "wb");
//
//    if (!in || !out) {
//        if (in) fclose(in);
//        if (out) fclose(out);
//        return -1; // �ļ���ʧ��
//    }
//
//    int num = 0; // ��¼ת���Ĵ���
//    int ch;
//    while ((ch = fgetc(in)) != EOF) {
//        if (ch != '\r') {
//            fputc(ch, out);
//        }
//        else {
//            num++; // ͳ��ת������
//        }
//    }
//
//    fclose(in);
//    fclose(out);
//    return num;
//}
//
//// Linux��ʽתWindows��ʽ
//int ltow(const char* inputFile, const char* outputFile) 
//{
//    FILE* in = fopen(inputFile, "rb");
//    FILE* out = fopen(outputFile, "wb");
//
//    if (!in || !out) {
//        if (in) fclose(in);
//        if (out) fclose(out);
//        return -1; // �ļ���ʧ��
//    }
//
//    int num = 0; // ��¼ת���Ĵ���
//    int ch;
//    while ((ch = fgetc(in)) != EOF) {
//        if (ch == '\n') {
//            fputc('\r', out);
//            num++; // ͳ��ת������
//        }
//        fputc(ch, out);
//    }
//
//    fclose(in);
//    fclose(out);
//    return num;
//}
//
//// ��ӡʹ�÷���
//void print_usage(const char* name) 
//{
//    printf("Usage : %s --check �ļ��� | --convert { wtol|ltow } Դ�ļ��� Ŀ���ļ���\n", name);
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
//        // ���������--check
//        if (strcmp(argv[1], "--check") == 0) {
//            int result = check_form(argv[2]);
//            switch (result) {
//                case 1:
//                    printf("Linux��ʽ\n");
//                    break;
//                case 2:
//                    printf("Windows��ʽ\n");
//                    break;
//                case 3:
//                    printf("�ļ���ʽ�޷�ʶ��\n");
//                    break;
//                case 4:
//                    printf("�ļ���ʧ��\n");
//                    break;
//            }
//        }
//        else {
//            print_usage(argv[0]);
//            return -1;
//        }
//    }
//    else {
//        // ���������--convert
//        if (strcmp(argv[1], "--convert") == 0) {
//            int result = check_form(argv[3]);
//            if (result == 4) {
//                printf("�ļ���ʧ��\n");
//            }
//            else if (result == 3 || (strcmp(argv[2], "wtol") == 0 && result == 1) || (strcmp(argv[2], "ltow") == 0 && result == 2)) {
//                printf("�ļ���ʽ�޷�ʶ��\n");
//            }
//            else {
//                if (strcmp(argv[2], "wtol") == 0) {
//                    int num = wtol(argv[3], argv[4]);
//                    printf("ת����ɣ�ȥ��%d��0x0D\n", num);
//                }
//                else if (strcmp(argv[2], "ltow") == 0) {
//                    int num = ltow(argv[3], argv[4]);
//                    printf("ת����ɣ�����%d��0x0D\n", num);
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
