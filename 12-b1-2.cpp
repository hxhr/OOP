/* 2250748 �����q �Ű� */
#include <iostream>
#include <iomanip>
using namespace std;

#define STUDENT_NUM	4
#define SCORE_NUM	5


//���д���ٶȱ�1����
/* --- ���������κ���ʽ��ȫ�ֱ��� --- */
double ave(int(*score)[STUDENT_NUM],int num)
{
    int(*row)[STUDENT_NUM]; // ��ָ������ɼ�

    int sum = 0;//�ܳɼ�

       
            for (row = score; row < score + SCORE_NUM; row++) {
               
                sum += *(*row + num);
            }
           return  sum / (double)SCORE_NUM;
        


}


/***************************************************************************
  �������ƣ�
  ��    �ܣ����һ�ſε�ƽ����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void average(int(*score)[STUDENT_NUM])
{
    /* ����������䲿�֣�
       1���������н������� 1���򵥱��� + 1��ָ����� */

       /* ����ִ����䲿�֣�
          1���������ٶ����κ����͵ı��������� for (int i=0;...������ʽ�������
          2��ѭ������������ָ���������������в��������[]��ʽ��������
             ������int a[10], i;
                     for(i=0; i<10; i++)
                         cout << a[i];
             ����  ��int a[10], p;
                     for(p=a; p<a+10; p++)
                         cout << *p;          */

    int sum = 0;
    int* col;
    //�������еĹ�ϵ������ʱ��col��row����������
    for (col = *score; col < *score + STUDENT_NUM; col++) {
        sum += *col;
    }
    cout << "��1�ſ�ƽ���֣�" << sum / (double)STUDENT_NUM << endl;
    cout << endl;



}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ҳ����������Ͽγ̲������ѧ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void fail(int(*score)[STUDENT_NUM])
{
    /* ����������䲿�֣�
       1���������н������� 3���򵥱��� + 1����ָ����� + 1����ָ����� */

       /* ����ִ����䲿�֣�Ҫ��ͬaverage��*/
    int(*row)[STUDENT_NUM]; // ��ָ������ɼ�
    int* col; // ��ָ�����ѧ��
    int fail_count = 0;
    int num = 1;
    int sum = 0;//�ܳɼ�
    cout << "2�����ϲ������ѧ����" << endl;

    //����һ�ᣬ��Ϊcol=*row������д�ǲ������ģ������ⲿѭ��ʵ���ϲ�����-1��ô˼��
    for (num = 0; num < STUDENT_NUM; num++) {
        fail_count = 0; // ��ʼ��������Ŀγ���
        sum = 0;//��ʼ���ܳɼ�
        for (row = score; row < score + SCORE_NUM; row++) {
            col = *row + num; // ָ���ѧ���ĵ�ǰ�γ̳ɼ�
            if (*col < 60) // ����ɼ������������Ӽ���
                fail_count++;
        }
        // ����������Ŀ�������ڵ���2�����ѧ������
        if (fail_count >= 2) {
        cout << "No��" << num+1 << " ";
        for (row = score; row < score + SCORE_NUM; row++) {
            cout << *(*row + num) << " ";
            sum += *(*row + num);
        }
        cout << "ƽ����" << sum / (double)SCORE_NUM << endl;
        }
    }
    cout << endl;






}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ҳ�ƽ���ɼ���90�����ϻ�ȫ���ɼ���85�����ϵ�ѧ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void good(int(*score)[STUDENT_NUM])
{
    /* ����������䲿�֣�
       1���������н������� 3���򵥱��� + 1����ָ����� + 1����ָ����� */

       /* ����ִ����䲿�֣�Ҫ��ͬaverage��*/


    cout << "ƽ��90���ϻ�ȫ��85���ϵ�ѧ����" << endl;
    int(*row)[STUDENT_NUM]; // ��ָ�����ѧ��
    int* col; // ��ָ������ɼ�
    int num = 0;//ѧ�����
    int yes = 1;
    for (num = 0; num < STUDENT_NUM; num++) {
        yes = 2;
        for (row = score; row < score + SCORE_NUM; row++) {
            col = *row + num;
            if (*col < 85) {
                yes--;
                break;
            }
        }
        if (ave(score,num) < 90) {
            yes--;
        }
        if (yes) {
            cout << "No��" << num + 1 << " ";
            for (row = score; row < score + SCORE_NUM; row++) {
                cout << *(*row + num) << " ";
            }
            cout << "ƽ����" << ave(score, num) << endl;

        }
    }



}

void initial(int(*score)[STUDENT_NUM])
{
    int(*row)[STUDENT_NUM]; // ��ָ�����ѧ��
    int num = 1;
    int* col;
    cout << "��ʼ��Ϣ��" << endl;
  
    for (row = score; row < score + SCORE_NUM; row++,num++) {
        cout << "No.1-4ѧ���ĵ�" << num << "�ſεĳɼ���";
        for (col = *row; col < *row + STUDENT_NUM; col++) {
            cout << *col << " ";
        }
        cout << endl;
    }
    cout << endl;
}



/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
    int a[SCORE_NUM][STUDENT_NUM] = {
        {91,92,93,97},  //��1-4��ѧ���ĵ�1�ſγɼ�
        {81,82,83,85},  //��1-4��ѧ���ĵ�2�ſγɼ�
        {71,72,99,87},  //��1-4��ѧ���ĵ�3�ſγɼ�
        {61,32,80,91},  //��1-4��ѧ���ĵ�4�ſγɼ�
        {51,52,95,88} };//��1-4��ѧ���ĵ�5�ſγɼ�
    /* �������Ԥ�������⣬�������н������� 1����ָ����� + 1����ָ����� */
    initial(a);
    average(a);
    fail(a);
    good(a);
    /* ����ִ����䲿�֣�Ҫ��ͬaverage��*/


    return 0;
}