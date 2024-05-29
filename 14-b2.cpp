/* 2250748 �����q �Ű� */
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>
/* �������Ҫ���˴��������ͷ�ļ� */

using namespace std;

/* �����峣����/�궨�壬����������ȫ�ֱ��� */
const char RANKS[13] = { '3','4','5','6','7','8','9','T','J','Q','K','A','2' };

#ifdef _WIN32
const char SUITS[4] = { 3,4,5,6 };
#elif defined(__linux__)
const char SUITS[4] = { 'H','D','C','S'};
#endif

const unsigned long long CARD = 1ULL;
/* ��������Լ���Ҫ�ĺ��� */

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡĳ����ҵ�������Ϣ������ǵ���������ӱ��
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int print(const char* prompt, const bool landlord, const unsigned long long player)
{
    /* ֻ�����岻���������������͵ļ򵥱��������ܶ�������������ṹ�塢string�� */
    cout << prompt;
    for (int i = 0; i < 54; i++) {
        if (player & (CARD << i)) {
            if (i < 52) {
                cout << SUITS[i / 13] << RANKS[i % 13] << " ";
            }
            else if (i == 52) {
                cout << "BJ ";
            }
            else {
                cout << "RJ ";
            }
        }
    }
    if (landlord) {
        cout << "(����)";
    }
    cout << endl;
    return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ƣ����������������
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int deal(unsigned long long* player) {
    srand((unsigned int)time(NULL));

    int carded = 0; // �ѷ�������
    int cur_player; // ��ǰ����Ƶ����
    int cur_card;   // ��ǰ������
    bool flag; // ���Ƿ��Ѿ�����ĳλ���

    while (carded < 51) {
        cur_player = carded % 3;
        do {
            flag = false;
            cur_card = rand() % 54;
            for (int i = 0; i < 3; i++) {
                if (player[i] & (CARD << cur_card)) { // ����������Ѿ���������ĳλ���
                    flag = true;
                    break;
                }
            }
        } while (flag); // ��֤ÿ����ֻ����һ��

        player[cur_player] |= (CARD << cur_card); // ����ǰ��ҷ���
        carded++;

        // ÿ����3���ƴ�ӡһ����ҵ���
        if (carded % 3 == 0) {
            cout << "��" << carded / 3 << "�ֽ�����" << endl;
            print("�׵��ƣ�", false, player[0]);
            print("�ҵ��ƣ�", false, player[1]);
            print("�����ƣ�", false, player[2]);
        }
    }

    // ���û�ѡ�����
    int landlord;
    cout << "��ѡ����� (0-��, 1-��, 2-��): ";
    cin >> landlord;

    while (carded < 54) {//����ʣ�µ�����
        cur_player = landlord;
        do {
            flag = false;
            cur_card = rand() % 54;
            for (int i = 0; i < 3; i++) {
                if (player[i] & (CARD << cur_card)) { // ����������Ѿ���������ĳλ���
                    flag = true;
                    break;
                }
            }
        } while (flag); // ��֤ÿ����ֻ����һ��

        player[cur_player] |= (CARD << cur_card); // ����ǰ��ҷ���
        carded++;
    }

    return landlord;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main��������׼�޸�
 ***************************************************************************/
int main()
{
    unsigned long long player[3] = { 0 }; //���������ҵķ�����Ϣ
    int landlord; //����0-2��ʾ�ĸ�����ǵ���

    cout << "���س�����ʼ����";
    while (getchar() != '\n')
        ;

    landlord = deal(player);
    print("�׵��ƣ�", (landlord == 0), player[0]);
    print("�ҵ��ƣ�", (landlord == 1), player[1]);
    print("�����ƣ�", (landlord == 2), player[2]);

    return 0;
}