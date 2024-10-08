﻿#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema
int resolver(const vector<int>& v, int ini, int fin) {
    int n = fin - ini;
    if (n == 1) { //Solo queda un elemento --> ini = fin - 1
        return v[ini];
    }
    else {
        int mid = (ini + fin) / 2;
        if (v[mid] - v[ini] == mid - ini) { //Se busca por la derecha, porque los actuales son consecutivos
            return resolver(v, mid, fin);
        }
        else { //Se busca por la izquierda, porque los actuales no son consecutivos
            return resolver(v, ini, mid);
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    vector<int> sec(n);
    for (int& e : sec) cin >> e;
    cout << resolver(sec, 0, n) << endl;
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}