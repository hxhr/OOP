/* 信安 2250748 王渝鹮 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>  // malloc, free

struct student {
    int* no;     // 使用指针
    char* name;  // 动态分配
    int* score;  // 使用指针
    struct student* next;
};

// 向链表的尾部添加一个新的学生节点
struct student* add(struct student* head, int no, const char* name, int score) {
    struct student* newStudent = (struct student*)malloc(sizeof(struct student));
    if (!newStudent) {
        fprintf(stderr, "内存申请失败\n");
        return NULL;
    }

    int nameLength;
    for (nameLength = 0; nameLength < 8 && name[nameLength] != '\0'; nameLength++) {
    }

    //二次申请
    newStudent->no = (int*)malloc(sizeof(int));     
    if (!newStudent->no) {
        fprintf(stderr, "内存申请失败\n");
        free(newStudent);
        return NULL;
    }
    *newStudent->no = no;  

    //二次申请，而且是按需分配，我用\0来确定
    newStudent->name = (char*)malloc(nameLength + 1);
    if (!newStudent->name) {
        fprintf(stderr, "内存申请失败\n");
        free(newStudent->no); // 别忘了释放学号内存
        free(newStudent);
        return NULL;
    }

    for (int i = 0; i < nameLength; i++) {
        newStudent->name[i] = name[i];
    }
    newStudent->name[nameLength] = '\0';

    newStudent->score = (int*)malloc(sizeof(int));  
    if (!newStudent->score) {
        fprintf(stderr, "内存申请失败\n");
        free(newStudent->name); // 别忘了释放名字内存
        free(newStudent->no);   // 别忘了释放学号内存
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
        fprintf(stderr, "无法打开list.txt\n");
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

    // 遍历链表并打印学生信息
    struct student* curr = head;
    while (curr) {
        printf("%d %s %d\n", *curr->no, curr->name, *curr->score);
        curr = curr->next;
    }

    // 释放链表内存
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
