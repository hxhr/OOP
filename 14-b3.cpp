/* 2250748 �����q �Ű� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

int usage(const char* const procname)
{
	cout << "Usage: " << procname << " Ҫ����ѧ��/all ƥ��ѧ��/all Դ������/all ���ƶȷ�ֵ(60-100) ���(filename/screen)" << endl << endl;
	cout << "e.g. : " << procname << " 2159999 2159998 all       80 screen" << endl;
	cout << "       " << procname << " 2159999 all     14-b1.cpp 75 result.txt" << endl;
	cout << "       " << procname << " all     all     14-b2.cpp 80 check.dat" << endl;
	cout << "       " << procname << " all     all     all       85 screen" << endl;

	return 0;
}

//����Ƿ�Ϊ��λ����
int is_num(char num[])
{
	for (int i = 0; i < 7; i++) {
		if (num[i] >= '0' && num[i] <= '9') {
			continue;
		}
		else {
			return 1;//������λ����
		}
	}
	if (num[7] == '\0') {
		return 2;//��
	}
	else {
		return 3;//������λ
	}
}
int main(int argc, char* argv[])//�����ĸ���������ָ��
{
	if (argc != 6) {
		usage(argv[0]);
		return 0;
	}

	char num1[8];//���
	char num2[8];//ƥ��
	char file[100];
	int like = 80;//ȱʡ
	char out[100];

	//�ַ�������ֱ�ӵ���
	strcpy(num1, argv[1]);
	strcpy(num2, argv[2]);
	strcpy(file, argv[3]);
	like = atoi(argv[4]); // ���ַ���ת��Ϊ����
	strcpy(out, argv[5]);


	if (strcmp(num1, "all") == 0) {//����0ʱ�������
		if (strcmp(num2, "all") != 0) {
			cout << "���ѧ����all��ƥ��ѧ�ű�����all" << endl;
			return 0;
		}
	}
	else {
		switch (is_num(num1)) {
			case 1:
				cout << "Ҫ����ѧ�Ų���7λ����" << endl;
				return 0;
				break;
			case 2://num1��ȷ
				break;
			case 3:
				cout << "Ҫ����ѧ�Ų���7λ" << endl;
				return 0;
				break;
		}
	}

	if (strcmp(num2, "all") == 0) {//����0ʱ�������
	}
	else {
		switch (is_num(num2)) {
			case 1:
				cout << "Ҫƥ���ѧ�Ų���7λ����" << endl;
				return 0;
				break;
			case 2://num2��ȷ
				break;
			case 3:
				cout << "Ҫƥ���ѧ�Ų���7λ" << endl;
				return 0;
				break;
		}
	}
	if ((strcmp(num2, num1) == 0) && strcmp(num1, "all") != 0) {
		cout << "ƥ��ѧ����Ҫ���ѧ����ͬ" << endl;
		return 0;
	}

	//�ļ�
	for (int i = 0; i < 32; i++) {
		if (file[i] == '\0') {
			break;
		}
		if (i == 31 && file[i] != '\0') {
			cout << "Դ�����ļ���������32�ֽ�" << endl;
			return 0;
		}
	}

	//���ƶ�
	if (like >= 60 && like <= 100) {
	}
	else {
		like = 80;
	}

	//�����ʽ
	for (int i = 0; i < 32; i++) {
		if (out[i] == '\0') {
			break;
		}
		if (i == 31 && out[i] != '\0') {
			cout << "Դ�����ļ���������32�ֽ�" << endl;
			return 0;
		}
	}

	cout << "�������ͨ��" << endl;
	cout << "���ѧ�ţ�" << num1 << endl;
	cout << "ƥ��ѧ�ţ�" << num2 << endl;
	cout << "Դ�ļ�����" << file << endl;
	cout << "ƥ����ֵ��" << like << endl;
	cout << "���Ŀ�꣺" << out << endl;

	return 0;
}
