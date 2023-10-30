/* �Ű� 2250748 �����q */
#include <iostream>
#include <fstream>

using namespace std;

struct student {
	int no;
	char name[9];
	int score;
	student* next;
};

 //�������β�����һ���µ�ѧ���ڵ�
student* add(student* head, int no, const char* name, int score) {
	//
	student* newstudent = new(nothrow) student;
	if (!newstudent) {
		cerr << "�ڴ����ʧ��" << endl;
		exit(-1);
	}

	newstudent->no = no;

	int len;
	for (len = 0; len < 8 && name[len] != '\0'; len++) {
	}

	for (int i = 0; i < len; i++) {
		newstudent->name[i] = name[i];
	}
	newstudent->name[len] = '\0';  // ȷ����null��β

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
		cerr << "�޷���list.txt�ļ�" << endl;
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

	 //����������ӡѧ����Ϣ
	student* curr = head;
	while (curr) {
		cout << curr->no << " " << curr->name << " " << curr->score << endl;
		curr = curr->next;
	}

	// �ͷ������ڴ�
	while (head) {
		student* temp = head;
		head = head->next;
		delete temp;
	}

	return 0;
}
