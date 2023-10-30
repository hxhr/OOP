/* 2250748 王渝鹮 信安 */
#include <iostream>
#include <iomanip>
using namespace std;

#define STUDENT_NUM	4
#define SCORE_NUM	5


//这个写的速度比1快了
/* --- 不允许定义任何形式的全局变量 --- */
double ave(int(*score)[STUDENT_NUM],int num)
{
    int(*row)[STUDENT_NUM]; // 行指针遍历成绩

    int sum = 0;//总成绩

       
            for (row = score; row < score + SCORE_NUM; row++) {
               
                sum += *(*row + num);
            }
           return  sum / (double)SCORE_NUM;
        


}


/***************************************************************************
  函数名称：
  功    能：求第一门课的平均分
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void average(int(*score)[STUDENT_NUM])
{
    /* 函数定义语句部分：
       1、本函数中仅允许定义 1个简单变量 + 1个指针变量 */

       /* 函数执行语句部分：
          1、不允许再定义任何类型的变量，包括 for (int i=0;...）等形式定义变量
          2、循环变量必须是指针变量，后续语句中不允许出现[]形式访问数组
             不允许：int a[10], i;
                     for(i=0; i<10; i++)
                         cout << a[i];
             允许  ：int a[10], p;
                     for(p=a; p<a+10; p++)
                         cout << *p;          */

    int sum = 0;
    int* col;
    //分清行列的关系，命名时用col和row方便后续检查
    for (col = *score; col < *score + STUDENT_NUM; col++) {
        sum += *col;
    }
    cout << "第1门课平均分：" << sum / (double)STUDENT_NUM << endl;
    cout << endl;



}

/***************************************************************************
  函数名称：
  功    能：找出有两门以上课程不及格的学生
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void fail(int(*score)[STUDENT_NUM])
{
    /* 函数定义语句部分：
       1、本函数中仅允许定义 3个简单变量 + 1个行指针变量 + 1个简单指针变量 */

       /* 函数执行语句部分（要求同average）*/
    int(*row)[STUDENT_NUM]; // 行指针遍历成绩
    int* col; // 列指针遍历学生
    int fail_count = 0;
    int num = 1;
    int sum = 0;//总成绩
    cout << "2门以上不及格的学生：" << endl;

    //卡了一会，因为col=*row反过来写是不成立的，所以外部循环实际上不能象-1那么思考
    for (num = 0; num < STUDENT_NUM; num++) {
        fail_count = 0; // 初始化不及格的课程数
        sum = 0;//初始化总成绩
        for (row = score; row < score + SCORE_NUM; row++) {
            col = *row + num; // 指向该学生的当前课程成绩
            if (*col < 60) // 如果成绩不及格，则增加计数
                fail_count++;
        }
        // 如果不及格科目数量大于等于2，输出学生索引
        if (fail_count >= 2) {
        cout << "No：" << num+1 << " ";
        for (row = score; row < score + SCORE_NUM; row++) {
            cout << *(*row + num) << " ";
            sum += *(*row + num);
        }
        cout << "平均：" << sum / (double)SCORE_NUM << endl;
        }
    }
    cout << endl;






}

/***************************************************************************
  函数名称：
  功    能：找出平均成绩在90分以上或全部成绩在85分以上的学生
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void good(int(*score)[STUDENT_NUM])
{
    /* 函数定义语句部分：
       1、本函数中仅允许定义 3个简单变量 + 1个行指针变量 + 1个简单指针变量 */

       /* 函数执行语句部分（要求同average）*/


    cout << "平均90以上或全部85以上的学生：" << endl;
    int(*row)[STUDENT_NUM]; // 行指针遍历学生
    int* col; // 列指针遍历成绩
    int num = 0;//学生编号
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
            cout << "No：" << num + 1 << " ";
            for (row = score; row < score + SCORE_NUM; row++) {
                cout << *(*row + num) << " ";
            }
            cout << "平均：" << ave(score, num) << endl;

        }
    }



}

void initial(int(*score)[STUDENT_NUM])
{
    int(*row)[STUDENT_NUM]; // 行指针遍历学生
    int num = 1;
    int* col;
    cout << "初始信息：" << endl;
  
    for (row = score; row < score + SCORE_NUM; row++,num++) {
        cout << "No.1-4学生的第" << num << "门课的成绩：";
        for (col = *row; col < *row + STUDENT_NUM; col++) {
            cout << *col << " ";
        }
        cout << endl;
    }
    cout << endl;
}



/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
    int a[SCORE_NUM][STUDENT_NUM] = {
        {91,92,93,97},  //第1-4个学生的第1门课成绩
        {81,82,83,85},  //第1-4个学生的第2门课成绩
        {71,72,99,87},  //第1-4个学生的第3门课成绩
        {61,32,80,91},  //第1-4个学生的第4门课成绩
        {51,52,95,88} };//第1-4个学生的第5门课成绩
    /* 除上面的预置数组外，本函数中仅允许定义 1个行指针变量 + 1个简单指针变量 */
    initial(a);
    average(a);
    fail(a);
    good(a);
    /* 函数执行语句部分（要求同average）*/


    return 0;
}