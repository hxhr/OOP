/* 2250748 王渝鹮 信安 */
#include <iostream>
#include <cmath>
using namespace std;

/* 从此处到标记替换行之间，给出各种类的定义及实现
	1、不允许定义全局变量（不含const和#define）
	2、不允许添加其它系统头文件
*/ 

class integral {
protected:
    double lower, upper; // 积分的上下限
    int n; // 划分数量

public:
    virtual double function(double x) = 0; // 被积函数
    virtual string functionName() const = 0; // 返回函数的名称

    // 为了提供输入提示，重载 >> 运算符
    friend istream& operator>>(istream& in, integral& obj) 
    {
        obj.printInputPrompt();
        in >> obj.lower >> obj.upper >> obj.n;
        return in;
    }

    // 打印输入提示的虚函数
    virtual void printInputPrompt() const = 0;

    double value()
    {
        double sum = 0;
        double width = (upper - lower) / n;
        for (int i = 1; i <= n; ++i) { // 从1开始，取每个矩形的右上角
            double x = lower + i * width;
            sum += function(x) * width;
        }

        // 打印计算的积分结果
        cout << functionName() << "dx[" << lower << "~" << upper << "/n=" << n << "] : "<< sum<<endl;
        return sum;
    }
};

class integral_sin : public integral {
public:
    double function(double x) override 
    {
        return sin(x);
    }
    string functionName() const override 
    {
        return "sinx";
    }
    void printInputPrompt() const override 
    {
        cout << "请输入sinxdx的下限、上限及区间划分数量" << endl;
    }
};

class integral_cos : public integral {
public:
    double function(double x) override 
    {
        return cos(x);
    }
    string functionName() const override 
    {
        return "cosx";
    }
    void printInputPrompt() const override 
    {
        cout << "请输入cosxdx的下限、上限及区间划分数量" << endl;
    }
};

class integral_exp : public integral {
public:
    double function(double x) override
    {
        return exp(x);
    }
    string functionName() const override 
    {
        return "e^x";
    }
    void printInputPrompt() const override
    {
        cout << "请输入e^xdx的下限、上限及区间划分数量" << endl;
    }
};

/* -- 替换标记行 -- 本行不要做任何改动 -- 本行不要删除 -- 在本行的下面不要加入任何自己的语句，作业提交后从本行开始会被替换 -- 替换标记行 -- */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：fun_integral不准动，思考一下，integral应如何定义
***************************************************************************/
void fun_integral(integral& fRef)
{
	cin >> fRef;	//输入上下限、划分数
	cout << fRef.value() << endl;
	return;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数不准动
***************************************************************************/
int main()
{
	integral_sin s1;
	integral_cos s2;
	integral_exp s3;

	fun_integral(s1); //计算sinxdx的值
	fun_integral(s2); //计算cosxdx的值
	fun_integral(s3); //计算expxdx的值

	return 0;
}

//注：矩形计算取右值，输出为正常double格式

