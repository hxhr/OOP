///* 信安 2250748 王渝鹮 */
//#include <stdio.h>
//
//int main()
//{
//    /* 三个条件编译的相互位置可互换（例：目前#if满足是输出VS2022，允许先换为Linux）*/
//#if defined(_MSC_VER) && (_MSC_VER >= 1929)
//    printf("VS2022\n");
//#elif defined(__MINGW32__) || defined(__MINGW64__)
//    printf("Dev\n");
//#elif defined(__linux__)
//    printf("Linux\n");
//#endif
//
//    return 0;
//}