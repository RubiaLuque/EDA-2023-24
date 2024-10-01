// Nombre del alumno: Muxu Rubia Luque
// Usuario del Juez: VJ53


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
#include <algorithm>
using namespace std;

bool esPrimo(int n) {
    if (n % 2 == 0) return false;

    for (int i = 3; i < n; ++i) {
        if (n % i == 0) return false;
    }

    return true;
}

struct Datos {
    int num;
    int altura;
};

// función que resuelve el problema
Datos resolver(const bintree<int>& tree) {
    if (tree.empty()) return { 1, -1 };
    else if (tree.right().empty() && tree.left().empty()) {
        if (!esPrimo(tree.root()) && tree.root() % 7 == 0) {
            return { tree.root(), 1 };
        }
        else return { 1, 0 };
    }
    else {
        //Si el nodo en el que nos encontramos es primo, no seguimos bajando
        if (esPrimo(tree.root())) return { 1, 0 };

        Datos iz, dr;

        iz = resolver(tree.left());
        dr = resolver(tree.right());

        Datos resultado;

        //Si este nodo es ya de por si un nodo que cumple los requisitos, lo devolvemos
        if (tree.root() % 7 == 0) return { tree.root(), max(iz.altura, dr.altura)+1 };

        //En otro caso, seguimos mirando
        
        //Se calcula la altura
        if (iz.num != 1 && dr.num != 1) resultado.altura = min(iz.altura, dr.altura) +1;
        else if (iz.num == 1 && dr.num != 1) resultado.altura = dr.altura +1;
        else if (iz.num != 1 && dr.num == 1) resultado.altura = iz.altura +1;
        //else resultado.altura == -1;

        //Se calcula el numero
        if (iz.num != 1 && dr.num != 1) (iz.altura <= dr.altura) ? resultado.num = iz.num : resultado.num = dr.num;
        else if (iz.num == 1 && dr.num != 1) resultado.num = dr.num;
        else if (iz.num != 1 && dr.num == 1) resultado.num = iz.num;
        //else resultado.num == -1;

        return resultado;

    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada

    bintree<int> datos = leerArbol(-1);

    Datos sol = resolver(datos);
    // escribir sol
    (sol.num == 1) ? cout << "NO HAY\n" : cout << sol.num << " " << sol.altura << "\n";

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