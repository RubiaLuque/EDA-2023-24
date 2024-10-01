
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;



// función que resuelve el problema
void resolver(vector<int>& soluc, int k, int n, int m, int gasto, int& mejorGasto, const vector<vector<int>>& precios) {

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, m, mejorGasto;
    cin >> m >> n; //m: num supermercados; n: num productos
    vector<vector<int>> precios(m, vector<int>(n));
    // Lectura de datos
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> precios[i][j];
        }
    }

    int gasto = 0;
    mejorGasto = -1;
    vector<int> soluc(n); //Precios de los productos
    vector<int> precioElegido(n);
    resolver(soluc, 0, n, m, gasto, mejorGasto, precios);

    (mejorGasto > -1) ? cout << mejorGasto : cout << "Sin solucion factible";
    cout << endl;
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
    //system("PAUSE");
#endif

    return 0;
}
