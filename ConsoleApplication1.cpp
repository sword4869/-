#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<cmath>
#include<Windows.h>
#include<algorithm>
using namespace std;

//矩阵元素区间
int lowdown, lowup;

//求最大公约数
int Division(int a, int b) {
	if (a < b) swap(a, b);		//a要大于等于b
	while (b != 0) {
		int temp;
		temp = a % b;
		a = b;
		b = temp;			//当a%b=0时，a是最大公约数，b是相除到0
	}
	return a;
}

class Matrix
{
public:
	//行数
	int line;
	//列数
	int column;
	//二维数组存储矩阵元素
	int m[10][10];

	Matrix() {

	}

	//生成一个l行c列的矩阵
	Matrix(int l, int c) {
		line = l;
		column = c;
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < column; j++)
			{
				m[i][j] = rand() % (lowup - lowdown) - (-lowdown);
			}
		}
	}

	//l行c列的0矩阵
	Matrix(int l, int c, bool flag) {
		line = l;
		column = c;
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < column; j++)
			{
				m[i][j] = 0;
			}
		}
	}

	//指定二维矩阵，需要调整矩阵的规模时请手动调整a[][]
	Matrix(int l, int c, int a[2][2]) {
		line = l;
		column = c;
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < column; j++) {
				m[i][j] = a[i][j];
			}
		}
	}

	//获得余子式M_ij矩阵
	//从零行零列开始
	Matrix getAs(int x, int y) {
		Matrix k(line - 1, column - 1, true);
		//i,j是伴随矩阵，p，q是原A矩阵

		for (int i = 0, p = 0; i < line - 1; i++) {
			for (int j = 0, q = 0; j < column - 1; j++) {
				if (p == x) {
					p++;
				}
				if (q == y) {
					q++;
				}
				k.m[i][j] = this->m[p][q];
				q++;
			}
			p++;
		}
		return k;
	}
	// 获得行列式的值A
	// 采用递归调用
	int getA(int n) {
		int sum = 0;

		if (n == 1) {
			return this->m[0][0];
		}

		for (int j = 0; j < n; j++)
		{
			// 行列式|A|=a_0j * 代数余子式A_0j
			sum += this->m[0][j] * pow(-1, 0 + j) * this->getAs(0, j).getA(this->getAs(0, j).line);
		}
		return sum;
	}

	// 矩阵乘一个数
	Matrix numberMul(int k) {
		Matrix temp(line, column);
		for (int i = 0; i < line; i++)
			for (int j = 0; j < column; j++)
				temp.m[i][j] = this->m[i][j] * k;
		return temp;
	}

	void print() {
		cout << "Matrix :line:" << line << " column:" << column << endl;
		cout << "********************************************\n";
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < column; j++)
			{
				printf_s("%15d,", m[i][j]);
			}
			cout << endl;
		}
		cout << "--------------------------------------------\n";
	}
};

class Addition
{
public:
	Matrix a, b;

	Addition(Matrix m1, Matrix m2) {
		a = m1;
		b = m2;
	}

	void calc() {
		
		system("pause");

		for (int i = 0; i < a.line; i++)
		{
			for (int j = 0; j < a.column; j++)
			{
				cout << "Addition :line:" << i << " column:" << j << endl;
				cout << "********************************************\n";
				for (int p = 0; p < a.line; p++) {
					for (int q = 0; q < a.column; q++) {
						if (p < i || p == i && q <= j)
							printf_s("(%+5d)+(%+5d),", a.m[p][q], b.m[p][q]);
						else
							printf_s("%15d,", 0);
					}
					cout << endl;
				}
				system("pause");
			}
			cout << endl;
		}
	}

	void print() {
		cout << "Addition :line:" << a.line << " column:" << a.column << endl;
		cout << "********************************************\n";
		for (int i = 0; i < a.line; i++)
		{
			for (int j = 0; j < a.column; j++)
			{
				printf_s("%15d,", a.m[i][j] + b.m[i][j]);
			}
			cout << endl;
		}
		system("pause");
	}
};

class Subtraction
{
public:
	Matrix a, b;

