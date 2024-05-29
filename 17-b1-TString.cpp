/* 2250748 王渝鹮 信安 */

/* 允许添加需要的头文件、宏定义等 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "17-b1-TString.h"
using namespace std;

/* 给出 tstring 类的所有成员函数的体外实现 */

// 私有成员函数 init 实现
void TString::init(const char* str)
{
	if (str && str[0] != '\0') {//这个后面这个条件是防""，不然不会输出NULL
		len = strlen(str);
		content = new(nothrow) char[len + 1];
		strcpy(content, str);
	}
	else {
		content = nullptr;
		len = 0;
	}
}

// 默认构造函数实现
TString::TString() : content(nullptr), len(0) {}
// 从 C 字符串初始化的构造函数实现/隐式调用的转换构造函数（既可以显示调用亦可以隐式调用

TString::TString(const char* str)
{
	init(str);
}
// 拷贝构造函数实现
TString::TString(const TString& other)
{
	init(other.content);
}
// 允许从单个字符构造TString对象
TString::TString(char c)
{
	len = 1;
	content = new char[2];
	content[0] = c;
	content[1] = '\0';
}
TString::TString(int n) : content(nullptr), len(0) {}
// 析构函数实现
TString::~TString()
{
	delete[] content;
}



//重载>>
istream& operator>>(istream& is, TString& str)
{
	delete[] str.content;
	str.content = nullptr;
	str.len = 0;

	// 估计输入行的典型大小
	const int bufferSize = 1000;
	char buffer[bufferSize];

	// 读取输入到缓冲区
	is >> ws; // 忽略前导空白
	char ch;
	int index = 0;
	bool word_finished = false;
	while (is.get(ch) && index < bufferSize - 1) {
		if (isspace(ch)) {
			if (!word_finished) {
				word_finished = true; // 遇到第一个空白字符，结束单词读取
			}
			if (ch == '\n') {
				is.unget(); // 如果是换行符，放回去以便下次读取
				break;
			}
		}
		else if (!word_finished) {
			buffer[index++] = ch; // 只有在单词未结束时才存储字符
		}
	}
	buffer[index] = '\0'; // 确保字符串正确终止

	// 复制缓冲区到TString
	str.len = index;
	str.content = new char[str.len + 1];
	strcpy(str.content, buffer);

	return is;
}
//重载<<
ostream& operator<<(ostream& os, const TString& str)
{
	//cout << "s3应为<NULL>，         实际输出：" << (s3 * 5) << endl;
	//cout << "s3应为<NULL>，         实际输出：" << (s3 = s3 * 5) << endl;

	if (str.content && str.content[0] != '\0') {//后一个条件限定是在调试过上面的代码后加的
		os << str.content;
	}
	else {
		os << "<NULL>";
	}
	return os;
}

const char* TString::c_str() const
{
	if (content) {
		return content;
	}
	else {
		// 如果content是空指针，我们返回一个指向空字符串的指针
		// 这是为了确保c_str()永远不会返回一个空指针
		return "";
	}
}


// 从另一个TString对象赋值
TString& TString::operator=(const TString& other)
{
	if (this != &other) {//避免自我赋值
		delete[] content;
		init(other.content);
	}
	return *this;
}

TString& TString::operator=(const char* str)
{
	delete[] content; // 删除当前对象的内容
	init(str); // 使用C风格字符串进行初始化
	return *this;
}

//在这里理一下重载+的思路
//一个成员函数 +TString，可以处理TString+char/char*/TString，因为可以隐式转换
//但是如果char/char*在左边就没办法了。所以还需要写两个友元函数分别是char+TString和char*+TString

// 重载 + 运算符，可以处理TString+char/char*/TString
TString TString::operator+(const TString& rhs) const
{
	int newLen = len + rhs.len;
	char* newContent = new char[newLen + 1];

	/*strcpy(newContent, this->content);
	strcat(newContent, rhs.content);*/
	//不能象注释里那么写，不然遇到NULL就会出错
	// 复制第一个字符串
	if (this->content) {
		strcpy(newContent, this->content);
	}
	else {
		newContent[0] = '\0'; // 如果是NULL，则设置为一个空字符串
	}

	// 连接第二个字符串
	if (rhs.content) {
		strcat(newContent, rhs.content);
	}


	TString result(newContent);
	delete[] newContent; // 避免内存泄漏
	return result;
}

