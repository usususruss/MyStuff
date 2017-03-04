#include "stdafx.h"
#include <iostream>
#include <clocale>
using namespace std;

int getnum() { // function which controls input data
	bool good = true;
	int a;
	do
	{
		//cout << " " << ch << "=";
		cin >> a;
		if (!(good = cin.good())) cout << ("  Retype please.\n");
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (!good);
	return a;
}


int main() {

	setlocale(LC_CTYPE, "rus");
	cout << "\t\t\tSquare root method\n\n";
	int n; //matrix dimention

	do {
		cout << "Enter the size of the symmetric matrix n = ";
		n = getnum();
	} while (n <= 0 || n >= 500);


	int **pA = new int*[n]; //allocation under n lines
	for (int k = 0; k < n; k++)
		pA[k] = new int[n];//and n rows


	cout << "\nEnter the elements of symmetric matrix A:\n";

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			cout << "A[" << i << ";" << j << "] = ";
			pA[i][j] = getnum();
		}

	cout << "\n\n The original matrix A:\n\n";

	for (int k = 0; k < n; k++) {
		for (int y = 0; y < n; y++) cout << pA[k][y] << "\t";
		cout << endl;
	}


	for (int m = 0; m < n; m++)
		delete[] pA[m];
	delete[] pA;

	system("pause");
	return 0;
}