	Subtraction(Matrix m1, Matrix m2) {
		a = m1;
		b = m2;
	}

	void calc() {
		system("pause");
		for (int i = 0; i < a.line; i++)
		{
			for (int j = 0; j < a.column; j++)
			{
				cout << "Subtraction :line:" << i << " column:" << j << endl;
				cout << "********************************************\n";
				for (int p = 0; p < a.line; p++) {
					for (int q = 0; q < a.column; q++) {
						if (p < i || p == i && q <= j)
							printf_s("(%+5d)-(%+5d),", a.m[p][q], b.m[p][q]);
						else
							printf_s("%15d,", 0);
					}
					cout << endl;
				}
				system("pause");
			}
			cout << endl;
		}
	}

	void print() {
		cout << "Subtraction :line:" << a.line << " column:" << a.column << endl;
		cout << "********************************************\n";
		for (int i = 0; i < a.line; i++)
		{
			for (int j = 0; j < a.column; j++)
			{
				printf_s("%15d,", a.m[i][j] - b.m[i][j]);
			}
			cout << endl;
		}
		system("pause");
	}
};

class Multiplication
{
public:
	Matrix a, b;
	Matrix mul;

	Multiplication(Matrix m1, Matrix m2) {
		a = m1;
		b = m2;
		mul = Matrix(a.line, b.column, true);
	}

	void calc() {
		system("pause");
		for (int i = 0; i < a.line; i++)
		{
			for (int j = 0; j < b.column; j++)
			{
				cout << "Multiplication :line:" << i << " column:" << j << endl;
				cout << "********************************************\n";
				for (int k = 0; k < a.column; k++) {
					mul.m[i][j] += a.m[i][k] * b.m[k][j];
				}

				for (int p = 0; p < a.line; p++) {
					for (int q = 0; q < b.column; q++) {
						printf_s("%15d,", mul.m[p][q]);
					}
					cout << endl;
				}
				for (int k = 0; k < a.column; k++) {
					printf_s("(%+5d)*(%5d)", a.m[i][k], b.m[k][j]);
					if (k < a.column - 1) {
						cout << "+";
					}
				}
				system("pause");
			}
			cout << endl;
		}
	}

	void print() {
		cout << "Multiplication :line:" << a.line << " column:" << b.column << endl;
		cout << "********************************************\n";
		for (int i = 0; i < a.line; i++)
		{
			for (int j = 0; j < b.column; j++)
			{
				printf_s("%15d,", mul.m[i][j]);
			}
			cout << endl;
		}
		system("pause");
	}
};

class Transpose
{
public:
	Matrix a;

	Transpose(Matrix m1) {
		a = m1;
	}

	void calc() {
		system("pause");
		Matrix k(a.column, a.line, true);

		for (int i = 0; i < a.column; i++)
		{
			for (int j = 0; j < a.line; j++)
			{
				k.m[i][j] = a.m[j][i];
				cout << "Transpose :line:" << i << " column:" << j << endl;
				cout << "********************************************\n";
				for (int i = 0; i < k.line; i++)
				{
					for (int j = 0; j < k.column; j++)
					{
						printf_s("%15d,", k.m[i][j]);
					}
					cout << endl;
				}
				system("pause");
			}
			cout << endl;
		}

	}

	void print() {
		cout << "Transpose :line:" << a.column << " column:" << a.line << endl;
		cout << "********************************************\n";
		for (int i = 0; i < a.column; i++)
		{
			for (int j = 0; j < a.line; j++)
			{
				printf_s("%15d,", a.m[j][i]);
			}
			cout << endl;
		}
		system("pause");
	}
};

class Inverse
{
public:
	// 原矩阵
	Matrix a;
	// 矩阵的行列式的值A
	int A;
	//A的伴随矩阵
	Matrix Astar;
	// 逆矩阵
	Matrix inv;

	Inverse(Matrix m1) {
		a = m1;
		A = a.getA(a.line);
	}