// 非成员函数，处理 char 在左侧的情况
TString operator+(char lhs, const TString& rhs)
{
	return TString(lhs) + rhs; // 转换为 TString 然后调用成员函数 operator+
}

// 非成员函数，处理 const char* 在左侧的情况
TString operator+(const char* lhs, const TString& rhs)
{
	return TString(lhs) + rhs; // 转换为 TString 然后调用成员函数 operator+
}

// TString += TString，也处理隐式转换的 char 和 const char*
TString& TString::operator+=(const TString& rhs)
{
	// 使用 operator+ 来连接字符串，然后赋值给当前对象
	*this = *this + rhs;
	return *this;
}

//// TString::append 实现
//TString& TString::append(const TString& rhs)
//{
//	if (this != &rhs) { // 防止自连接
//		int newLen = len + rhs.len;
//		char* newContent = new char[newLen + 1];
//		strcpy(newContent, content); // 复制当前内容
//		strcat(newContent, rhs.content); // 连接rhs内容
//
//		delete[] content; // 删除旧内容
//		content = newContent; // 更新内容
//		len = newLen; // 更新长度
//	}
//	return *this;
//}
//
TString TString::operator-(const TString& rhs) const
{
	// 如果要移除的字符串为空，或者当前字符串为空，直接返回当前字符串的副本
	if (rhs.content == nullptr || rhs.len == 0 || this->content == nullptr) {
		return *this;
	}

	TString result(this->content); // 创建当前字符串的副本
	size_t pos = 0;
	bool found = true;
	// 在当前字符串中查找第一次出现要移除的字符串的位置
	for (int i = 0; i < result.len; ++i) {
		found = true;
		for (int j = 0; j < rhs.len; ++j) {
			if (i + j >= result.len || result.content[i + j] != rhs.content[j]) {
				found = false;
				break;
			}
		}

		// 如果找到了匹配的字符串
		if (found) {
			pos = i;
			break;
		}
	}

	// 如果找到了一个匹配项，移除它
	if (pos < (unsigned int)result.len && found) {
		// 创建一个新的临时数组来存储新的内容
		int newLen = result.len - rhs.len;
		char* newContent = new char[newLen + 1];

		// 复制前面的部分
		strncpy(newContent, result.content, pos);

		// 复制跳过找到的部分后的字符串
		strcpy(newContent + pos, result.content + pos + rhs.len);

		// 释放旧的内存，并更新result对象的内容和长度
		delete[] result.content;
		result.content = newContent;
		result.len = newLen;
	}

	return result;
}

TString& TString::operator-=(const TString& rhs)
{
	// 使用之前定义的 operator- 来得到结果
	*this = *this - rhs;
	return *this;
}

// *= 运算符的实现
TString& TString::operator*=(int factor)
{
	if (factor <= 0 || this->content == nullptr) {
		// 如果因子非正数或当前字符串为空，不执行任何操作
		return *this;
	}

	// 计算新的字符串长度
	int newLen = len * factor;
	char* newContent = new char[newLen + 1];

	// 复制当前字符串若干倍
	for (int i = 0; i < factor; ++i) {
		strcpy(newContent + i * len, content);
	}

	// 释放旧的内存，更新当前对象的内容和长度
	delete[] content;
	content = newContent;
	len = newLen;

	return *this;
}


TString TString::operator*(int factor)
{
	TString result(*this); // 创建当前对象的副本

	if (factor <= 0 || this->content == nullptr) {
		// 如果因子非正数或当前字符串为空，返回空字符串
		result.content = new char[1];
		result.content[0] = '\0';
		result.len = 0;
		return result;
	}

	// 复制当前字符串若干倍
	for (int i = 1; i < factor; ++i) {
		result += *this;
	}

	return result;
}

