/* 信安 2250748 王渝鹮 */
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Student {
    int no;
    char* name;
    char* school;
};

int main() {
    ifstream fin;
    ofstream fout;

    fin.open("stulist.txt", ios::in);
    fout.open("r.txt", ios::out);

    if (!fin.is_open()) {
        cout << "打开输入文件失败" << endl;
        return -1;
    }

    if (!fout.is_open()) {
        cout << "打开输出文件失败" << endl;
        fin.close();
        return -1;
    }

    int N, M;
    fin >> N >> M;
    fin.ignore(); // 清除掉换行

    Student* students = new(nothrow) Student[M];

    for (int m = 0; m < M; m++) {
        char temp[256];
        fin.getline(temp, 256);  // 获取整行
        int i = 0;

        // 读取学号
        students[m].no = atoi(temp);//学到一个非常方便的转换函数!!!
        while (temp[i] != ' ') i++;

        // 读取名字
        i++;  // 跳过空格
        int nameStart = i;
        while (temp[i] != ' ') i++;
        int nameLength = i - nameStart;
        students[m].name = new char[nameLength + 1];
        for (int j = 0; j < nameLength; j++) {
            students[m].name[j] = temp[nameStart + j];
        }
        students[m].name[nameLength] = '\0';

        // 读取学校
        i++;  // 跳过空格
        int schoolStart = i;
        while (temp[i] != '\0') i++;
        int schoolLength = i - schoolStart;
        students[m].school = new char[schoolLength + 1];
        for (int j = 0; j < schoolLength; j++) {
            students[m].school[j] = temp[schoolStart + j];
        }
        students[m].school[schoolLength] = '\0';
    }

    cout << "已将随机抽取结果放入r.txt。请自行查看。" << endl;
    srand(static_cast<unsigned int>(time(0)));
    for (int n = 0; n < N; n++) {
        int r = rand() % M;
        fout << students[r].no << " " << students[r].name << " " << students[r].school << endl;
    }

    // 释放动态内存
    for (int m = 0; m < M; m++) {
        delete[] students[m].name;
        delete[] students[m].school;
    }
    delete[] students;

    fin.close();
    fout.close();

    return 0;
}
