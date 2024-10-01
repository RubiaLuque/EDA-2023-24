// Nombre del alumno Muxu Rubia Luque
// Usuario del Juez VJ53


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include "bintree_eda.h"
using namespace std;

template <typename T>
T resolver(bintree<T>const& tree) {
    if (tree.right().empty() && tree.left().empty()) {
        return tree.root();
    }
    else if (tree.left().empty()) {
        return min(resolver(tree.right()), tree.root());
    }
    else if (tree.right().empty()) {
        return min(resolver(tree.left()), tree.root());
    }
    else {
        T minL = resolver(tree.left());
        T minR = resolver(tree.right());
        T root = tree.root();
        
        T aux = min(minL, minR);
        T minim = min(aux, root);
        return minim;
    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    char op;
    cin >> op;
    if (!std::cin)
        return false;
    bintree<int> treeN;
    bintree<string> treeP;
    if (op == 'N') {
        treeN = leerArbol(-1);
        if (!treeN.empty()) {
        int sol = resolver(treeN);
        cout << sol << '\n';
        }
        else {
            cout << -1 << "\n";
        }
    }
    else {
        treeP = leerArbol(std::string("#"));
        if (!treeP.empty()) {
            string sol = resolver(treeP);
            cout << sol << '\n';
        }
        else {
            cout << "#" << "\n";
        }
    }


    return true;

}

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