TString TString::operator!() const
{
	if (content == nullptr) {
		// 如果当前字符串为空，返回一个空字符串
		return TString();
	}

	// 计算新的字符串长度
	int newLen = len;
	char* newContent = new char[newLen + 1];

	// 将原字符串反转复制到新字符串中
	for (int i = 0; i < len; ++i) {
		newContent[i] = content[len - 1 - i];
	}
	newContent[len] = '\0'; // 添加 null 结尾

	// 创建一个新的 TString 对象并返回
	TString result(newContent);
	delete[] newContent; // 不再需要新字符串的内存，释放掉
	return result;
}

bool TString::operator>(const TString& rhs) const
{
	return strcmp(this->c_str(), rhs.c_str()) > 0;
}

bool TString::operator<(const TString& rhs) const
{
	return strcmp(this->c_str(), rhs.c_str()) < 0;
}

bool TString::operator==(const TString& rhs) const
{
	return strcmp(this->c_str(), rhs.c_str()) == 0;
}

bool TString::operator!=(const TString& rhs) const
{
	return strcmp(this->c_str(), rhs.c_str()) != 0;
}

bool TString::operator>=(const TString& rhs) const
{
	return strcmp(this->c_str(), rhs.c_str()) >= 0;
}

bool TString::operator<=(const TString& rhs) const
{
	return strcmp(this->c_str(), rhs.c_str()) <= 0;
}

bool operator>(const TString& lhs, const char* rhs)
{
	const char* rhs_ptr = rhs ? rhs : "";  // 将 NULL 视为指向空字符串的指针
	return strcmp(lhs.c_str(), rhs_ptr) > 0;
}

bool operator<(const TString& lhs, const char* rhs)
{
	const char* rhs_ptr = rhs ? rhs : "";  // 将 NULL 视为指向空字符串的指针
	return strcmp(lhs.c_str(), rhs_ptr) < 0;
}

bool operator==(const TString& lhs, const char* rhs)
{
	const char* rhs_ptr = rhs ? rhs : "";  // 将 NULL 视为指向空字符串的指针
	return strcmp(lhs.c_str(), rhs_ptr) == 0;
}

bool operator!=(const TString& lhs, const char* rhs)
{
	const char* rhs_ptr = rhs ? rhs : "";  // 将 NULL 视为指向空字符串的指针
	return strcmp(lhs.c_str(), rhs_ptr) != 0;
}

bool operator>=(const TString& lhs, const char* rhs)
{
	const char* rhs_ptr = rhs ? rhs : "";  // 将 NULL 视为指向空字符串的指针
	return strcmp(lhs.c_str(), rhs_ptr) >= 0;
}

bool operator<=(const TString& lhs, const char* rhs)
{
	const char* rhs_ptr = rhs ? rhs : "";  // 将 NULL 视为指向空字符串的指针
	return strcmp(lhs.c_str(), rhs_ptr) <= 0;
}

bool operator>(const char* lhs, const TString& rhs)
{
	return strcmp(lhs, rhs.c_str()) > 0;
}

bool operator<(const char* lhs, const TString& rhs)
{
	return strcmp(lhs, rhs.c_str()) < 0;
}

bool operator==(const char* lhs, const TString& rhs)
{
	return strcmp(lhs, rhs.c_str()) == 0;
}

bool operator!=(const char* lhs, const TString& rhs)
{
	return strcmp(lhs, rhs.c_str()) != 0;
}

bool operator>=(const char* lhs, const TString& rhs)
{
	return strcmp(lhs, rhs.c_str()) >= 0;
}

bool operator<=(const char* lhs, const TString& rhs)
{
	return strcmp(lhs, rhs.c_str()) <= 0;
}

int TString::length() const
{
	return len;
}

// 常量版本的下标操作符实现
char TString::operator[](int index) const
{
	if (index < 0 || index >= len || content == nullptr) {
		static char nullchar = '\0';
		// 返回一个空字符，或者抛出一个异常
		return nullchar;
	}
	return content[index];
}

// 非常量版本的下标操作符实现
char& TString::operator[](int index)
{
	if (index < 0 || index >= len || content == nullptr) {
		static char nullchar = '\0';
		// 返回一个空字符的引用，或者抛出一个异常
		return nullchar;
	}
	return content[index];
}

/* 如果有需要的其它全局函数的实现，可以写于此处 */

int TStringLen(const TString& str)
{
	return str.length(); // 调用TString的length函数
}