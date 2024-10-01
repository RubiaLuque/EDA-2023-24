#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema
int resolver(const vector<int>& sec, int ini, int fin) {
    if (ini == fin -1) {
        return sec[ini];
    }
    else {
        int med = (ini + fin) / 2;
        if (sec[med] % 2 != 0) return sec[med];
        else {
            if (sec[fin-1] - sec[med] == 2*(fin -1 - med)) { //Si se cumple que el lado dcho tiene su numero de componentes esperada
                //Se resuelve hacia la izquierda
                return resolver(sec, ini, med);
            }

            //Buscar a la izquierda
            else { //Si el lado dcho tiene mayor numero de componentes que las esperadas, se resuelve por la dcha.
                return resolver(sec, med, fin);
            }
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    if (n == 0) return false;
    vector<int> sec(n);
    for (int& e : sec) cin >> e;
    cout << resolver(sec, 0, n) << endl;
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
    //system("PAUSE");
#endif

    return 0;
}