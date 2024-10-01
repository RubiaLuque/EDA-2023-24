// Muxu Rubia Luque
// VJ53

//Tiene una complejidad lineal, es decir, O(n)

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema
bool resolver(vector<int> datos, int n) {
    if (n == 1) return false;

    bool aux = true;
    int i = 0;
    while (aux && i<n-1) {
        if (datos[i] >= datos[i + 1]) aux = false;
        i++;
    }

    bool aux1 = true;
    int j = 0;
    while (aux1 && j < n-1) {
        if (datos[j] <= datos[j + 1]) aux1 = false;
        j++;
    }

    return aux || aux1;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    if (n == 0)
        return false;

    //se crea un vector y se rellena con los datos pertinentes
    vector<int> datos;
    int dato;
    for (int i = 0; i < n; i++) {
        cin >> dato;
        datos.push_back(dato);
    }

    bool sol = resolver(datos, n);

    // escribir sol
    if (sol) cout << "DALTON" <<endl;
    else cout << "DESCONOCIDOS" << endl;


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


    while (resuelveCaso());


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
