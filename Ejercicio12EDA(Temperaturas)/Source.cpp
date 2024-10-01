// Muxu Rubia Luque
// VJ53


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

struct temp {
    int pico, valle;
};

// función que resuelve el problema
temp resolver(vector<int> datos, int n) {
    //pico: anterior y posterior valores menores que él
    //valle: anterior y posterior valores mayores que él
    temp temps = { 0,0 };

    for (int i = 1; i < n-1; ++i) {
        //picos
        if (datos[i - 1] < datos[i] && datos[i]> datos[i + 1]) temps.pico++;
        //valle
        else if (datos[i - 1] > datos[i] && datos[i] < datos[i + 1]) temps.valle++;
    }

    return temps;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n; 
    cin >> n;

    vector<int> datos;

    int dato;
    for (int i = 0; i < n; ++i)
    {
        cin >> dato;
        datos.push_back(dato);
    }

    temp sol = resolver(datos, n);
    // escribir sol
    cout << sol.pico << " " << sol.valle << endl;

}

//#define DOMJUDGE

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