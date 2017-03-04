#include "stdafx.h"
#include <iostream>
#include <clocale>
using namespace std;

template < typename T >
void getnum(T & a) { // function which controls input data
	bool good = true;
	do
	{	cin >> a;
		if (!(good = cin.good())) cout << ("  Retype please.\n");
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (!good);
	return;
}

void matrixoutput(double **&pTemp, int n) {
	for (int k = 0; k < n; k++) {
		for (int y = 0; y < n; y++) cout << pTemp[k][y] << "\t";
		cout << endl;
	}

	return;
}

int main() {

	setlocale(LC_CTYPE, "rus");
	cout << "\t\t\tSquare root method\n\n";
	int n; //matrix dimention

	do {
		cout << "Enter the size of the symmetric matrix n = ";
		getnum(n);
	} while (n <= 0 || n >= 500);


	double **pA = new double*[n]; //allocation under n lines
	for (int k = 0; k < n; k++)
		pA[k] = new double[n];//and n rows


	cout << "\nEnter the elements of symmetric matrix A:\n";

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			cout << "A[" << i << ";" << j << "] = ";
			getnum(pA[i][j]); //pA[i][j] = getnum();
		}

	cout << "\n\n The original matrix A:\n\n";
	matrixoutput(pA, n);
	


	for (int m = 0; m < n; m++)
		delete[] pA[m];
	delete[] pA;

	system("pause");
	return 0;
}