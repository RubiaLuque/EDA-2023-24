// Nombre del alumno Muxu Rubia Luque
// Usuario del Juez VJ53


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema
bool resolver(vector<int>& v, int dato, int ini, int fin) {
    if (ini == fin - 1) {
        if (v[ini] == dato) return true;
        else return false;
    }
    else if (v.empty()) return false;
    else {
        int med = (ini + fin) / 2;
        if (dato == v[med]) return true;
        else if (dato == v[ini]) return true;
        else if (dato == v[fin - 1]) return true;

        if (dato > v[med] && dato < v[fin - 1]) {
            return resolver(v, dato, med, fin);
        }
        else if (dato > v[med] && dato > v[fin - 1] && v[med] < v[fin-1]) {
            return resolver(v, dato, ini, med);
        }
        else if (dato > v[med] && dato > v[fin - 1] && v[med] > v[fin-1]) {
            return resolver(v, dato, med, fin);
        }
        else if (dato < v[med] && dato > v[ini]) {
            return resolver(v, dato, ini, med);
        }
        else if (dato < v[med] && dato < v[ini] && v[med] < v[fin-1]) {
            return resolver(v, dato, ini, med);
        }
        else if (dato < v[med] && dato < v[ini] && v[med] > v[fin-1]) {
            return resolver(v, dato, med, fin);
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // Lectura de los datos
    int N, dato;
    std::cin >> N;
    if (N == -1) return false;
    std::cin >> dato;
    std::vector<int> v(N);
    for (int& i : v) std::cin >> i;

    
    bool sol = resolver(v, dato, 0, N);
    

    // Escribir los resultados
    if (sol) std::cout << "SI\n";
    else std::cout << "NO\n";
    return true;
}

//#define DOMJUDGE

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
