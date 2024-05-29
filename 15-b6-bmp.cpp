/* �Ű� 2250748 �����q */
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "15-b6-bmp.h"
using namespace std;

bitmap_image::bitmap_image(const string& filename) : _pixels(nullptr), colorTable(nullptr)
{
    load(filename);
}

bitmap_image::~bitmap_image() 
{
    if (colorTable) {
        delete[] colorTable;
    }
    if (_pixels) {
        for (int i = 0; i < _height; ++i) {
            delete[] _pixels[i];
        }
        delete[] _pixels;
    }
}

void bitmap_image::load(const string& filename) 
{
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    WORD bfType;
    file.read(reinterpret_cast<char*>(&bfType), sizeof(bfType)); // ������ȡbfType
    if (bfType != 0x4D42) { // ����ļ������Ƿ�ΪBM
        cerr << "Error: Not a valid bitmap file" << endl;
        return;
    }
    BITMAPFILEHEADERo bfh;//12
    BITMAPINFOHEADERo bih;//40

    file.read(reinterpret_cast<char*>(&bfh), sizeof(bfh));
    file.read(reinterpret_cast<char*>(&bih), sizeof(bih));

    _width = bih.biWidth;
    _height = bih.biHeight;

    // ������ɫ���ڴ�
    if (bih.biBitCount < 24) {
        int colorTableSize = (bih.biClrUsed == 0) ? (1 << bih.biBitCount) : bih.biClrUsed;
        colorTable = new DWORD[colorTableSize];
        //file.read(reinterpret_cast<char*>(colorTable), colorTableSize * sizeof(DWORD));
        //bmp����ɫ����BGR�洢������ϣ�������ͬʱ��ת����RGB
        for (int i = 0; i < colorTableSize; ++i) {
            BYTE bgr[4];
            file.read(reinterpret_cast<char*>(&bgr), sizeof(bgr));

            // ��BGRת��ΪRGB����ߵ�һ���ֽڲ���
            //��bbggrr00����00bbggrr
            colorTable[i] = (bgr[0] << 16) | (bgr[1] << 8) | bgr[2];
        }
    }

    // �������������ڴ�
    _pixels = new DWORD * [_height];
    for (int i = 0; i < _height; ++i) {
        _pixels[i] = new DWORD[_width];
    }

    read_pixel_data(file, bih);

    file.close();
}


void bitmap_image::read_pixel_data(ifstream& file, const BITMAPINFOHEADERo& bih) 
{
    int bytesPerRow = WIDTHBYTES(bih.biBitCount * _width);//λͼ��ʵ�ʿ��
    BYTE* rowData = new BYTE[bytesPerRow];

    for (int row = 0; row < _height; ++row) {
        file.read(reinterpret_cast<char*>(rowData), bytesPerRow);

        for (int col = 0; col < _width; ++col) {
            DWORD color = 0;
            int index = 0;
            BYTE temp;
            switch (bih.biBitCount) {
                //ÿ��������nλ��ʾ��8λ=1�ֽ�
                case 24:
                    index = col * 3;
                    color = (rowData[index + 2] << 16) | (rowData[index + 1] << 8) | rowData[index];
                    break;
                case 8:
                    color = colorTable[rowData[col]];
                    break;
                case 4:
                    index = col / 2;
                    temp = rowData[index];
                    if (col % 2 == 0) {
                        temp >>= 4;
                    }
                    else {
                        temp &= 0x0F;
                    }
                    color = colorTable[temp];
                    break;
                case 1:
                    index = col / 8;
                    BYTE mask = 0x80 >> (col % 8);
                    color = colorTable[(rowData[index] & mask) != 0];
                    break;
            }
            _pixels[_height - row - 1][col] = color;
        }
    }

    delete[] rowData;
}

DWORD bitmap_image::get_pixel(int row, int col) const 
{
    if (row < 0 || row >= _height || col < 0 || col >= _width) {
        return 0; // Խ����
    }
    return _pixels[row][col];
}

int bitmap_image::width() const 
{
    return _width;
}

int bitmap_image::height() const
{
    return _height;
}