	void calc() {
		system("pause");
		// A的伴随矩阵A*=代数余子式Aij=(-1)^(i+j)乘以余子式Mij
		for (int i = 0; i < a.line; i++) {

			for (int j = 0; j < a.column; j++) {
				Astar.m[j][i] = pow(-1, i + j) * a.getAs(i, j).getA(a.getAs(i, j).line);
			}
		}

		cout << "Inverse :line:" << a.line << " column:" << a.column << endl;
		cout << "********************************************\nA*=\n";
		for (int i = 0; i < a.line; i++) {

			for (int j = 0; j < a.column; j++) {
				
				printf_s("(A%d%d：%3d)    ", j+1,i+1, Astar.m[i][j]);
			}
			cout << endl;
		}
		system("pause");

		printf_s("|A|=%d\n", A);
		system("pause");


		// A=0无逆矩阵
		if (A == 0) {
			cout << "None\n";
			return;
		}

		// A^-1逆矩阵=1/|A| *伴随矩阵
		printf_s("A^-1=\n");
		for (int i = 0; i < a.line; i++) {
			for (int j = 0; j < a.column; j++) {

				// 这些输出是为了输出逆矩阵的结果

				// 分这么多if是为了好看

				// 如果可以直接整除，即4/2  4/-2  0/5的情况，就直接输出相除的结果

				if ((Division(A, Astar.m[i][j]) == A && abs(Astar.m[i][j]) >= abs(A)) || (Division(A, Astar.m[i][j]) == -A && abs(Astar.m[i][j]) >= abs(A)) || Astar.m[i][j] == 0)
				{
					printf_s("%+12d    ", Astar.m[i][j] / A);
				}
				// 如果不可以整除，用分数表示

				// 考虑到9/6可以化简为3/2的情况，就用9和6分别除以最大公约数3
				else {
					printf_s("(%+3d)/(%+3d)    ", Astar.m[i][j] / Division(A, Astar.m[i][j]), A / Division(A, Astar.m[i][j]));
				}
			}
			cout << endl;
		}
		system("pause");
	}
};

int main(int argc, char* argv[])
{
	srand((unsigned)time(NULL));

	cout << "输入矩阵元素随机生成的区间a和b（可以为负数）：" << endl;
	cin >> lowdown >> lowup;


	while (true)
	{
		printf_s("Please choice your operator: \n"
			"\t0), Quit\n"
			"\t1), Addition\n"
			"\t2), Subtraction\n"
			"\t3), Multiplication\n"
			"\t4), Transpose\n"
			"\t5), Inverse\n\n"
		);

		int code;
		cin >> code;

		switch (code)
		{
		case 0:
		{// quit
			return 0;
		}
		case 1:
		{// addition
			cout << "enter your line and colum: ";

			int line, column;
			cin >> line >> column;

			Matrix m1(line, column);
			Matrix m2(line, column);

			m1.print();
			m2.print();

			Addition add(m1, m2);
			add.calc();
			add.print();
			break;
		}
		case 2:
		{// subtraction
			cout << "enter your line and colum: ";

			int line, column;
			cin >> line >> column;

			Matrix m3(line, column);
			Matrix m4(line, column);

			m3.print();
			m4.print();

			Subtraction sub(m3, m4);
			sub.calc();
			sub.print();
			break;
		}
		case 3:
		{// multiplication
			cout << "First Matrix:enter your line and colum: ";

			int line1, column1;
			cin >> line1 >> column1;

			cout << "Second Matrix:enter your colum: ";

			int line2, column2;
			line2 = column1;
			cin >> column2;

			Matrix m5(line1, column1);
			Matrix m6(line2, column2);

			m5.print();
			m6.print();

			Multiplication mul(m5, m6);
			mul.calc();
			mul.print();

			break;
		}
		case 4:
		{// transpose
			cout << "enter your line and colum: ";

			int line, column;
			cin >> line >> column;

			Matrix m7(line, column);
			m7.print();

			Transpose tra(m7);
			tra.calc();
			tra.print();

			break;
		}
		case 5:
		{// inverse
			cout << "enter your nth order: ";

			int n;
			cin >> n;

			Matrix m8(n, n);
			m8.print();

			Inverse inv(m8);
			inv.calc();
			break;
		}
		default:
		{
			break;
		}
		}
		system("cls");
	}


	return 0;
}