// Muxu Rubia Luque
// VJ53


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// función que resuelve el problema
bool resolver(vector<int> datos, int n, int p) {
    int upper = datos[0], lower = datos[p+1];
    
    if (p == datos.size() - 1) return true;
    for (int i = 1; i < p + 1; ++i) {
        if (datos[i] > upper) upper = datos[i];
    }

    for (int j = p + 2; j < n; ++j) {
        if (datos[j] < lower) lower = datos[j];
    }
    
    return (upper < lower);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, p;
    cin >> n;
    cin >> p;
    vector<int> datos;

    int dato;
    for (int i = 0; i < n; i++) {
        cin >> dato;
        datos.push_back(dato);
    }

    bool sol = resolver(datos, n, p);

    // escribir sol
    if (sol) cout << "SI" << endl;
    else cout << "NO" << endl;

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