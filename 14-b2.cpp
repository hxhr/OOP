/* 2250748 王渝鹮 信安 */
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>
/* 如果有需要，此处可以添加头文件 */

using namespace std;

/* 允许定义常变量/宏定义，但不允许定义全局变量 */
const char RANKS[13] = { '3','4','5','6','7','8','9','T','J','Q','K','A','2' };

#ifdef _WIN32
const char SUITS[4] = { 3,4,5,6 };
#elif defined(__linux__)
const char SUITS[4] = { 'H','D','C','S'};
#endif

const unsigned long long CARD = 1ULL;
/* 可以添加自己需要的函数 */

/***************************************************************************
  函数名称：
  功    能：打印某个玩家的牌面信息，如果是地主，后面加标记
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int print(const char* prompt, const bool landlord, const unsigned long long player)
{
    /* 只允许定义不超过三个基本类型的简单变量，不能定义数组变量、结构体、string等 */
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
        cout << "(地主)";
    }
    cout << endl;
    return 0;
}

/***************************************************************************
  函数名称：
  功    能：发牌（含键盘输入地主）
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int deal(unsigned long long* player) {
    srand((unsigned int)time(NULL));

    int carded = 0; // 已发的牌数
    int cur_player; // 当前获得牌的玩家
    int cur_card;   // 当前发的牌
    bool flag; // 牌是否已经发给某位玩家

    while (carded < 51) {
        cur_player = carded % 3;
        do {
            flag = false;
            cur_card = rand() % 54;
            for (int i = 0; i < 3; i++) {
                if (player[i] & (CARD << cur_card)) { // 如果这张牌已经被发给了某位玩家
                    flag = true;
                    break;
                }
            }
        } while (flag); // 保证每张牌只被发一次

        player[cur_player] |= (CARD << cur_card); // 给当前玩家发牌
        carded++;

        // 每发完3张牌打印一次玩家的牌
        if (carded % 3 == 0) {
            cout << "第" << carded / 3 << "轮结束：" << endl;
            print("甲的牌：", false, player[0]);
            print("乙的牌：", false, player[1]);
            print("丙的牌：", false, player[2]);
        }
    }

    // 让用户选择地主
    int landlord;
    cout << "请选择地主 (0-甲, 1-乙, 2-丙): ";
    cin >> landlord;

    while (carded < 54) {//补发剩下的三张
        cur_player = landlord;
        do {
            flag = false;
            cur_card = rand() % 54;
            for (int i = 0; i < 3; i++) {
                if (player[i] & (CARD << cur_card)) { // 如果这张牌已经被发给了某位玩家
                    flag = true;
                    break;
                }
            }
        } while (flag); // 保证每张牌只被发一次

        player[cur_player] |= (CARD << cur_card); // 给当前玩家发牌
        carded++;
    }

    return landlord;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数，不准修改
 ***************************************************************************/
int main()
{
    unsigned long long player[3] = { 0 }; //存放三个玩家的发牌信息
    int landlord; //返回0-2表示哪个玩家是地主

    cout << "按回车键开始发牌";
    while (getchar() != '\n')
        ;

    landlord = deal(player);
    print("甲的牌：", (landlord == 0), player[0]);
    print("乙的牌：", (landlord == 1), player[1]);
    print("丙的牌：", (landlord == 2), player[2]);

    return 0;
}