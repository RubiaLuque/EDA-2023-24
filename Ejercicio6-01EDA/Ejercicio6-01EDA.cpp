
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "bintree_eda.h"
using namespace std;

struct datos {
    int nodos = 0;
    int altura = 0;
    int hojas = 0;
};

template<class T>
datos resolver(bintree<T> const& tree) {
    if (tree.empty()) return { 0,0,0 };
    else if (tree.right().empty() && tree.left().empty()) {
        return { 1,1,1 };
    }
    else {
        datos r1 = resolver(tree.left());
        datos r2 = resolver(tree.right());
        datos resultados;

        resultados.altura = max(r1.altura, r2.altura) +1;
        resultados.hojas = r1.hojas + r2.hojas;
        resultados.nodos = r1.nodos + r2.nodos +1;

        return resultados;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<char> tree;
    tree = leerArbol('.');
    datos resultados = resolver(tree);

    cout << resultados.nodos << " " << resultados.hojas << " " << resultados.altura << endl;
}


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
