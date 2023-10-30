/* 2250748 ÍõÓåûq ĞÅ°² */
#include<iostream>
using namespace std;
int main()
{
	const char* month[] = { "January","February","March","April","May","June","July","August","September","October","November","December" };
	int num = 0;
	cin >> num;
	(cin.good() && num >= 1 && num <= 12) ? (cout << *(month + num - 1) << endl) : (cout << "Invalid" << endl);
	return 0;
}