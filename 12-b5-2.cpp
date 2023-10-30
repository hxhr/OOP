/* 信安 2250748 王渝鹮 */
#include <iostream>
#include <iomanip>
using namespace std;

const char* sp = "=====================================";

// 打印矩阵
template <typename T, size_t Rows, size_t Cols>
void matrix_print(const char* prompt, T(&matrix)[Rows][Cols]) {
	cout << prompt << endl;
	for (size_t i = 0; i < Rows; i++) {
		for (size_t j = 0; j < Cols; j++) {
			cout << setw(8) << right << matrix[i][j];
		}
		cout << endl;
	}
}

// 矩阵加法
template <typename T, size_t Rows, size_t Cols>
void matrix_addition(T(&result)[Rows][Cols], T(&matrix1)[Rows][Cols], T(&matrix2)[Rows][Cols]) {
	for (size_t i = 0; i < Rows; i++) {
		for (size_t j = 0; j < Cols; j++) {
			result[i][j] = matrix1[i][j] + matrix2[i][j];
		}
	}
}

// 矩阵乘法
//关键是那个中间变量的类型longlong
//不同类型的乘法在计算时会发生隐式转换，int就有可能溢出，但longlong不会
template <typename T1, typename T2, size_t Rows1, size_t Cols1, size_t Cols2>
void matrix_multiplication(int(&result)[Rows1][Cols2], T1(&matrix1)[Rows1][Cols1], T2(&matrix2)[Cols1][Cols2]) {
	for (size_t i = 0; i < Rows1; i++) {
		for (size_t j = 0; j < Cols2; j++) {
			long long temp_result = 0; // 使用long long作为中间结果
			for (size_t k = 0; k < Cols1; k++) {
				temp_result += static_cast<long long>(matrix1[i][k]) * static_cast<long long>(matrix2[k][j]);
			}
			result[i][j] = static_cast<int>(temp_result);
		}
	}
}



/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数不准更改
***************************************************************************/
int main()
{
	int t1[3][4] = {
		{1,2,3,4},
		{5,6,7,8},
		{9,10,11,12}
	};
	int t2[3][4] = {
		{12,11,10,9},
		{8,7,6,5},
		{4,3,2,1}
	};
	int t3[4][2] = {
		{1, 2},
		{3, 4},
		{5, 6},
		{7, 8}
	};
	int t_add[3][4], t_mul[3][2];

	cout << sp << endl;
	matrix_print("加法运算，源矩阵1：", t1);
	matrix_print("加法运算，源矩阵2：", t2);
	matrix_addition(t_add, t1, t2);	//将t1和t2的和放入t_add中，人工保证三个矩阵行列一致
	matrix_print("加法运算，和矩阵 ：", t_add);
	cout << sp << endl;
	matrix_print("乘法运算，源矩阵1：", t1);
	matrix_print("乘法运算，源矩阵2：", t3);
	matrix_multiplication(t_mul, t1, t3);	//将t1和t2的和放入t_add中，人工保证三个矩阵行列一致
	matrix_print("乘法运算，积矩阵 ：", t_mul);
	cout << sp << endl;

	double d1[2][4] = {
		{1.1, 2.2, 3.3, 4.4},
		{5.5 ,6.6, 7.7, 8.8}
	};
	double d2[2][4] = {
		{8.8, 7.7, 6.6, 5.5},
		{4.4, 3.3, 2.2, 1.1}
	};
	double d_add[2][4];
	/* 不要问为什么矩阵乘法数据类型不同，故意的 */
	float f3[4][3] = {
		{12.12f, 11.11f, 10.10f},
		{9.9f, 8.8f, 7.7f},
		{6.6f, 5.5f, 4.4f},
		{3.3f, 2.2f, 1.1f}
	};
	int i_mul[2][3];

	matrix_print("加法运算，源矩阵1：", d1);
	matrix_print("加法运算，源矩阵2：", d2);
	matrix_addition(d_add, d1, d2);	//将d1和d2的和放入d_add中，人工保证三个矩阵行列一致
	matrix_print("加法运算，和矩阵 ：", d_add);
	cout << sp << endl;
	matrix_print("乘法运算，源矩阵1：", d1);
	matrix_print("乘法运算，源矩阵2：", f3);
	matrix_multiplication(i_mul, d1, f3);	//将t1和t2的和放入t_add中，人工保证三个矩阵行列一致
	matrix_print("乘法运算，积矩阵 ：", i_mul);
	cout << sp << endl;

	return 0;
}
