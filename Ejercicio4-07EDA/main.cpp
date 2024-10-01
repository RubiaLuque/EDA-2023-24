//Muxu Rubia Luque
//VJ53

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Set.h"
#include <vector>
using namespace std;

Set<int> resolver(int k) {
    Set<int> aux = Set<int>();
    //añadir a aux los k menores elementos de un set dado
    int e;
    cin >> e;
    //En su conjunto, el bucle y su interior, tienen un coste en caso peor de O(n*(k+log k))
    //donde k es el numero de elementos menores de un numero n dado de elementos
    //Es asi porque para cada n, se realizan operaciones que recorren el set con k elementos con coste
    // lineal
    
    while (e != -1) { //unicamente el bucle, que recorre todos los elementos dados inicialmente 
        //tiene coste lineal con respecto a dicho numero de elementos, sea n. 
        if (aux.size() < k) {
            aux.add(e);
        }
        else {
            if (e < aux.getMax() && !aux.contains(e)) { //contains tiene complejidad log k
                aux.removeMax();
                aux.add(e); //Complejidad lineal con respecto a k
            }
        }
        
        
        cin >> e;
    }

    return aux;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int k;

    cin >> k;
    if (k == 0) return false;

    auto aux = resolver(k);

    for (int i = 0; i < k; ++i) {
        cout << aux.getArray(i) << ' ';
    }
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
#endif

    return 0;
}