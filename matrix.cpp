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
	int line;
	int column;
	int m[10][10];

	Matrix() {

	}

	Matrix(int l, int c) {
		line = l;
		column = c;
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < column; j++)
			{
				m[i][j] = rand() % (lowup - lowdown)-(-lowdown);
			}
		}
	}
	//0矩阵
	Matrix(int l, int c,bool flag) {
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

	//指定矩阵，需要手动调整a[][]
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

	//从零行零列开始
	Matrix getAs(int x,int y) {
		Matrix k(line-1,column-1,true);
		//i,j是伴随矩阵，p，q是原A矩阵
	
		for (int i = 0,p=0; i < line - 1; i++) {
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

	int getA(int n) {
		int sum = 0;
		
		if (n == 1) {
			return this->m[0][0];
		}

		for (int j = 0; j < n; j++)
		{
			int k = this->m[0][j] * pow(-1, 0 + j);
			
			sum += this->m[0][j] * pow(-1, 0 + j) * this->getAs(0, j).getA(this->getAs(0, j).line);
			
		}
		return sum;
	}
	

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
				cout << "--------------------------------------------\n";
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
				printf_s("%15d,", a.m[i][j]+b.m[i][j]);
			}
			cout << endl;
		}
		cout << "--------------------------------------------\n";
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
				cout << "--------------------------------------------\n";
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
		cout << "--------------------------------------------\n";
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
		mul = Matrix(a.line, b.column,true);
	}

	void calc() {

		for (int i = 0; i < a.line; i++)
		{
			for (int j = 0; j < b.column; j++)
			{
				cout << "Multiplication :line:" << i << " column:" << j << endl;
				cout << "********************************************\n";
				for (int k = 0; k < a.column; k++) {
					mul.m[i][j] +=a.m[i][k]*b.m[k][j];
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
				cout << "\n--------------------------------------------\n";
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
				printf_s("%15d,",mul.m[i][j]);
			}
			cout << endl;
		}
		cout << "--------------------------------------------\n";
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
		Matrix k(a.column, a.line,true);

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
				cout << "--------------------------------------------\n";
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
		cout << "--------------------------------------------\n";
	}
};

class Inverse
{
public:
	Matrix a;
	int A;
	Matrix Astar;
	Matrix inv;

	Inverse(Matrix m1) {
		a = m1;
		A = a.getA(a.line);
	}

	void calc() {
		cout << "Inverse :line:" << a.line << " column:" << a.column << endl;
		cout << "********************************************\n|A*|=\n";
		for (int i = 0; i < a.line; i++) {
			cout << "|";
			for (int j = 0; j < a.column; j++) {
				Astar.m[i][j] = pow(-1,i+j)*a.getAs(i, j).getA(a.getAs(i, j).line);
				printf_s("(A%d%d：%3d)    ", i + 1, j + 1, Astar.m[i][j]);
			}
			cout << "|" << endl;
		}
		cout << "--------------------------------------------\n";

		A = a.getA(a.line);
		printf_s("|A|=%d\n", A);
		cout << "--------------------------------------------\n";

		if (A == 0) {
			cout << "None\n";
			return;
		}

		printf_s("|A^-1|=\n");
		for (int i = 0; i < a.line; i++) {
			cout << "|";
			for (int j = 0; j < a.column; j++) {
				if ((Division(A, Astar.m[i][j]) ==A && abs(Astar.m[i][j])>=abs(A))   || (Division(A, Astar.m[i][j]) == -A && abs(Astar.m[i][j]) >= abs(A))    ||   Astar.m[i][j] == 0)
				{
					printf_s("A(%d,%d)：%+12d    ", i + 1, j + 1, Astar.m[i][j]/A );
				}
				else {
					if (Astar.m[i][j] < 0 && A < 0) {
						printf_s("A(%d,%d)：(%+3d)/(%+3d)    ", i + 1, j + 1, Astar.m[i][j] / Division(A, Astar.m[i][j]), A / Division(A, Astar.m[i][j]));
					}
					else
						printf_s("A(%d,%d)：(%+3d)/(%+3d)    ", i + 1, j + 1, Astar.m[i][j] / Division(A, Astar.m[i][j]), A / Division(A, Astar.m[i][j]));
				}
			}
			cout << "|" << endl;
		}
		cout << "--------------------------------------------\n";
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

			Matrix m8(n,n);
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
		system("pause");
		system("cls");
	}

	
	return 0;
}