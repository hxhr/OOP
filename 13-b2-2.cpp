/* 信安 2250748 王渝鹮 */
#include <iostream>
#include <fstream>

using namespace std;

struct student {
	int no;
	char name[9];
	int score;
	student* next;
};

 //向链表的尾部添加一个新的学生节点
student* add(student* head, int no, const char* name, int score) {
	//
	student* newstudent = new(nothrow) student;
	if (!newstudent) {
		cerr << "内存分配失败" << endl;
		exit(-1);
	}

	newstudent->no = no;

	int len;
	for (len = 0; len < 8 && name[len] != '\0'; len++) {
	}

	for (int i = 0; i < len; i++) {
		newstudent->name[i] = name[i];
	}
	newstudent->name[len] = '\0';  // 确保以null结尾

	newstudent->score = score;
	newstudent->next = nullptr;

	if (!head) {
		return newstudent;
	}
	else {
		student* curr = head;
		while (curr->next) {
			curr = curr->next;
		}
		curr->next = newstudent;
		return head;
	}
}

int main() {
	ifstream fin;
	fin.open("list.txt", ios::in);

	if (!fin.is_open() ){
		cerr << "无法打开list.txt文件" << endl;
		return -1;
	}

	student* head = nullptr;
	int no, score;
	char name[9];
	while (fin >> no >> name >> score) {
		if (no == 9999999) {
			break;
		}
		head = add(head, no, name, score);
	}
	fin.close();

	 //遍历链表并打印学生信息
	student* curr = head;
	while (curr) {
		cout << curr->no << " " << curr->name << " " << curr->score << endl;
		curr = curr->next;
	}

	// 释放链表内存
	while (head) {
		student* temp = head;
		head = head->next;
		delete temp;
	}

	return 0;
}
