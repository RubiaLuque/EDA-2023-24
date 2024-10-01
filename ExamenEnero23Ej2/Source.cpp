// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
#include <climits>

using namespace std;

// función que resuelve el problema
void resolver(bintree<int> const& tree, int numDrag, int& root, int& minDrag) {
    if (tree.empty()) return;
    //Se les dan valores a los parametros de la funcion si nos encontramos en un caso base
    else if (tree.right().empty() && tree.left().empty()) {
        if (numDrag < minDrag) {
            minDrag = numDrag;
            root = tree.root();
        }
    }
    else {

        if (tree.root() == 1)
            numDrag++;

        resolver(tree.left(), numDrag, root, minDrag);
        resolver(tree.right(), numDrag, root, minDrag);
    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada

    bintree<int> tree = leerArbol(-1);
    int root;
    int minDrag = INT_MAX;
    resolver(tree, 0, root, minDrag);

    // escribir sol
    cout << root << "\n";

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