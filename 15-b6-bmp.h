/* 信安 2250748 王渝鹮 */

#pragma once

#include <fstream>
#include <iostream>

using namespace std;

typedef unsigned char  BYTE;//1
typedef unsigned short WORD;//2
typedef unsigned long  DWORD;//4
typedef long LONG;//4

struct BITMAPFILEHEADERo 
{
    //第一行这个type必须单独读，因为结构体会字节对齐
    //WORD    bfType;        // 文件类型，必须是0x4D42，即字符'BM'
    DWORD  bfSize;          //文件大小    
    WORD   bfReserved1;     //保留字，不考虑    
    WORD   bfReserved2;     //保留字，同上    
    DWORD  bfOffBits;       //实际位图数据的偏移字节数，即前三个部分长度之和    
};

struct BITMAPINFOHEADERo
{
    DWORD   biSize;             //指定此结构体的长度，为40    
    LONG    biWidth;            //位图宽    
    LONG    biHeight;           //位图高    
    WORD    biPlanes;           //平面数，为1    
    WORD    biBitCount;         //采用颜色位数，可以是1，2，4，8，16，24，新的可以是32    
    DWORD   biCompression;      //压缩方式，可以是0，1，2，其中0表示不压缩    
    DWORD   biSizeImage;        //实际位图数据占用的字节数    
    LONG    biXPelsPerMeter;    //X方向分辨率    
    LONG    biYPelsPerMeter;    //Y方向分辨率    
    DWORD   biClrUsed;          //使用的颜色数，如果为0，则表示默认值(2^颜色位数)    
    DWORD   biClrImportant;     //重要颜色数，如果为0，则表示所有颜色都是重要的    
};

#define WIDTHBYTES(bits) (((bits) + 31) / 32 * 4)

class bitmap_image 
{
protected:
    int _width;
    int _height;
    DWORD** _pixels; // 二维数组存储RGB值
    DWORD* colorTable; // 存储颜色表（RGB格式）

public:
    bitmap_image(const string& filename);
    ~bitmap_image();

    void load(const string& filename);
    void read_pixel_data(ifstream& file, const BITMAPINFOHEADERo& bih);

    DWORD get_pixel(int row, int col) const;
    int width() const;
    int height() const;
};

