/* �Ű� 2250748 �����q */
#include <iostream>
#include <fstream>

using namespace std;
//�����Ǹ�cpp��һ��Ŀ¼�²��ܴ򿪰�����ô��ʦ˵��exe��
struct student {
    int no;
    char name[9];
    int score;
    int rank;
};

void sort_score(student* start, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (start[j].score < start[j + 1].score) {
                student temp = start[j];
                start[j] = start[j + 1];
                start[j + 1] = temp;
            }
        }
    }
}

void sort_no(student* start, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (start[j].no > start[j + 1].no) {
                student temp = start[j];
                start[j] = start[j + 1];
                start[j + 1] = temp;
            }
        }
    }
}

int main() {

    int count = 0;
    ifstream fin;
    fin.open("student.txt", ios::in);
    if (!fin.is_open()) {
        cout << "���ļ�ʧ��" << endl;
        return -1;
    }
    fin >> count;
    student* start = new(nothrow) student[count];
    if (start == NULL) {
        cout << "�ռ�����ʧ��" << endl;
        return -1;
    }
    student* curr = start;
    for (int i = 0; i < count; i++, curr++) {
        fin >> curr->no >> curr->name >> curr->score;
    }
    fin.close();

    sort_score(start, count);

    int cur_rank = 1;
    int cur_p = 1;//��ֹ����
    start[0].rank = cur_rank;

    for (int i = 1; i < count; i++) {
        cur_p++;
        if (start[i].score == start[i - 1].score) {
            start[i].rank = cur_rank;
        }
        else {
            cur_rank = cur_p;
            start[i].rank = cur_rank;
        }
    }


    sort_no(start, count);

    for (int i = 0; i < count; i++) {
        cout << start[i].no << " " << start[i].name << " " << start[i].score << " " << start[i].rank << endl;
    }

    delete[] start;
    return 0;
}
