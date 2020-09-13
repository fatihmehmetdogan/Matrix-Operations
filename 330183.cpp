//330183 Fatih Mehmet DOGAN
//#pragma one

//#include "pch.h"
#include <iostream>
//#include <iostream>
#include <ctime>
//#include "pch.h"
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <string>
//#include "windows.h"
using namespace std;

template<typename T>
class Matrix
{
protected:
	int column;
	int line;
	T **AP;

public:
	Matrix();
	Matrix(int l, int c, int val);
	Matrix(int l, int c, char v);
	Matrix(int l, int c);
	void print();
	int det();
	void resize(int l, int c);
	void print(char* _dosya);
	void Tr();
	void emul(const Matrix<T>&);

	Matrix<T> operator+(const Matrix<T>&);
	Matrix<T> operator-(const Matrix<T>&);
	Matrix<T> operator*(const Matrix<T>&);


	Matrix<T> operator+(double);
	Matrix<T> operator-(double);
	Matrix<T> operator*(double);
	Matrix<T> operator/(double);
	Matrix<T> operator%(int);
	Matrix<T> operator^(int);

};

template <typename T>

void Matrix<T>::print(char* _dosya) {
	ofstream myfile;
	myfile.open(_dosya);
	for (int i = 0; i < this->line; i++) {
		for (int j = 0; j < this->column; j++)
		{
			myfile << AP[i][j];
			myfile << " ";
		}
		myfile << endl;
	}

	myfile.close();
}


template <typename T>
Matrix<T>::Matrix(int l, int c) {
	line = l;
	column = c;
	AP = new T*[c];
	for (int i = 0; i < l; i++)
		AP[i] = new T[c];
	for(int i=0; i<l; i++)
		for (int j = 0; j < c; j++)
		{
			AP[i][j] = 0;
		}

}


template <typename T>
Matrix<T>::Matrix(int l, int c, char v) {

	this->column = c; // Matris sütun değeri atandı.
	this->line = l; // Matris satır değeri atandı.


			// 10x10 birim matris oluşturuldu.
	AP = new T*[c];
	for (int i = 0; i < l; i++)
	{
		AP[i] = new T[c];
	}

	if (v == 'e') {
		if (l != c)
		{
			cout << "Birim matris olusturabilmek icin kare matris olmali";
		//	Sleep(5000);
			exit(0);

		}


		for (int i = 0; i < c; i++) {
			for (int j = 0; j < l; j++) {
				if (i == j)
				{
					AP[i][j] = 1;
				}
				else
				{
					AP[i][j] = 0;
				}
			}
		}

	}
	else if (v == 'r') {

		for (int i = 0; i < l; i++) {
			for (int j = 0; j < c; j++) {
				int x = rand() % 255 + 1;
				AP[i][j] = x;
			}
		}

	}

}


template <typename T>
void Matrix<T>::Tr()
{
	Matrix<T> m1(this->column, (this->line), 0);
	int a;
	for (int i = 0; i < this->line; i++)
		for (int j = 0; j < this->column; j++)
			m1.AP[j][i] = AP[i][j];
	AP = new T*[line];
	for (int i = 0; i < this->column; i++)
	{
		AP[i] = new T[line];
	}
	for (int i = 0; i < this->column; i++)
		for (int j = 0; j < this->line; j++)
			this->AP[i][j] = m1.AP[i][j];

	a = this->line;
	this->line = this->column;
	this->column = a;
}



