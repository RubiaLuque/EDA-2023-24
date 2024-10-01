// Nombre del alumno Muxu Rubia Luque
// Usuario del Juez VJ53


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

// función que resuelve el problema
std::pair<bool, int> resolver(bintree<int>const& tree) {
    if (tree.empty()) return { true, 0 };

    else if (tree.right().empty() && tree.left().empty()) {
        return { true, 1 };
    }

    else if(tree.left().empty()){
        return { false, -1 }; //-1 indica que no es un arbol genealogico valido
    }

    else if (tree.right().empty()) {
        std::pair<bool, int> r;
        if (tree.root() >= tree.left().root() + 18) {
            r.first = true;
            //r.second;
        }
        else {
            r.first = false;
            r.second = -1;
        }

    }

    else {
        std::pair<bool, int> iz = resolver(tree.left());
        std::pair<bool, int> dr = resolver(tree.right());

        std::pair<bool, int> total;
        total.first = iz.first && dr.first;
        total.second = std::max(iz.second, dr.second) + 1;

        return total;

    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada

    bintree<int> tree = leerArbol(-1);

    std::pair<bool, int> sol = resolver(tree);

    // escribir sol
    (sol.first) ? std::cout << "SI " << sol.second : std::cout << "NO";

    std::cout << "\n";

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