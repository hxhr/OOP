/* 2250748 王渝鹮 信安 */
#include <iostream>
#include <iomanip>
using namespace std;

#define STUDENT_NUM	4
#define SCORE_NUM	5

/* --- 不允许定义任何形式的全局变量 --- */

/***************************************************************************
  函数名称：
  功    能：求第一门课的平均分
  输入参数：
  返 回 值：
  说    明：相关输出都放在函数中即可
***************************************************************************/
void average(int(*score)[SCORE_NUM])
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
    int(*p)[SCORE_NUM];
    for (p = score; p < score + STUDENT_NUM; p++) {
        sum += **p;
    }
    
   
    
    cout << "第1门课平均分：" << sum/(double)STUDENT_NUM << endl;
    cout << endl;

}
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
double ave(int a[5]) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += a[i];
    }
    return sum / (double)SCORE_NUM;
}
/***************************************************************************
  函数名称：
  功    能：找出有两门以上课程不及格的学生
  输入参数：
  返 回 值：
  说    明：相关输出都放在函数中即可
***************************************************************************/
void fail(int(*score)[SCORE_NUM])
{
    /* 函数定义语句部分：
       1、本函数中仅允许定义 2个简单变量 + 1个行指针变量 + 1个简单指针变量 */

       /* 函数执行语句部分（要求同average）*/

    int(*row)[SCORE_NUM]; // 行指针遍历学生
    int* col; // 列指针遍历成绩
    int fail_count=0; 
    int num = 1; 
    cout << "2门以上不及格的学生：" << endl;

    // 遍历每个学生的成绩
    for (row = score; row < score + STUDENT_NUM; ++row, ++num) {
        fail_count = 0; // 初始化不及格科目数量为0
        // 遍历每门成绩，检查不及格的科目数量
        for (col = *row; col < *row + SCORE_NUM; col++) {
            if (*col < 60) { // 如果成绩小于60，记为不及格
                fail_count++;
            }
        }
        // 如果不及格科目数量大于等于2，输出学生索引
        if (fail_count >= 2) {
            cout << "No：" << num << " ";
            for (col = *row; col < *row + SCORE_NUM; col++) {
                cout << *col << " ";
            }
            cout <<"平均：" << ave(*row) << endl;
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
void good(int(*score)[SCORE_NUM])
{
    /* 函数定义语句部分：
       1、本函数中仅允许定义 2个简单变量 + 1个行指针变量 + 1个简单指针变量 */

       /* 函数执行语句部分（要求同average）*/
    cout << "平均90以上或全部85以上的学生：" << endl;
    int(*row)[SCORE_NUM]; // 行指针遍历学生
    int* col; // 列指针遍历成绩
    int num = 1;//学生编号
    int yes = 1;
    for (row = score; row < score + STUDENT_NUM; row++,num++) {
        yes = 2;
        for (col = *row; col < *row + SCORE_NUM; col++) {
            if (*col < 85) {
                yes--;
                break;
            }
        }
        if (ave(*row) < 90) {
            yes--;
        }
        if (yes) {
            cout << "No：" << num << " ";
            for (col = *row; col < *row + SCORE_NUM; col++) {
                cout << *col << " ";
            }
            cout << "平均：" << ave(*row) << endl;
        }
    }

}

void initial(int(*score)[SCORE_NUM])
{
    int(*row)[SCORE_NUM]; // 行指针遍历学生
    int* col; // 列指针遍历成绩
    int num = 1;
    cout << "初始信息：" << endl;
    for (row = score; row < score + STUDENT_NUM; row++, num++) {
        cout << "No." << num << "的1-5门课成绩：";
        for (col = *row; col < *row + SCORE_NUM; col++) {
            cout << *col << " ";
        }
        cout << endl;

    }
    cout << endl;
}

int main()
{
    int a[STUDENT_NUM][SCORE_NUM] = {
        {91, 81, 71, 61, 51},	//第1个学生的1-5门课的成绩
        {92, 82, 72, 32, 52},   //第2个学生的1-5门课的成绩
        {93, 83, 99, 80, 95},   //第3个学生的1-5门课的成绩
        {97, 85, 87, 91, 88} }; //第4个学生的1-5门课的成绩

    /* 除上面的预置数组外，本函数中仅允许定义 1个行指针变量 + 1个简单指针变量 */
    initial(a);
    average(a);
    fail(a);
    good(a);

    /* 函数执行语句部分（要求同average）*/


    return 0;
}