template <typename T>
int Matrix<T>::det()
{
	int sag_determinant = 1;
	int sol_determinant = 1;
	int sag1 = 1;
	int sag2 = 1;
	int sag3 = 1;
	int sol1 = 1;
	int sol2 = 1;
	int sol3 = 1;
	int toplam_determinant;
	if (line == column)
	{
		Matrix<float> m1(this->line + 2, this->column);
		for (int i = 0; i < this->line; i++)
			for (int j = 0; j < this->column; j++)
				m1.AP[i][j] = AP[i][j];
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < this->column; j++)
				m1.AP[this->line + i][j] = AP[i][j];

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < line; j++) {
				if (i == 0)
				{
					sag1 = sag1 * m1.AP[i + j][j];
				}
				else if (i == 1)
				{
					sag2 = sag2 * m1.AP[i + j][j];
				}
				else
				{
					sag3 = sag3 * m1.AP[i + j][j];
				}
			}
		sag_determinant = sag1 + sag2 + sag3;

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < line; j++) {
				int a = line - j - 1;
				if (i == 0)
				{
					sol1 = sol1 * m1.AP[i + j][a];
				}
				else if (i == 1)
				{
					sol2 = sol2 * m1.AP[i + j][a];
				}
				else
				{
					sol3 = sol3 * m1.AP[i + j][a];
				}

			}
		sol_determinant = sol1 + sol2 + sol3;
		toplam_determinant = (sag_determinant - sol_determinant);

		cout << "Matrisin Determinanti =" << toplam_determinant;
		return toplam_determinant;

	}
	else
	{
		cout << "Matrisin boyutlari determinant icin uygun degil.Kare matris olmali..";
		exit(0);
	}
}



 //Matris yazdırma fonksiyonu.


template <typename T>
void Matrix<T>::print() {

	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < column; j++) {

			cout <<AP[i][j]<<" ";
		}
		cout << endl;
	}
}
template <typename T>
Matrix<T>::Matrix(int l, int c, int val) {
	this->column = c; // Matris sütun değeri atandı.
	this->line = l; // Matris satır değeri atandı.
	AP = new T*[c];
	for (int i = 0; i < l; i++)
	{
		AP[i] = new T[c];
	}

	for (int i = 0; i < line; i++)
		for (int j = 0; j < column; j++)
			AP[i][j] = val;


}
template <typename T>
Matrix<T>::Matrix()
{
	this->column = 10; // Matris sütun değeri atandı.
	this->line = 10; // Matris satır değeri atandı.
	AP = new T*[column];
	for (int i = 0; i < line; i++)
	{
		AP[i] = new T[column];
	}
	for (int i = 0; i < column; i++)
		for (int j = 0; j < line; j++)
			AP[i][j] = 0;
}




template <class U>
Matrix<U> Matrix<U>::operator+(const Matrix& other)
{

	Matrix m1(this->line, this->column,0);
	if (this->line == other.line && this->column == other.column)
	{
		for (int i = 0; i < line; i++) {
			for (int j = 0; j < column; j++) {
				m1.AP[i][j] = AP[i][j] + other.AP[i][j];
			}
		}
		return m1;
	}
	else
	{
		cout << "Toplama islemi icin satir ve sutun boyutlari her iki matris icinde esit olmak zorundadir..." << endl;
		exit(1);
	}

}


template <class U>
Matrix<U> Matrix<U>::operator-(const Matrix& other)
{

	Matrix m1(this->line, this->column);
	if (this->line == other.line && this->column == other.column)
	{
		for (int i = 0; i < line; i++) {
			for (int j = 0; j < column; j++) {
				m1.AP[i][j] = AP[i][j] - other.AP[i][j];
			}
		}
		return m1;
	}
	else
	{
		cout << "Cikarma islemi icin satir ve sutun boyutlari her iki matris icinde esit olmak zorundadir..." << endl;
		exit(1);
	}

}








template <class U>
Matrix<U> Matrix<U>::operator*(const Matrix& other)
{

	Matrix m1(this->line, other.column, 0);
	if ( this->column == other.line)
	{
		for (int i = 0; i < line; i++) {
			for (int j = 0; j < other.column; j++) {
				for (int k = 0; k < column; k++)
				m1.AP[i][j] += AP[i][k] * other.AP[k][j];
			}
		}
		return m1;
	}
	else
	{
		cout << "Carpma islemi icin hedef matrisin sutun boyutlariyla kendi matrisin satir boyutu esit olmak zorundadir..." << endl;
		exit(1);
	}

}




template <class U>
Matrix<U> Matrix<U>::operator-(double x)
{
	Matrix m1(this->line, this->column);
	for (int i = 0; i < line; i++) {
		for (int j = 0; j < column; j++) {
			m1.AP[i][j] = AP[i][j] - x;
		}
	}

	return m1;
}


template <class U>
Matrix<U> Matrix<U>::operator+(double x)
{
	Matrix m1(this->line, this->column);
	for (int i = 0; i < line; i++) {
		for (int j = 0; j < column; j++) {
			m1.AP[i][j] = AP[i][j] + x;
		}
	}

	return m1;
}




