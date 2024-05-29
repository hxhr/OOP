/* 2250748 王渝鹮 信安 */

#pragma once


#include "17-b1-TString.h"
using namespace std;


class TStringAdv : public TString {
public:
    // 使用基类的构造函数
    using TString::TString;

    TStringAdv& operator=(const TString& rhs) {
        // 调用基类的赋值操作符来处理赋值
        TString::operator=(rhs);
        // 返回当前对象的引用
        return *this;
    }

    // TStringAdv特有的成员函数声明
    TStringAdv substr(const int pos, const int len = INT_MAX) const;

    // // substr 方法声明

    // 新增的 assign 函数声明
    TStringAdv& assign(const TStringAdv& ts2);
    TStringAdv& assign(const char* s);

    // append 方法声明
    TStringAdv& append(const TStringAdv& ts2);
    TStringAdv& append(const char* s);
    TStringAdv& append(const char& c);

    // insert 方法声明
    TStringAdv& insert(const TStringAdv& ts2, int pos);
    TStringAdv& insert(const char* s, int pos);
    TStringAdv& insert(const char& c, int pos);

    // erase 方法声明
    TStringAdv& erase(const TStringAdv& ts2);
    TStringAdv& erase(const char* s);
    TStringAdv& erase(const char& c);

    char& at(const int n) const;

    int TStringLenAdv(const TStringAdv& str) const;

};
