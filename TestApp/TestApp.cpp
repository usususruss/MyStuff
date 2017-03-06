#include "stdafx.h"
#include <iostream>
#include <clocale>
#include "math.h"
#include <cstdlib> // for working srand()
#include <ctime>
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

void vectoutput(double *&b, int n) {
	for (int i = 0; i < n; i++)
		cout << b[i] << endl;
	return;
}

void zeroInit(double **&pTemp, int n) { //output matrix
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) pTemp[i][j] = 0;
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
	else 
		if (ans == 2) {
			for (int i = 0; i < n; i++)
				for (int j = 1; j + i < n; j++) { pA[i][j + i] = pA[j + i][i] = rand() % 5 + 1; }
			for (int i = 0; i < n; i++)
				pA[i][i] = rand() % 5 + 1;
		}
		else {
			double pAcopy[4][4] = {
						{ 6, -5, -1, -8 },
						{ -5, 7, -5, 5 },
						{ -1, -5, 9, -1 },
						{ -8, 5, -1, 7 } };
			for (int p = 0; p < n; p++)
				for (int l = 0; l < n; l++) pA[p][l] = pAcopy[p][l];
		}

	return;
}

void setb(double *&b, int n, int &ans) {
	if (ans == 1) {
		cout << "\nEnter the elements of vector b:\n";
		for (int i = 0; i < n; i++) {
			cout << "b[" << i << "] = ";
			getnum(b[i]);
		}
	}
	else 
		if (ans == 2) {
			for (int i = 0; i < n; i++) {
				b[i] = rand() % 10 + 1;
			}
		}
		else {
			double bcopy[4] = { 158, -100, -20, -146 };
			for (int l = 0; l < n; l++) b[l] = bcopy[l];
		}
	return;
}

bool check(double **&pA, int n) {
	bool b = true;
	for (int i = 0; i < n; i++)
		for (int j = 1; j + i < n; j++)
			if (pA[i][j+i] != pA[j+i][i]) b = false;
	if (b == false) cout << "\n\n!!Matrix is NOT symmetric!!\n\n";
	return b;
}

double sign(double d) {
	if (d < 0) d = -1;
	else 
		if (d > 0) d = 1;
		else d = 0;
	return d;
}

double sum1(double ***&pM, int i) {
	double s = 0;
	for (int k = 0; k <= (i - 1); k++) {
		s = s + pM[2][k][i] * pM[2][k][i] * pM[1][k][k];
	}
	return s;
}

double sum2(double ***&pM, int i, int j) {
	double s = 0;
	for (int k = 0; k <= (i - 1); k++) {
		s = s + pM[2][k][i] * pM[1][k][k] * pM[2][k][j];
	}
	return s;
}

double sum3(double **&St, double *y, int i) {
	double s = 0;
	for (int k = 0; k <= (i - 1); k++)
		s = s + y[k] * (St[i][k] / St[i][i]);
	return s;
}

double sum4(double **&S, double *x, int i, int n) {
	double s = 0;
	for (int k = (n - 1); k >= (i + 1); k--)
		s = s + x[k] * S[i][k] / S[i][i];
	return s;
}

void transp(double **&pRes, double **&pInit, int n) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) pRes[i][j] = pInit[j][i];
	return;
}

int main() {

	setlocale(LC_CTYPE, "rus");
	cout << "\t\t\tSquare root method\n\n";
	cout.precision(3); // setting the number of decimal places
	int n, ans; // n -matrix dimention

	do {
		cout << "Enter the size of the symmetric matrix n = ";
		getnum(n);
	} while (n <= 0 || n >= 500);

	//creating a three-dimensional array. 
	double ***pM = new double**[4]; // pM[0] - A matrix, pM[1] - D matrix,pM[2] - S matrix, pM[3] - transposed S.
	for (int q = 0; q < 4; q++) {
		pM[q] = new double*[n];
		for (int k = 0; k < n; k++) {
			pM[q][k] = new double[n];
		}
	}

	double *b = new double[n]; // allocate memory for the array of responses, vector b

	for (int z = 0; z < 4; z++) zeroInit(pM[z],n);

	srand(time(0)); // random values each time
	do {
		if (n == 4) {
			do {
				cout << "\nSelect an action:\n\t1 - Enter the matrix A from the keyboard\n";
				cout << "\t2 - Filling the pseudo-random numbers\n\t3 - Prepared sample of matrix A\n  Answer: ";
				getnum(ans);
			} while (!(ans == 1 || ans == 2 || ans == 3));
		}
		else {
			do {
				cout << "\nSelect an action:\n\t1 - Enter the matrix A from the keyboard\n";
				cout << "\t2 - Filling the pseudo-random numbers\n  Answer: ";
				getnum(ans);
			} while (!(ans == 1 || ans == 2));
			}
		setA(pM[0], n, ans);
		setb(b, n, ans);
	} while (!(check(pM[0],n)));

	cout << "\n\n The original matrix A:\n\n";
	matrixoutput(pM[0], n);
	cout << "\n\n The original vector b:\n\n";
	vectoutput(b, n);
	
	//calculation of matrices D and S
	for (int i = 0; i < n; i++) {
		pM[1][i][i] = sign(pM[0][i][i] - sum1(pM,i)); // countig D[i;i]
		pM[2][i][i] = sqrt(fabs(pM[0][i][i] - sum1(pM, i))); // counting S[i;i]
		for (int j = i + 1; j < n; j++) {
			pM[2][i][j] = (pM[0][i][j] - sum2(pM, i, j)) / (pM[1][i][i] * pM[2][i][i]);
		}
	}

	transp(pM[3],pM[2],n); // filling the transposed matrix S

	cout << "\n\n The original matrix D:\n\n";
	matrixoutput(pM[1], n);
	cout << "\n\n The original matrix S:\n\n";
	matrixoutput(pM[2], n);
	cout << "\n\n The original matrix ST:\n\n";
	matrixoutput(pM[3], n);

	double *y = new double[n];
	double *x = new double[n];

	for (int l = 0; l < n; l++) {
		y[l] = b[l] / pM[3][l][l] - sum3(pM[3], y, l);
	}

	cout << "\n\nVector y:\n\n";
	vectoutput(y, n);

	for (int h = (n - 1); h >= 0; h--) {
		x[h] = pM[1][h][h] * y[h] / pM[2][h][h] - sum4(pM[2], x, h, n);
	}

	cout << "\n\nSolution is ready! Vector x:\n\n";
	vectoutput(x, n);

	//erasing all dynamyc memory
	for (int d1 = 0; d1 < 4; d1++) {
		for (int d2 = 0; d2 < n; d2++)
			delete[] pM[d1][d2];
		delete[] pM[d1];
	}
	delete[]pM;
	delete[]y;
	delete[]x;
	delete[]b;

	cout << endl;
	system("pause");
	return 0;
}