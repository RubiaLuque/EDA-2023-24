// Nombre del alumno: Muxu Rubia Luque
// Usuario del Juez: VJ53


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema
bool resolver(const vector<int> & v, int ini, int fin, int k) {
    int n = fin - ini;
    if (n == 1) { //Un solo elemento es disperso por definicion
        return true;
    }
    else if (n == 2) { //Dos elementos
        bool b; 
        (abs(v[ini] - v[fin - 1]) >= k) ? b = true: b = false;
        return b;
    }
    else {
        bool iz, dr, tIz, tDr; //tIz = this izquierda, tDr = this Derecha
        int mid = (ini + fin) / 2;
        //Se comprueba para los fragmentos actuales
        tIz = (abs(v[ini] - v[mid - 1]) >= k);
        tDr = (abs(v[mid] - v[fin - 1]) >= k);

        iz = resolver(v, ini, mid, k);
        dr = resolver(v, mid, fin, k);

        return iz && dr && tIz && tDr;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, k;
    cin >> n >> k;

    if (!std::cin)
        return false;

    vector<int> v(n);
    for (int& e : v) cin >> e;
    

    // escribir sol
    cout << (resolver(v, 0, n, k) ? "SI" : "NO") << endl;

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