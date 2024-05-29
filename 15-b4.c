/* 2250748 �����q �Ű� */
/* 2254275 �պ��� 2252086 �ﾸ�� 2252536 ��ӱ�� 2151753 ������ 2254298 ���� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



//demo�������Ժø߰�����ʹ��c++�汾�Ĳ��˿ո�ĸ�ʽҲ����ȷת�����²��ȡ��ʽ�������ո�������ô������
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
    return (unsigned char)((highVal << 4) | lowVal);
}

void print_usage(const char* name) 
{
    fprintf(stderr, "Usage : %s --infile hex��ʽ�ļ� --outfile bin��ʽ�ļ�\n", name);
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
    //����˳����Ȼ���ƽϣ���������out����in

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
        fprintf(stderr, "�����ļ�%s��ʧ�ܣ�\n", input_filename);
        return -1;
    }

    FILE* outFile = fopen(output_filename, "wb");
    if (!outFile) {
        fprintf(stderr, "�޷���������ļ� %s\n", output_filename);
        fclose(file);
        return -1;
    }


    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char* ptr = line + 8; // ��Ϊ֮ǰ�ɿ�ð�Ų��ң�c��棺�ĳɿո��ˣ�����ֱ����
        if (!ptr) continue;

        ptr += 2; // ����2���ո�

        for (int i = 0; i < 16; ++i) {
            if (!isxdigit((unsigned char)ptr[0]) || !isxdigit((unsigned char)ptr[1])) {
                break; // ȷ����������Ч��ʮ�������ַ�
            }

            unsigned char ch = hexCharsToByte(ptr[0], ptr[1]);
            fputc(ch, outFile);

            ptr += (i == 7) ? 5 : 3; // ���м�����ۺŴ������������ո�
        }
    }

    fclose(file);
    fclose(outFile);

    return 0;
}
