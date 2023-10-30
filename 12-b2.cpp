/* 2250748 王渝鹮 信安 */

#include <iostream>
#include<cmath>
#include <cstdio>
using namespace std;

double definite_integration(double (*handle) (double) ,double low,double high,int n)
{
	//不允许任何选择形式[if/switch/条件表达式]出现
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
	cout << "请输入sinxdx的下限、上限及区间划分数量" << endl;
	cin >> low >> high >> n;
    value = definite_integration(sin, low, high, n);
    cout << "sinxdx["<<low<<"~"<<high<<"/n="<<n<<"] : " << value << endl;
    cout << "请输入cosxdx的下限、上限及区间划分数量" << endl;
    cin >> low >> high >> n;
    value = definite_integration(cos, low, high, n);
    cout << "cosxdx[" << low << "~" << high << "/n=" << n << "] : " << value << endl;
    cout << "请输入e^xdx的下限、上限及区间划分数量" << endl;
    cin >> low >> high >> n;
    value = definite_integration(exp, low, high, n);
    cout << "e^xdx[" << low << "~" << high << "/n=" << n << "] : " << value << endl;

    return 0;
}


