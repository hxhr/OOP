/* �Ű� 2250748 �����q */
#include <iostream>
/* --���ĳ����������Ҫ���˴�������������ĸ�ʽ����ͷ�ļ� --*/
#ifdef __linux__
#include <cstdio>
#endif
using namespace std;

int main()
{
	char a[80];

#if defined(__MINGW32__) || defined(__MINGW64__)  //DevC++
	gets(a);
#elif defined(_MSC_VER) && (_MSC_VER >= 1929)       //VS2022
	gets_s(a);
#elif defined(__linux__)       //Linux
	fgets(a, 80, stdin); //����Ҫ�������Ļس�
#endif
	cout << a << endl;
	return 0;
}

