/* 2250748 �����q �Ű� */
/* 2254275 �պ��� 2252086 �ﾸ�� 2252536 ��ӱ�� 2151753 ������ 2254298 ���� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 16

void print_hex(FILE* out, const unsigned char* buffer, int length, int address)
{
    char line[LINE_SIZE + 1];
    line[LINE_SIZE] = '\0'; // ȷ���ַ�����null����

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

    // �������һ�п��ܲ���16���ַ������
    if (length % LINE_SIZE != 0) {
        for (int i = length; i < LINE_SIZE; ++i) {
            fprintf(out, "   ");
            line[i % LINE_SIZE] = '\0';//��Ҫд�ɴ�ӡ�ո񣬲�Ȼ�ͻ��ڽ�β�ж���Ŀո�15-b1��û��
        }

        if (length <= 8) {
            fprintf(out, "  ");
        }
    }

    fprintf(out, "    %s\n", line);
}

//��ӡʹ�÷�����ʾ�ĺ���
void print_usage(const char* name) 
{
    fprintf(stdout, "Usage : %s --infile ԭʼ�ļ� [ --outfile hex��ʽ�ļ� ]\n", name);
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

    //������־��¼�Ƿ��Ѿ�����input��output������ظ���ֱ�Ӵ���
    int flag_1 = 0;//input
    int flag_2 = 0;//output
    // ���������в���
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


    FILE* infile = fopen(input_filename, "rb");//�����Ʒ�ʽ��ȡ
    if (!infile) {
        fprintf(stdout, "�����ļ�%s��ʧ��!\n", input_filename);
        return -1;
    }

    FILE* outfile = NULL;
    if (output_filename) {
        outfile = fopen(output_filename, "w");//����ʽд��
        if (!outfile) {
            fprintf(stdout, "����ļ�%s��ʧ��!\n", output_filename);
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
