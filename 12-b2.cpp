/* 2250748 �����q �Ű� */

#include <iostream>
#include<cmath>
#include <cstdio>
using namespace std;

double definite_integration(double (*handle) (double) ,double low,double high,int n)
{
	//�������κ�ѡ����ʽ[if/switch/�������ʽ]����
    double dx = (high - low) / n;
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += handle(low+dx * (2*i+2)/2) * dx;
    }
    return sum;

}

int main()
{
	int n;
	double low, high, value;
    double (*functions[3])(double) = { sin, cos, exp };
	cout << "������sinxdx�����ޡ����޼����仮������" << endl;
	cin >> low >> high >> n;
    value = definite_integration(sin, low, high, n);
    cout << "sinxdx["<<low<<"~"<<high<<"/n="<<n<<"] : " << value << endl;
    cout << "������cosxdx�����ޡ����޼����仮������" << endl;
    cin >> low >> high >> n;
    value = definite_integration(cos, low, high, n);
    cout << "cosxdx[" << low << "~" << high << "/n=" << n << "] : " << value << endl;
    cout << "������e^xdx�����ޡ����޼����仮������" << endl;
    cin >> low >> high >> n;
    value = definite_integration(exp, low, high, n);
    cout << "e^xdx[" << low << "~" << high << "/n=" << n << "] : " << value << endl;

    return 0;
}


