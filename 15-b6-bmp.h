/* �Ű� 2250748 �����q */

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
    //��һ�����type���뵥��������Ϊ�ṹ����ֽڶ���
    //WORD    bfType;        // �ļ����ͣ�������0x4D42�����ַ�'BM'
    DWORD  bfSize;          //�ļ���С    
    WORD   bfReserved1;     //�����֣�������    
    WORD   bfReserved2;     //�����֣�ͬ��    
    DWORD  bfOffBits;       //ʵ��λͼ���ݵ�ƫ���ֽ�������ǰ�������ֳ���֮��    
};

struct BITMAPINFOHEADERo
{
    DWORD   biSize;             //ָ���˽ṹ��ĳ��ȣ�Ϊ40    
    LONG    biWidth;            //λͼ��    
    LONG    biHeight;           //λͼ��    
    WORD    biPlanes;           //ƽ������Ϊ1    
    WORD    biBitCount;         //������ɫλ����������1��2��4��8��16��24���µĿ�����32    
    DWORD   biCompression;      //ѹ����ʽ��������0��1��2������0��ʾ��ѹ��    
    DWORD   biSizeImage;        //ʵ��λͼ����ռ�õ��ֽ���    
    LONG    biXPelsPerMeter;    //X����ֱ���    
    LONG    biYPelsPerMeter;    //Y����ֱ���    
    DWORD   biClrUsed;          //ʹ�õ���ɫ�������Ϊ0�����ʾĬ��ֵ(2^��ɫλ��)    
    DWORD   biClrImportant;     //��Ҫ��ɫ�������Ϊ0�����ʾ������ɫ������Ҫ��    
};

#define WIDTHBYTES(bits) (((bits) + 31) / 32 * 4)

class bitmap_image 
{
protected:
    int _width;
    int _height;
    DWORD** _pixels; // ��ά����洢RGBֵ
    DWORD* colorTable; // �洢��ɫ��RGB��ʽ��

public:
    bitmap_image(const string& filename);
    ~bitmap_image();

    void load(const string& filename);
    void read_pixel_data(ifstream& file, const BITMAPINFOHEADERo& bih);

    DWORD get_pixel(int row, int col) const;
    int width() const;
    int height() const;
};

