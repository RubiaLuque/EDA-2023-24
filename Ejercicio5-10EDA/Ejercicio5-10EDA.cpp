// Nombre del alumno Muxu Rubia Luque
// Usuario del Juez VJ53


#include <iostream>
#include <iomanip>
#include <fstream>
#include <list>
using namespace std;

// función que resuelve el problema
void resolver(list<int>& lista) {
    if (lista.size() == 1) return;

    auto itAux = lista.begin();
    for (auto it = lista.begin(); it != lista.end() && itAux != lista.end();) {
        if (it == lista.begin()) ++it;
        if (it!= lista.end() && *it < *itAux) {
            it = lista.erase(it);
        }
        else {
            if(it!= lista.end())
                ++it;
            if(itAux != lista.end())
                ++itAux;
        }
    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    list<int> l;
    int dato;
    cin >> dato;
    while (dato != -1) {
        l.push_back(dato);
        cin >> dato;
    }

     resolver(l);
    // escribir sol
     for (auto e : l) {
         cout << e << ' ';
     }
     cout << '\n';
}
#define DOMJUDGE
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