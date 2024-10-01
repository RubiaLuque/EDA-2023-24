﻿// Muxu Rubia Luque
// VJ53


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// función que resuelve el problema
void resolver(vector<long long int> &datos) {
    for (int i = 0; i < datos.size(); i++) {
        //if (datos[i] % 2 != 0) datos.erase(datos.begin()+i);

    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    
    int n;
    cin >> n;
    vector<long long int>datos(n);

    for (int i = 0; i < n; ++i)
        cin >> datos[i];

    resolver(datos);
    // escribir sol
    n = datos.size();
    for (int i = 0; i < n; ++i)
        cout << datos[i] << " ";

    cout << endl;

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