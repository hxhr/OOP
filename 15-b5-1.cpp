/* 2250748 王渝鹮 信安 */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int check_form(const string& filename) 
{
    ifstream file(filename, ios::binary);
    if (!file) {
        return 4; // 返回无法打开文件
    }

    int flag_l = 1; // Linux格式标志
    int flag_w = 1; // Windows格式标志
    int ch;
    int prev = EOF; // 存储前一个字符，初始为EOF

    while ((ch = file.get()) != EOF) {
        if (ch == '\n') {
            if (prev == '\r') { // 如果当前字符是\n且前一个字符是\r，则为Windows格式
                flag_l = 0; // 置Linux格式标志为false
            }
            else { // 如果当前字符是\n且前一个字符不是\r，则为Linux格式
                flag_w = 0; // 置Windows格式标志为false
            }
        }
        prev = ch; // 更新前一个字符
    }

    file.close();
    // 根据标志位的情况返回对应的格式
    if (flag_l && flag_w) return 3; // 两个标志都为true，说明没有遇到任何换行符，无法识别格式
    if (flag_l) return 1; // Linux格式标志为true
    if (flag_w) return 2; // Windows格式标志为true
    return 3; // 默认返回无法识别格式
}


int wtol(const string& inputFile, const string& outputFile) 
{
    ifstream in(inputFile, ios::binary);
    ofstream out(outputFile, ios::binary);

    int num = 0;//记录转换的次数
    char ch;
    while (in.get(ch)) {
        if (ch != '\r') {
            out.put(ch);
        }
        else {
            num++;
        }
    }
    return num;
    in.close();
    out.close();
}

int ltow(const string& inputFile, const string& outputFile)
{
    ifstream in(inputFile, ios::binary);
    ofstream out(outputFile, ios::binary);
    int num = 0;//记录转换的次数
    char ch;
    while (in.get(ch)) {
        if (ch == '\n') {
            out.put('\r');
            num++;
        }
        out.put(ch);
    }
    in.close();
    out.close();

    return num;
}

void print_usage(const string& name)
{
    cout << "Usage : " << name << " --check 文件名 | --convert { wtol|ltow } 源文件名 目标文件名" << endl;
    cout << "        " << name << " --check a.txt" << endl;
    cout << "        " << name << " --convert wtol a.win.txt a.linux.txt" << endl;
    cout << "        " << name << " --convert ltow a.linux.txt a.win.txt" << endl;

}

int main(int argc, char* argv[]) 
{
    string name = argv[0];

    if (argc != 3 && argc != 5) {
        print_usage(name);
        return -1;
    }

    string option = argv[1];
    string inputFile = argv[2];
    
    //仅check
    if (argc == 3) {
        if (option != "--check") {
            print_usage(name);
            return -1;
        }
        switch (check_form(inputFile)) {
            case 1:
                cout << "Linux格式" << endl;
                return 0;
                break;
            case 2:
                cout << "Windows格式" << endl;
                return 0;
                break;
            case 3:
                cout << "文件格式无法识别" << endl;
                return 0;
                break;
            case 4:
                cout << "文件打开失败" << endl;
                return 0;
                break;
        }

    }
    else {//证明命令是convert，那要先check后convert，且一定是5
        string way = argv[2];//转换方式 wtol或ltow
        string input = argv[3];//输入文件
        string output = argv[4];//输出文件
        //先把错误情况排除
        if (!(option == "--convert") || !(way == "wtol" || way == "ltow")) {
            print_usage(name);
            return -1;
        }

        if (way == "wtol") {//wtol
            if (check_form(input) == 4) {
                cout << "文件打开失败" << endl;
                return 0;
            }
            else if (check_form(input) == 3 || check_form(input) == 1) {
                cout << "文件格式无法识别" << endl;
                return 0;
            }
            int num = wtol(input, output);
            cout << "转换完成，去除" << num << "个0x0D" << endl;
            return 0;

        }
        else {//ltow
            //根据demo，打印错误提示信息不需要明确是什么格式，只有无法识别或者打开失败两种
            if (check_form(input) == 4) {
                cout << "文件打开失败" << endl;
                return 0;
            }
            else if (check_form(input) == 3 || check_form(input) == 2) {
                cout << "文件格式无法识别" << endl;
                return 0;
            }
            int num = ltow(input, output);
            cout << "转换完成，加入" << num << "个0x0D" << endl;
            return 0;

        }

    }

    return 0;
}
