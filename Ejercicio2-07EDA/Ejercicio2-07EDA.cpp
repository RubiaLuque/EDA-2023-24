// Nombre del alumno: Muxu Rubia Luque
// Usuario del Juez: VJ53


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;


// función que resuelve el problema
void resolver(const vector<int>& v, int ini, int fin, int& min) {
    int n = fin - ini;
    if (n == 1) {
        min = v[ini];
    }
    else if (n == 2) {
        if (v[ini] < v[fin - 1]) min = v[ini];
        else min = v[fin - 1];
    }
    else {
        int mid = (ini + fin) / 2;
        //Caso en el que no se ha rotado el vector -> por la derecha
        if (v[mid] < v[ini] && v[mid] > v[fin - 1]) resolver(v, mid, fin, min);
        //Caso en el que la mayoria del vector esta rotado -> por la izquierda
        else if (v[mid] > v[ini] && v[mid] > v[fin - 1]) resolver(v, ini, mid, min);
        //Caso en el que un solo elemento o muy pocos se han rotado, lo mas seguro es que mid sea el menor o este muy cerca
        else if (v[mid] < v[ini] && v[mid] < v[fin - 1]) resolver(v, mid, fin, min);
        //Caso en el que mid es mayor que ambos extremos -> por la derecha
        else if (v[mid] > v[ini] && v[mid] > v[fin - 1]) resolver(v, ini, mid, min);
    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n; cin >> n;
    if (!std::cin)
        return false;

    vector<int> v(n);
    for (int& e : v) cin >> e;
    int min;
    resolver(v, 0, n, min);

    // escribir sol
    cout << min << "\n";

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