/* 2250748 王渝鹮 信安 */
/* 2254275 陶鸿周 2251882 聂师扬 2253716 欧佳音 2151753 彭坤宇 2050215 吴樾强 */
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
    char filename[256];
    cerr << "文件名以下形式均可以:"<<endl;
    //双斜杠才能用
    cerr << "    a.txt                     : 不带路径形式" << endl;
    cerr << "    ..\\data\\b.dat             : 相对路径形式" << endl;
    cerr << "    C:\\Windows\\System32\\c.dat : 绝对路径形式" << endl;
    cerr << "请输入文件名 : ";
    cin.getline(filename, sizeof(filename));

    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "输入文件" << filename<<"打开失败！" << endl;
        return 1;
    }

    unsigned char ch;
    unsigned int count = 0;//很有意思 int就不行
    int address = 0;
    char line[17]; // 用于存储ASCII字符
    line[16] = '\0'; // 确保字符串以null结束

    cout << hex << uppercase;
    while (file.get((char&)ch)) {//(int)(ch = file.get()) != EOF
        if (count % 16 == 0) {
            if (count > 0) {
                cout << " " << line << endl;
            }
            cout << setw(8) << setfill('0') << hex << address << ":  ";
            address += 16;
        }

        cout << setw(2) << setfill('0') << hex << static_cast<int>(ch) << " ";
        line[count % 16] = (ch >= 33 && ch <= 126) ? ch : '.'; // 只打印可打印字符

        if (count % 16 == 7) {
            if (file.peek() != EOF) {
                cout << "- ";
            }
        }
        count++;
    }

    if (count % 16 != 0) {
        int padding = 3 * (16 - count % 16);
        if (count % 16 <= 8) padding += 2;
        for (int i = 0; i < padding; ++i) {
            cout << ' ';
        }
        line[count % 16] = '\0';
    }

    cout << " " << line << endl;

    file.close();
    return 0;
}
