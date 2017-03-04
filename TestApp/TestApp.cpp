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

void matrixoutput(double **&pTemp, int n) { //output matrix
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) cout << pTemp[i][j] << "\t";
		cout << endl;
	}
	return;
}

void setA(double **&pA, int n, int &ans) { //the procedure of filling the matrix A
	if (ans == 1) {
		cout << "\nEnter the elements of symmetric matrix A:\n";
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				cout << "A[" << i << ";" << j << "] = ";
				getnum(pA[i][j]);
			}
	}
	else {
		double pAcopy[4][4] = {
			{ 4, -8, -6, 7},
			{ -8, 4, -2, 9 },
			{ -6, -2, -7, -10 },
			{ 7, 9, -10, -7 } };
		for (int p = 0; p < n; p++)
			for (int l = 0; l < n; l++) pA[p][l] = pAcopy[p][l];
	}

	return;
}

bool check(double **&pA, int n) {
	bool b = true;
	for (int i = 0; i < n; i++)
		for (int j = 1; j+i < n; j++) //(int j = 1; j + i < n; j++)
			if (pA[i][j+i] != pA[j+i][i]) b = false;
	if (b == false) cout << "\n\n!!Matrix is NOT symmetric!!\n\n";
	return b;
}

int main() {

	setlocale(LC_CTYPE, "rus");
	cout << "\t\t\tSquare root method\n\n";
	int n, ans; //matrix dimention

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


	do {
		if (n == 4) {
			do {
				cout << "\nSelect an action:\n\t1 - Enter the matrix A from the keyboard\n";
				cout << "\t2 - Prepared sample of matrix A\n   Answer: ";
				getnum(ans);
			} while (!(ans == 1 || ans == 2));
			setA(pM[0], n, ans);
		}
		else { ans = 1; setA(pM[0], n, ans); }
	} while (!(check(pM[0],n)));


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