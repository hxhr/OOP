/* 2250748 �����q �Ű� */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int check_form(const string& filename) 
{
    ifstream file(filename, ios::binary);
    if (!file) {
        return 4; // �����޷����ļ�
    }

    int flag_l = 1; // Linux��ʽ��־
    int flag_w = 1; // Windows��ʽ��־
    int ch;
    int prev = EOF; // �洢ǰһ���ַ�����ʼΪEOF

    while ((ch = file.get()) != EOF) {
        if (ch == '\n') {
            if (prev == '\r') { // �����ǰ�ַ���\n��ǰһ���ַ���\r����ΪWindows��ʽ
                flag_l = 0; // ��Linux��ʽ��־Ϊfalse
            }
            else { // �����ǰ�ַ���\n��ǰһ���ַ�����\r����ΪLinux��ʽ
                flag_w = 0; // ��Windows��ʽ��־Ϊfalse
            }
        }
        prev = ch; // ����ǰһ���ַ�
    }

    file.close();
    // ���ݱ�־λ��������ض�Ӧ�ĸ�ʽ
    if (flag_l && flag_w) return 3; // ������־��Ϊtrue��˵��û�������κλ��з����޷�ʶ���ʽ
    if (flag_l) return 1; // Linux��ʽ��־Ϊtrue
    if (flag_w) return 2; // Windows��ʽ��־Ϊtrue
    return 3; // Ĭ�Ϸ����޷�ʶ���ʽ
}


int wtol(const string& inputFile, const string& outputFile) 
{
    ifstream in(inputFile, ios::binary);
    ofstream out(outputFile, ios::binary);

    int num = 0;//��¼ת���Ĵ���
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
    int num = 0;//��¼ת���Ĵ���
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
    cout << "Usage : " << name << " --check �ļ��� | --convert { wtol|ltow } Դ�ļ��� Ŀ���ļ���" << endl;
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
    
    //��check
    if (argc == 3) {
        if (option != "--check") {
            print_usage(name);
            return -1;
        }
        switch (check_form(inputFile)) {
            case 1:
                cout << "Linux��ʽ" << endl;
                return 0;
                break;
            case 2:
                cout << "Windows��ʽ" << endl;
                return 0;
                break;
            case 3:
                cout << "�ļ���ʽ�޷�ʶ��" << endl;
                return 0;
                break;
            case 4:
                cout << "�ļ���ʧ��" << endl;
                return 0;
                break;
        }

    }
    else {//֤��������convert����Ҫ��check��convert����һ����5
        string way = argv[2];//ת����ʽ wtol��ltow
        string input = argv[3];//�����ļ�
        string output = argv[4];//����ļ�
        //�ȰѴ�������ų�
        if (!(option == "--convert") || !(way == "wtol" || way == "ltow")) {
            print_usage(name);
            return -1;
        }

        if (way == "wtol") {//wtol
            if (check_form(input) == 4) {
                cout << "�ļ���ʧ��" << endl;
                return 0;
            }
            else if (check_form(input) == 3 || check_form(input) == 1) {
                cout << "�ļ���ʽ�޷�ʶ��" << endl;
                return 0;
            }
            int num = wtol(input, output);
            cout << "ת����ɣ�ȥ��" << num << "��0x0D" << endl;
            return 0;

        }
        else {//ltow
            //����demo����ӡ������ʾ��Ϣ����Ҫ��ȷ��ʲô��ʽ��ֻ���޷�ʶ����ߴ�ʧ������
            if (check_form(input) == 4) {
                cout << "�ļ���ʧ��" << endl;
                return 0;
            }
            else if (check_form(input) == 3 || check_form(input) == 2) {
                cout << "�ļ���ʽ�޷�ʶ��" << endl;
                return 0;
            }
            int num = ltow(input, output);
            cout << "ת����ɣ�����" << num << "��0x0D" << endl;
            return 0;

        }

    }

    return 0;
}
