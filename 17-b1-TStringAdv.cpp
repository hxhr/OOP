/* 2250748 王渝鹮 信安 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "17-b1-TStringAdv.h"
#include "17-b1-TString.h"

TStringAdv TStringAdv::substr(const int pos, const int n) const
{
    // 调整 pos 为从 1 开始的索引
    int adjustedPos = pos - 1;

    // 如果 pos 非法，返回空字符串
    if (adjustedPos < 0 || adjustedPos >= this->len||n<=0) {
        return TStringAdv();
    }

    // 计算实际要复制的长度
    int actualLen = n;
    if (n == INT_MAX|| adjustedPos + n > this->len) {
        actualLen = this->len - adjustedPos;
    }

    // 创建一个新的 TStringAdv 对象来存储子串
    TStringAdv subString;
    subString.content = new char[actualLen + 1];
    strncpy(subString.content, this->content + adjustedPos, actualLen);
    subString.content[actualLen] = '\0'; // 确保以 null 字符终止
    subString.len = actualLen; // 设置正确的长度

    return subString;
}


// 使用 TStringAdv 对象作为参数的 assign 函数实现
TStringAdv& TStringAdv::assign(const TStringAdv& ts2) 
{
    if (this != &ts2) {
        delete[] this->content; // 删除旧内容
        this->init(ts2.content); // 复制新内容
        this->len = ts2.len; // 设置新长度
    }
    return *this; // 返回当前对象的引用
}

// 使用 C 风格字符串作为参数的 assign 函数实现
TStringAdv& TStringAdv::assign(const char* s)
{
    delete[] this->content; // 删除旧内容
    this->init(s); // 复制新内容
    if (s) {
        this->len = strlen(s); // 设置新长度
    }
    else {
        this->len = 0; // 空字符串长度设置为0
    }
    return *this; // 返回当前对象的引用
}

// 追加 TStringAdv 对象
TStringAdv& TStringAdv::append(const TStringAdv& ts2)
{
    // 在这里调用 TString::operator+= 来连接字符串
    *this += ts2;
    return *this;
}

// 追加 C 风格字符串
TStringAdv& TStringAdv::append(const char* s) 
{
    // 在这里调用 TString::operator+= 来连接字符串
    TString temp(s);  // 假设 TString 有一个接受 const char* 的构造函数
    *this += temp;
    return *this;
}

// 追加单个字符
TStringAdv& TStringAdv::append(const char& c) 
{
    char str[2] = { c, '\0' }; // 创建一个临时的 C 风格字符串
    TString temp(str);  // 使用临时字符串创建 TString 对象
    *this += temp;
    return *this;
}

// 插入 TStringAdv 对象
TStringAdv& TStringAdv::insert(const TStringAdv& ts2, int pos)
{
    if (pos < 1 || pos > this->len + 1) {
        return *this; // 如果 pos 不合法，返回当前对象
    }
    TStringAdv before = this->substr(1, pos - 1); // 从第一个字符开始，截取到 pos - 1
    TStringAdv after = this->substr(pos);         // 从 pos 开始截取
    *this = before + ts2 + after;
    return *this;
}

// 插入 C 风格字符串
TStringAdv& TStringAdv::insert(const char* s, int pos)
{
    if (pos < 1 || pos > this->len + 1) {
        return *this; // 如果 pos 不合法，返回当前对象
    }
    TStringAdv before = this->substr(1, pos - 1); // 从第一个字符开始，截取到 pos - 1
    TStringAdv after = this->substr(pos);         // 从 pos 开始截取
    *this = before + TStringAdv(s) + after;
    return *this;
}
//
//// 插入单个字符
//TStringAdv& TStringAdv::insert(const char& c, int pos)
//{
//    if (pos < 1 || pos > this->len + 1) {
//        return *this; // 如果 pos 不合法，返回当前对象
//    }
//    TStringAdv before = this->substr(1, pos - 1); // 从第一个字符开始，截取到 pos - 1
//    TStringAdv after = this->substr(pos);         // 从 pos 开始截取
//    char str[2] = { c, '\0' };
//    *this = before + TStringAdv(str) + after;
//    return *this;
//}

TStringAdv& TStringAdv::insert(const char& c, int pos) 
{
    if (pos < 1 || pos > this->len + 1) {
        return *this; // 如果 pos 不合法，返回当前对象
    }

    // 特殊处理：如果 pos=1 且 c 是 '\0'
    if (pos == 1 && c == '\0') {
        delete[] this->content; // 释放原字符串
        this->len = 0;
        this->content = nullptr;
        return *this;
    }

    TStringAdv before = this->substr(1, pos - 1); // 从第一个字符开始，截取到 pos - 1
    TStringAdv after = (c == '\0') ? TStringAdv() : this->substr(pos); // 如果 c 是 '\0'，则 after 为空

    char str[2] = { c, '\0' };
    // 如果 c 是 '\0'，则不包括它
    *this = before + ((c == '\0') ? TStringAdv() : TStringAdv(str)) + after;
    return *this;
}


// 移除 TStringAdv 对象
TStringAdv& TStringAdv::erase(const TStringAdv& ts2)
{
    *this -= ts2;  // 使用 TString::operator-= 来移除子字符串
    return *this;
}

// 移除 C 风格字符串
TStringAdv& TStringAdv::erase(const char* s)
{
    TStringAdv temp(s);  // 将 C 风格字符串转换为 TStringAdv 对象
    *this -= temp;  // 使用 TString::operator-= 来移除子字符串
    return *this;
}

TStringAdv& TStringAdv::erase(const char& c)
{
    char str[2] = { c, '\0' };  // 创建一个以 null 结尾的字符串
    TStringAdv temp(str);      // 创建一个包含单一字符的 TStringAdv 对象
    *this -= temp;             // 使用 TStringAdv::operator-= 来移除该字符
    return *this;
}


char& TStringAdv::at(const int n) const
{
    int num = n;
    if (n < 0 || n >= this->len) {
        num  = 0;
    }
    return this->content[num];
}

int TStringAdv::TStringLenAdv(const TStringAdv& str) const
{
    return str.length();
}
