/* �Ű� 2250748 �����q */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>  // malloc, free

struct student {
    int* no;     // ʹ��ָ��
    char* name;  // ��̬����
    int* score;  // ʹ��ָ��
    struct student* next;
};

// �������β�����һ���µ�ѧ���ڵ�
struct student* add(struct student* head, int no, const char* name, int score) {
    struct student* newStudent = (struct student*)malloc(sizeof(struct student));
    if (!newStudent) {
        fprintf(stderr, "�ڴ�����ʧ��\n");
        return NULL;
    }

    int nameLength;
    for (nameLength = 0; nameLength < 8 && name[nameLength] != '\0'; nameLength++) {
    }

    //��������
    newStudent->no = (int*)malloc(sizeof(int));     
    if (!newStudent->no) {
        fprintf(stderr, "�ڴ�����ʧ��\n");
        free(newStudent);
        return NULL;
    }
    *newStudent->no = no;  

    //�������룬�����ǰ�����䣬����\0��ȷ��
    newStudent->name = (char*)malloc(nameLength + 1);
    if (!newStudent->name) {
        fprintf(stderr, "�ڴ�����ʧ��\n");
        free(newStudent->no); // �������ͷ�ѧ���ڴ�
        free(newStudent);
        return NULL;
    }

    for (int i = 0; i < nameLength; i++) {
        newStudent->name[i] = name[i];
    }
    newStudent->name[nameLength] = '\0';

    newStudent->score = (int*)malloc(sizeof(int));  
    if (!newStudent->score) {
        fprintf(stderr, "�ڴ�����ʧ��\n");
        free(newStudent->name); // �������ͷ������ڴ�
        free(newStudent->no);   // �������ͷ�ѧ���ڴ�
        free(newStudent);
        return NULL;
    }
    *newStudent->score = score;  

    newStudent->next = NULL;

    if (!head) {
        return newStudent;
    }
    else {
        struct student* curr = head;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = newStudent;
        return head;
    }
}

int main() {
    FILE* file = fopen("list.txt", "r");
    if (!file) {
        fprintf(stderr, "�޷���list.txt\n");
        return -1;
    }

    struct student* head = NULL;
    int no, score;
    char name[9];
    while (fscanf(file, "%d %s %d", &no, name, &score) == 3) {
        if (no == 9999999) {
            break;
        }
        head = add(head, no, name, score);
    }
    fclose(file);

    // ����������ӡѧ����Ϣ
    struct student* curr = head;
    while (curr) {
        printf("%d %s %d\n", *curr->no, curr->name, *curr->score);
        curr = curr->next;
    }

    // �ͷ������ڴ�
    while (head) {
        struct student* temp = head;
        head = head->next;
        free(temp->name);
        free(temp->no);
        free(temp->score);
        free(temp);
    }

    return 0;
}
