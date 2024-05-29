/* 2250748 �����q �Ű� */ 
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;

class Shape {
protected:
    //������Ҫ������Ӧ�ĳ�Ա��Ҳ����Ϊ��
public:
    virtual void ShapeName() = 0; //�˾䲻׼��
    //������Ҫ������Ӧ�ĳ�Ա��Ҳ����Ϊ��
    virtual double area() = 0;
};

//�˴����������Ķ��弰ʵ��(��Ա������������ʵ����ʽ)
class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r);
    void ShapeName() override;
    double area() override;
};

class Square : public Shape {
private:
    double side;
public:
    Square(double s);
    void ShapeName() override;
    double area() override;
};

class Rectangle : public Shape {
private:
    double length, width;
public:
    Rectangle(double l, double w);
    void ShapeName() override;
    double area() override;
};

class Triangle : public Shape {
private:
    double a, b, c;
public:
    Triangle(double a, double b, double c);
    void ShapeName() override;
    double area() override;
};

class Trapezoid : public Shape {
private:
    double a, b, h;
public:
    Trapezoid(double a, double b, double h);
    void ShapeName() override;
    double area() override;
};

Circle::Circle(double r) : radius(r) {}

void Circle::ShapeName()
{
    cout << "Circle" << endl;
}

double Circle::area() 
{
    return radius > 0 ? M_PI * radius * radius : 0;
}

Square::Square(double s) : side(s) {}

void Square::ShapeName() 
{
    cout << "Square" << endl;
}

double Square::area() 
{
    return side > 0 ? side * side : 0;
}

Rectangle::Rectangle(double l, double w) : length(l), width(w) {}

void Rectangle::ShapeName()
{
    cout << "Rectangle" << endl;
}

double Rectangle::area()
{
    return (length > 0 && width > 0) ? length * width : 0;
}

Triangle::Triangle(double a, double b, double c) : a(a), b(b), c(c) {}

void Triangle::ShapeName() 
{
    cout << "Triangle" << endl;
}

double Triangle::area()
{
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}


Trapezoid::Trapezoid(double a, double b, double h) : a(a), b(b), h(h) {}

void Trapezoid::ShapeName() {
    cout << "Trapezoid" << endl;
}

double Trapezoid::area() {
    return (a > 0 && b > 0 && h > 0) ? 0.5 * (a + b) * h : 0;
}

/* -- �滻����� -- ���в�Ҫ���κθĶ� -- ���в�Ҫɾ�� -- �ڱ��е����治Ҫ�����κ��Լ�����䣬��ҵ�ύ��ӱ��п�ʼ�ᱻ�滻 -- �滻����� -- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
    if (1) {
        Circle    c1(5.2);           //�뾶5.2�����<=0�����Ϊ0��
        Square    s1(5.2);           //�߳�5.2�����<=0�����Ϊ0��
        Rectangle r1(5.2, 3.7);      //�����������һ<=0�����Ϊ0��
        Trapezoid t1(2.3, 4.4, 3.8); //�ϵס��µס��ߣ������һ<=0�����Ϊ0��
        Triangle  t2(3, 4, 5);       //���߳��ȣ������һ<=0�򲻹��������Σ����Ϊ0��
        Shape* s[5] = { &c1, &s1, &r1, &t1, &t2 };

        int   i;
        for (i = 0; i < 5; i++) {
            s[i]->ShapeName(); //�ֱ��ӡ��ͬ��״ͼ�ε����ƣ���ʽ�ο�demo��
            cout << s[i]->area() << endl; //�ֱ��ӡ��ͬ��״ͼ�ε��������ʽ�ο�demo��
            cout << endl;
        }
    }

    if (1) {
        Circle    c1(-1);           //�뾶5.2�����<=0�����Ϊ0��
        Square    s1(-1);           //�߳�5.2�����<=0�����Ϊ0��
        Rectangle r1(5.2, -1);      //�����������һ<=0�����Ϊ0��
        Trapezoid t1(2.3, -1, 3.8); //�ϵס��µס��ߣ������һ<=0�����Ϊ0��
        Triangle  t2(3, 4, -1);       //���߳��ȣ������һ<=0�򲻹��������Σ����Ϊ0��
        Shape* s[5] = { &c1, &s1, &r1, &t1, &t2 };

        cout << "============" << endl;
        int   i;
        for (i = 0; i < 5; i++) {
            s[i]->ShapeName(); //�ֱ��ӡ��ͬ��״ͼ�ε����ƣ���ʽ�ο�demo��
            cout << s[i]->area() << endl; //�ֱ��ӡ��ͬ��״ͼ�ε��������ʽ�ο�demo��
            cout << endl;
        }
    }

    return 0;
}

