// Nombre del alumno Muxu Rubia Luque
// Usuario del Juez VJ53


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "bintree_eda.h"
using namespace std;

// función que resuelve el problema
void resolver(vector<int>& frontera, const bintree<int>& tree) {
    if (tree.empty()) return;
    else if (tree.right().empty() && tree.left().empty()) {
        frontera.push_back(tree.root());
    }
    else {
        resolver(frontera, tree.left());
        resolver(frontera, tree.right());
    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<int> tree;
    tree = leerArbol(-1);

    vector<int> frontera;
    resolver(frontera, tree);
    // escribir sol
    for (auto elem : frontera) {
        cout << elem << " ";
    }
    cout << '\n';

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
    system("PAUSE");
#endif

    return 0;
}