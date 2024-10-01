// Nombre del alumno Muxu Rubia Luque
// Usuario del Juez VJ53


#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

#include "Set1.h"
using namespace std;

// función que resuelve el problema
void resolver(Set1<int>& s, int num) {
    bool aux = false;

    int sum = 0;
    int m = num / 1000;
    int c = (num % 1000) / 100;
    int d = (num % 100) / 10;
    int u = (num % 10);
    s.add(num);

    do {
        sum = pow(m, 2) + pow(c, 2) + pow(d, 2) + pow(u, 2);
        if (num == 1) {
            s.add(1);
            aux = true;
        }
        else if (sum == 1) {
            s.add(sum);
            s.add(1);
            aux = true;
        }
        else if (s.contains(sum)) {
            s.add(sum);
            s.add(0);
            aux = true;
        }
        s.add(sum);
        m = sum / 1000;
        c = (sum % 1000) / 100;
        d = (sum % 100) / 10;
        u = (sum % 10);

    }while (!aux);

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    int num;
    cin >> num;
    if (!std::cin)
        return false;

    Set1<int> s;
    resolver(s,num);
   
    // escribir s
    cout << s;

    cout << '\n';

    return true;

}

#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}