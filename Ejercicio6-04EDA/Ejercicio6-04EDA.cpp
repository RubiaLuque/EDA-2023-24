// Nombre del alumno Muxu Rubia Luque
// Usuario del Juez VJ53


#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <climits>
#include "bintree_eda.h"
using namespace std;

// función que resuelve el problema
bool resolver(bintree<int> const& tree, int& maxTree, int& minTree) {
    //minDer y maxIz deberian ser el maximo y el minimo absolutos en un ABB
    if (tree.empty()) {
        return true;
    }
    else if (tree.right().empty() && tree.left().empty()) {
        minTree = maxTree = tree.root();
        return true;
    }
    else {
        int maxLeft, minRight, minLeft, maxRight;

        //Se devuelven los maximos y minimos de la derecha y de la izquierda, ademas de si son o no ABB
        bool iz = resolver(tree.left(), maxLeft, minLeft);
        bool dcha = resolver(tree.right(), maxRight, minRight);

        //Si el arbol no tiene rama izquierda, tanto el maximo como el minimo se toman del hijo derecho
        if (tree.left().empty()) {
            minTree = std::min(minRight, tree.root());
            maxTree = std::max(maxRight, tree.root());
        }
        //Si no tiene rama derecha, se hace lo mismo pero con el hijo izquierdo
        else if (tree.right().empty()) {
            minTree = std::min(minLeft, tree.root());
            maxTree = std::max(maxLeft, tree.root());
        }
        //Si tiene ambos hijos, se usan ambas ramas
        else {
            minTree = std::min({ minLeft, minRight, tree.root() });
            maxTree = std::max({ maxLeft, maxRight, tree.root() });
        }

        bool raiz;

        //Si no tiene hijo izquierdo, se comprueba solo con el maximo del hijo derecho
        if (tree.left().empty()) {
            raiz = tree.root() < minRight;
        }
        //Idem si tiene el hijo derecho vacio
        else if (tree.right().empty()) {
            raiz = tree.root() > maxLeft;
        }
        //Tiene que ocurrir que la raiz sea menor que el mayor de su hijo izquierdo y menor que el minimo del derecho
        else {
            raiz = (tree.root() > maxLeft) && (tree.root() < minRight);

        }

        return iz && dcha && raiz;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada

    bintree<int> tree;
    tree = leerArbol(-1);
    int maxIz = INT_MIN, minDr = INT_MAX;
    bool sol;

    sol = resolver(tree, maxIz, minDr);
    // escribir sol
    sol ? cout << "SI\n" : cout << "NO\n";

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