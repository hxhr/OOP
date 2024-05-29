/* 2250748 王渝鹮 信安 */
#pragma once


#include <iostream>
using namespace std;
template<typename T, int ROW, int COL>
class matrix 
{
private:
    T value[ROW][COL];

public:
    matrix() 
    {  
        for (int i = 0; i < ROW; ++i) {
            for (int j = 0; j < COL; ++j) {
                value[i][j] = T();
            }
        }
    }

    // 重载+运算符
    matrix operator+(const matrix& m) const
    {
        matrix result;
        for (int i = 0; i < ROW; ++i)
            for (int j = 0; j < COL; ++j)
                result.value[i][j] = value[i][j] + m.value[i][j];
        return result;
    }

    // 重载输出运算符
    friend ostream& operator<<(ostream& os, const matrix& m)
    {
        for (int i = 0; i < ROW; ++i) {
            for (int j = 0; j < COL; ++j)
                os << m.value[i][j] << " ";
            os << endl;
        }
        return os;
    }

    // 重载输入运算符
    friend istream& operator>>(istream& is, matrix& m) 
    {
        for (int i = 0; i < ROW; ++i)
            for (int j = 0; j < COL; ++j)
                is >> m.value[i][j];
        return is;
    }
};


