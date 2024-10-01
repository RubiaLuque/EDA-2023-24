// puesto_eda.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
using namespace std;

int main()
{
	int N = 53;
	float lab = ((N - 1) / 20) + 8;
	float puesto = ((N - 1) % 20) + 1;

	cout << "Lab: " << lab << endl;
	cout << "Puesto: " << puesto << endl;
}
