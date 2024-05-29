/* 2250748 �����q �Ű� */
#include <iostream>
#include <cmath>
using namespace std;

/* �Ӵ˴�������滻��֮�䣬����������Ķ��弰ʵ��
	1����������ȫ�ֱ���������const��#define��
	2���������������ϵͳͷ�ļ�
*/ 

class integral {
protected:
    double lower, upper; // ���ֵ�������
    int n; // ��������

public:
    virtual double function(double x) = 0; // ��������
    virtual string functionName() const = 0; // ���غ���������

    // Ϊ���ṩ������ʾ������ >> �����
    friend istream& operator>>(istream& in, integral& obj) 
    {
        obj.printInputPrompt();
        in >> obj.lower >> obj.upper >> obj.n;
        return in;
    }

    // ��ӡ������ʾ���麯��
    virtual void printInputPrompt() const = 0;

    double value()
    {
        double sum = 0;
        double width = (upper - lower) / n;
        for (int i = 1; i <= n; ++i) { // ��1��ʼ��ȡÿ�����ε����Ͻ�
            double x = lower + i * width;
            sum += function(x) * width;
        }

        // ��ӡ����Ļ��ֽ��
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
        cout << "������sinxdx�����ޡ����޼����仮������" << endl;
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
        cout << "������cosxdx�����ޡ����޼����仮������" << endl;
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
        cout << "������e^xdx�����ޡ����޼����仮������" << endl;
    }
};

/* -- �滻����� -- ���в�Ҫ���κθĶ� -- ���в�Ҫɾ�� -- �ڱ��е����治Ҫ�����κ��Լ�����䣬��ҵ�ύ��ӱ��п�ʼ�ᱻ�滻 -- �滻����� -- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����fun_integral��׼����˼��һ�£�integralӦ��ζ���
***************************************************************************/
void fun_integral(integral& fRef)
{
	cin >> fRef;	//���������ޡ�������
	cout << fRef.value() << endl;
	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main������׼��
***************************************************************************/
int main()
{
	integral_sin s1;
	integral_cos s2;
	integral_exp s3;

	fun_integral(s1); //����sinxdx��ֵ
	fun_integral(s2); //����cosxdx��ֵ
	fun_integral(s3); //����expxdx��ֵ

	return 0;
}

//ע�����μ���ȡ��ֵ�����Ϊ����double��ʽ

