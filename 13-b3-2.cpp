/* 信安 2250748 王渝鹮 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

using namespace std;

struct student {
    int* no;
    char* name;  // 动态分配的名称
    int* score;
    student* next;
};

// 向链表的尾部添加一个新的学生节点
student* add(student* head, int* no, const char* name, int* score) {
    student* newStudent = new student;
    if (!newStudent) {
        cerr << "内存分配失败" << endl;
        exit(-1);
    }

    newStudent->no = new int;
    if (!newStudent->no) {
        cerr << "为学号分配内存失败" << endl;
        delete newStudent;
        exit(-1);
    }
    *(newStudent->no) = *no;

    // 动态得到名字长度，按需分配
    int nameLength;
    for (nameLength = 0; nameLength < 8 && name[nameLength] != '\0'; nameLength++) {
    }

    newStudent->name = new char[nameLength + 1];
    if (!newStudent->name) {
        cerr << "为名称分配内存失败" << endl;
        delete newStudent->no;
        delete newStudent;
        exit(-1);
    }

    for (int i = 0; i < nameLength; i++) {
        newStudent->name[i] = name[i];
    }
    newStudent->name[nameLength] = '\0';

    newStudent->score = new int;
    if (!newStudent->score) {
        cerr << "为分数分配内存失败" << endl;
        delete[] newStudent->name;
        delete newStudent->no;
        delete newStudent;
        exit(-1);
    }
    *(newStudent->score) = *score;

    newStudent->next = NULL;

    if (!head) {
        return newStudent;
    }
    else {
        student* curr = head;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = newStudent;
        return head;
    }
}

int main() {
    ifstream fin;
    fin.open("list.txt", ios::in);
    if (!fin.is_open()) {
        cerr << "无法打开list.txt文件。" << endl;
        return -1;
    }

    student* head = NULL;
    int no, score;
    char name[9];
    while (fin >> no >> name >> score) {
        if (no == 9999999) {
            break;
        }
        int* p_no = new int;
        char* p_name = new char[strlen(name) + 1];
        int* p_score = new int;
        *p_no = no;
        strcpy(p_name, name);
        *p_score = score;
        head = add(head, p_no, p_name, p_score);
    }
    fin.close();

    // 遍历链表并打印学生信息
    student* curr = head;
    while (curr) {
        cout << *(curr->no) << " " << curr->name << " " << *(curr->score) << endl;
        curr = curr->next;
    }

    // 释放链表内存
    while (head) {
        student* temp = head;
        head = head->next;
        delete[] temp->name;
        delete temp->no;
        delete temp->score;
        delete temp;
    }

    return 0;
}
