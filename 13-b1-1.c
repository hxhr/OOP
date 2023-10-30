/* �Ű� 2250748 �����q */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
struct student {
    int no;
    char name[9];
    int score;
    int rank;
};

//ð�ݷ�
void sort_score(struct student* start, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (start[j].score < start[j + 1].score) {
                struct student temp = start[j];
                start[j] = start[j + 1];
                start[j + 1] = temp;
            }
        }
    }
}

void sort_no(struct student* start, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (start[j].no > start[j + 1].no) {
                struct student temp = start[j];
                start[j] = start[j + 1];
                start[j + 1] = temp;
            }
        }
    }
}

int main() {
    int count = 0;
    FILE* fin = fopen("student.txt", "r");
    if (!fin) {
        printf("���ļ�ʧ��\n");
        return -1;
    }

    fscanf(fin, "%d", &count);//�̶���ʽ����ס

    struct student* start = (struct student*)malloc(count * sizeof(struct student));
    if (start == NULL) {
        printf("�ռ�����ʧ��\n");
        return -1;
    }

    for (int i = 0; i < count; i++) {
        fscanf(fin, "%d %s %d", &start[i].no, start[i].name, &start[i].score);
    }
    fclose(fin);

    sort_score(start, count);

    int cur_rank = 1;
    int cur_p = 1;//��������ֹ����
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
        printf("%d %s %d %d\n", start[i].no, start[i].name, start[i].score, start[i].rank);
    }

    free(start);
    return 0;
}
