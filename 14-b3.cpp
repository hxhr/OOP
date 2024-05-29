/* 2250748 王渝鹮 信安 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

int usage(const char* const procname)
{
	cout << "Usage: " << procname << " 要检查的学号/all 匹配学号/all 源程序名/all 相似度阀值(60-100) 输出(filename/screen)" << endl << endl;
	cout << "e.g. : " << procname << " 2159999 2159998 all       80 screen" << endl;
	cout << "       " << procname << " 2159999 all     14-b1.cpp 75 result.txt" << endl;
	cout << "       " << procname << " all     all     14-b2.cpp 80 check.dat" << endl;
	cout << "       " << procname << " all     all     all       85 screen" << endl;

	return 0;
}

//检查是否为七位数字
int is_num(char num[])
{
	for (int i = 0; i < 7; i++) {
		if (num[i] >= '0' && num[i] <= '9') {
			continue;
		}
		else {
			return 1;//不是七位数字
		}
	}
	if (num[7] == '\0') {
		return 2;//对
	}
	else {
		return 3;//不是七位
	}
}
int main(int argc, char* argv[])//参数的个数，参数指针
{
	if (argc != 6) {
		usage(argv[0]);
		return 0;
	}

	char num1[8];//检查
	char num2[8];//匹配
	char file[100];
	int like = 80;//缺省
	char out[100];

	//字符串不能直接等于
	strcpy(num1, argv[1]);
	strcpy(num2, argv[2]);
	strcpy(file, argv[3]);
	like = atoi(argv[4]); // 从字符串转换为整数
	strcpy(out, argv[5]);


	if (strcmp(num1, "all") == 0) {//返回0时代表相等
		if (strcmp(num2, "all") != 0) {
			cout << "检查学号是all，匹配学号必须是all" << endl;
			return 0;
		}
	}
	else {
		switch (is_num(num1)) {
			case 1:
				cout << "要检查的学号不是7位数字" << endl;
				return 0;
				break;
			case 2://num1正确
				break;
			case 3:
				cout << "要检查的学号不是7位" << endl;
				return 0;
				break;
		}
	}

	if (strcmp(num2, "all") == 0) {//返回0时代表相等
	}
	else {
		switch (is_num(num2)) {
			case 1:
				cout << "要匹配的学号不是7位数字" << endl;
				return 0;
				break;
			case 2://num2正确
				break;
			case 3:
				cout << "要匹配的学号不是7位" << endl;
				return 0;
				break;
		}
	}
	if ((strcmp(num2, num1) == 0) && strcmp(num1, "all") != 0) {
		cout << "匹配学号与要检查学号相同" << endl;
		return 0;
	}

	//文件
	for (int i = 0; i < 32; i++) {
		if (file[i] == '\0') {
			break;
		}
		if (i == 31 && file[i] != '\0') {
			cout << "源程序文件名超过了32字节" << endl;
			return 0;
		}
	}

	//相似度
	if (like >= 60 && like <= 100) {
	}
	else {
		like = 80;
	}

	//输出方式
	for (int i = 0; i < 32; i++) {
		if (out[i] == '\0') {
			break;
		}
		if (i == 31 && out[i] != '\0') {
			cout << "源程序文件名超过了32字节" << endl;
			return 0;
		}
	}

	cout << "参数检查通过" << endl;
	cout << "检查学号：" << num1 << endl;
	cout << "匹配学号：" << num2 << endl;
	cout << "源文件名：" << file << endl;
	cout << "匹配阈值：" << like << endl;
	cout << "输出目标：" << out << endl;

	return 0;
}
