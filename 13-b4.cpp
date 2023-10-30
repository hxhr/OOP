/* �Ű� 2250748 �����q */
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
        cout << "�������ļ�ʧ��" << endl;
        return -1;
    }

    if (!fout.is_open()) {
        cout << "������ļ�ʧ��" << endl;
        fin.close();
        return -1;
    }

    int N, M;
    fin >> N >> M;
    fin.ignore(); // ���������

    Student* students = new(nothrow) Student[M];

    for (int m = 0; m < M; m++) {
        char temp[256];
        fin.getline(temp, 256);  // ��ȡ����
        int i = 0;

        // ��ȡѧ��
        students[m].no = atoi(temp);//ѧ��һ���ǳ������ת������!!!
        while (temp[i] != ' ') i++;

        // ��ȡ����
        i++;  // �����ո�
        int nameStart = i;
        while (temp[i] != ' ') i++;
        int nameLength = i - nameStart;
        students[m].name = new char[nameLength + 1];
        for (int j = 0; j < nameLength; j++) {
            students[m].name[j] = temp[nameStart + j];
        }
        students[m].name[nameLength] = '\0';

        // ��ȡѧУ
        i++;  // �����ո�
        int schoolStart = i;
        while (temp[i] != '\0') i++;
        int schoolLength = i - schoolStart;
        students[m].school = new char[schoolLength + 1];
        for (int j = 0; j < schoolLength; j++) {
            students[m].school[j] = temp[schoolStart + j];
        }
        students[m].school[schoolLength] = '\0';
    }

    cout << "�ѽ������ȡ�������r.txt�������в鿴��" << endl;
    srand(static_cast<unsigned int>(time(0)));
    for (int n = 0; n < N; n++) {
        int r = rand() % M;
        fout << students[r].no << " " << students[r].name << " " << students[r].school << endl;
    }

    // �ͷŶ�̬�ڴ�
    for (int m = 0; m < M; m++) {
        delete[] students[m].name;
        delete[] students[m].school;
    }
    delete[] students;

    fin.close();
    fout.close();

    return 0;
}