template <class U>
Matrix<U> Matrix<U>::operator*(double x)
{
	Matrix m1(this->line, this->column);
	for (int i = 0; i < line; i++) {
		for (int j = 0; j < column; j++) {
			m1.AP[i][j] = AP[i][j] * x;
		}
	}

	return m1;
}


 template <class U>
 void Matrix<U>::emul(const Matrix<U> &other)
{
	Matrix m1(this->line, this->column);
	for (int i = 0; i < line; i++) {
		for (int j = 0; j < column; j++) {
			m1.AP[i][j] = AP[i][j] * other.AP[i][j];
		}
	}
	for (int i = 0; i < line; i++)
		for (int j = 0; j < column; j++)
			this->AP[i][j] = m1.AP[i][j];

}
 template <class T>
 void Matrix<T>::resize(int a, int b)
 {
	 Matrix <int> m1(a, b);
	 if (a > this->line && b > this->column)
	 {
		 for (int i = 0; i < this->line; i++)
			 for (int j = 0; j < this->column; j++)
				 m1.AP[i][j] = AP[i][j];

		 for (int i = this->line; i < a; i++)
			 for (int j = this->column; j < b; j++)
				 m1.AP[i][j] = 0;
	 }
	 else if (a < this->line && b < this->column)
	 {
		 for (int i = 0; i < a; i++)
			 for (int j = 0; j < b; j++)
				 m1.AP[i][j] = this->AP[i][j];
	 }
	 else if (a > this->line && b < this->column)
	 {
		 for (int i = 0; i < this->column; i++)
			 for (int j = 0; j < b; j++)
				 m1.AP[i][j] = this->AP[i][j];
		 for (int i = this->line; i < a; i++)
			 for (int j = 0; j < b; j++)
				 m1.AP[i][j] = 0;
	 }
	 else if (a < this->line && b > this->column)
	 {
		 for (int i = 0; i < a; i++)
			 for (int j = 0; j < this->column; j++)
				 m1.AP[i][j] = AP[i][j];
		 for (int i = 0; i < a; i++)
			 for (int j = this->column; j < b; j++)
				 m1.AP[i][j] = 0;
	 }
	 else if (a > this->line && b == this->column)
	 {
		 for (int i = 0; i < this->line; i++)
			 for (int j = 0; j < this->column; j++)
				 m1.AP[i][j] = AP[i][j];
		 for (int i = this->line; i < a; i++)
			 for (int j = 0; j < this->column; j++)
				 m1.AP[i][j] = 0;
	 }
	 else if (a == this->line && b < this->column)
	 {
		 for (int i = 0; i < this->line; i++)
			 for (int j = 0; j < b; j++)
				 m1.AP[i][j] = AP[i][j];
	 }
	 else if (a < this->line && b == this->column)
	 {
		 for (int i = 0; i < a; i++)
			 for (int j = 0; j < this->column; j++)
				 m1.AP[i][j] = AP[i][j];
	 }
	 else if (a == this->line && b > this->column)
	 {
		 for (int i = 0; i < this->line; i++)
			 for (int j = 0; j < this->column; j++)
				 m1.AP[i][j] = AP[i][j];
		 for (int i = 0; i < this->line; i++)
			 for (int j = this->column; j < b; j++)
				 m1.AP[i][j] = 0;
	 }

	 this->line = a;
	 this->column = b;
	 AP = new T*[b];
	 for (int i = 0; i < a; ++i)
		 AP[i] = new T[b];

	 for (int i = 0; i < a; i++) {
		 for (int j = 0; j < b; j++) {
			 AP[i][j] = m1.AP[i][j];
			 //cout << setw(4) << m1.matrix[i][j];
		 }
		 cout << endl;
	 }
 }




template <class U>
Matrix<U> Matrix<U>::operator/(double x)
{
	Matrix m1(this->line, this->column);
	for (int i = 0; i < line; i++) {
		for (int j = 0; j < column; j++) {
			m1.AP[i][j] = AP[i][j] / x;
		}
	}

	return m1;
}

template <class U>
Matrix<U> Matrix<U>::operator%(int x)
{
	Matrix m1(this->line, this->column);
	for (int i = 0; i < line; i++) {
		for (int j = 0; j < column; j++) {
			m1.AP[i][j] = AP[i][j] % x;
		}
	}

	return m1;
}

