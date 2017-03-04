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

	//creating a three-dimensional array, pM[0] - A matrix, pM[1] - D matrix,
	double ***pM = new double**[4]; // pM[2] - S matrix, pM[3] - transposed S.
	for (int q = 0; q < 4; q++) {
		pM[q] = new double*[n];
		for (int k = 0; k < n; k++) {
			pM[q][k] = new double[n];
		}
	}

	cout << "\nEnter the elements of symmetric matrix A:\n";

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			cout << "A[" << i << ";" << j << "] = ";
			getnum(pM[0][i][j]); //pA[i][j] = getnum();
		}

	cout << "\n\n The original matrix A:\n\n";
	matrixoutput(pM[0], n);
	

	for (int d1 = 0; d1 < 4; d1++) {
		for (int d2 = 0; d2 < n; d2++)
			delete[] pM[d1][d2];
		delete[] pM[d1];
	}
	delete[]pM;

	cout << endl;
	system("pause");
	return 0;
}