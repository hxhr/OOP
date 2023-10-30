///* 信安 2250748 王渝鹮 */
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//
//struct student {
//	int no;
//	char name[9];
//	int score;
//	struct student* next;
//};
//
//// 向链表的尾部添加一个新的学生节点
//struct student* add(struct student* head, int no, char name[], int score) {
//	//还是一次性分配空间
//	struct student* newstudent = (struct student*)malloc(sizeof(struct student));
//	//判断申请状态
//	if (!newstudent) {
//		printf("申请失败\n");
//		exit(-1);
//	}
//
//	
//	newstudent->no = no;
//	int i;
//	for (i = 0; i < 8 && name[i] != '\0'; i++) {
//		newstudent->name[i] = name[i];
//	}
//	newstudent->name[i] = '\0';
//	newstudent->score = score;
//	newstudent->next = NULL;
//
//	if (head == NULL) {
//		return newstudent;
//	}
//	else {
//		struct student* curr = head;
//		while (curr->next) {
//			curr = curr->next;
//		}
//		curr->next = newstudent;
//		return head;
//	}
//}
//
//int main() {
//	FILE* file = fopen("list.txt", "r");
//	if (!file) {
//		printf("Could not open list.txt\n");
//		return -1;
//	}
//
//	struct student* head = NULL;
//	int no, score;
//	char name[9];
//	while (fscanf(file, "%d %s %d", &no, name, &score) == 3) {
//		if (no == 9999999) {
//			break;
//		}
//		head = add(head, no, name, score);
//	}
//	fclose(file);
//
//	// 遍历链表并打印学生信息
//	struct student* curr = head;
//	while (curr) {
//		printf("%d %s %d\n", curr->no, curr->name, curr->score);
//		curr = curr->next;
//	}
//
//	// 释放链表内存
//	while (head) {
//		struct student* temp = head;
//		head = head->next;
//		free(temp);
//	}
//
//	return 0;
//}
