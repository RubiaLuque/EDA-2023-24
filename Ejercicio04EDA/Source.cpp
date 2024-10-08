﻿// Muxu Rubia Luque
// VJ53


#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// función que resuelve el problema
int resolver(int datos) {

    return datos * 2;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int datos;
    cin >> datos;
    if (!std::cin)
        return false;

    int sol = resolver(datos);

    // escribir sol
    cout << sol << endl;

    return true;

}

//#define DOMJUDGE

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