template <class U>
Matrix<U> Matrix<U>::operator ^(int x)
{
	Matrix m1(this->line, this->column);
	for (int i = 0; i < line; i++) {
		for (int j = 0; j < column; j++) {
			m1.AP[i][j] = pow(AP[i][j],x);
		}
	}

	return m1;
}


template <class U>
class Table :public Matrix<U>
{
	int  *rowNames;
	string *columnNames;
public:
	Table<U>();
	Table<U>(int, int, int);
	Table<U>(int, int, char);
	void setColNames(string s[], int n);
	int itemAt(int r, int c);
	int itemAt(string s);
	int itemAt(string rs, string cs);
	void print();


};

template <typename type>
void Table<type>::setColNames(string s[], int n)
{
	for (int i = 0; i < n; i++)
	{
		for(int j=0;j<s->length();j++)
		columnNames[j] = s[i][j];
	}
}

template <class type>
void Table<type>::print()
{
	for (int i = 0; i < this->line; i++) {
		for (int j = 0; j < this->column; j++)
		{
			cout << rowNames[i];
			cout << columnNames[j];
			cout << "->  ";
			cout << this->AP[i][j];
			cout << " ";
		}
		cout << endl;
	}
}


template <class type>
int Table<type>::itemAt(string rs, string cs)
{
	int a = (char)cs[0];
	int b = rs[0] % 48;
	int index;

	for (int i = 0; i < this->line; i++)
	{
		if (b == rowNames[i])
		{
			index = i;
		}
	}

	return this->AP[a % 65][index];

}

template <class type>
int Table<type>::itemAt(string s)
{

	int a = (int)s[0];
	int b = s[1];




	return this->AP[b % 48][a % 65];
}
template <typename U>
int Table<U>::itemAt(int r, int c)
{
	return this->AP[r][c];
}
template <typename U>
Table<U>::Table():Matrix<U>()
{
	int a = 65;
	int b = 0;

	rowNames = new int[this->line];
	columnNames = new string[this->column];

	for (int i = 0; i < this->column; i++)
	{
		columnNames[i] = char(a);
		a++;
	}
	for (int j = 0; j < this->line; j++)
	{
		rowNames[j] = b;
		b++;
	}
}
template <typename U>
Table<U>::Table(int x, int y, char c) :Matrix<U>(x, y, c)
{
	int a = 60;
	int b = 0;

	rowNames = new int[x];
	columnNames = new string[y];

	for (int i = 0; i < y; i++)
	{
		columnNames[i] = char(a);
		a++;
	}
	for (int j = 0; j < x; j++)
	{
		rowNames[j] = b;
		b++;
	}
}
template <typename U>
Table<U>::Table(int x, int y, int c) :Matrix<U>(x, y, c)
{
	int a = 65;
	int b = 0;

	rowNames = new int[x];
	columnNames = new string[y];

	for (int i = 0; i < y; i++)
	{
		columnNames[i] = char(a);
		a++;
	}
	for (int j = 0; j < x; j++)
	{
		rowNames[j] = b;
		b++;
	}
}




int main()
{

     /* Matrix<int> m3(5,4,1);
      m3.print();
      // aşağıdaki durumları ayrı ayrı dene
      //m3.resize(2,6);
      //m3.resize(10,6);
      //m3.resize(10,3);
      m3.print();*/

     Matrix<double> a(2,3,1);
      a.print();
      /*
      Matrix<double> b(2,3,9);
      b.print();
      a = b + a*1;
      a.print("file.txt");*/

      /*Matrix<int> m3(5,4,1);
      m3.print();
      // aşağıdaki durumları ayrı ayrı dene
      //m3.resize(2,6);
      m3.resize(10,6);
     // m3.resize(10,3);

      m3.print();*/

     // Matrix<float> m6(3,3,'e');
     // cout<<m6.det(); // sonuç 0 olmalı


     /* Matrix<int> *m3 = new Matrix<int>(5,4,1);
      m3->print();
      // aşağıdaki durumları ayrı ayrı dene
      m3->resize(2,6);
      //m3.resize10,6);
     // m3->resize(10,3);

      m3->print();*/



  /*  Matrix<int> *m2 = new Matrix<int>(5,4,1);
	m2->resize(10, 3);
	m2->print();*/

	return 0;
}


