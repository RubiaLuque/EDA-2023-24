// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// 0 : azul
// 1 : rojo
// 2 : verde

bool esValida(const vector<int>& datos, int k, int n) {
    bool valida = true;
    bool noVerdes = true;
    //No puede haber 2 piezas verdes juntas nunca
    if (k > 0 && datos[k] == 2) {
        int i = 0;
        while (i < n && noVerdes) {
            if (datos[i] == 2) noVerdes = false;
            else ++i;
        }
    }
    //Siempre debe haber alguna roja en la base
    if (k == n - 1 && datos[k] != 1) valida = false;

    return valida && noVerdes; 
}


// función que resuelve el problema
void resolver(vector<int>& datos, int n, int k, const vector<int>& colores) {
    for (int i = 0; i < 3; ++i) {
        datos[k] = colores[i];
        if (esValida(datos, k, n)) {
            if (k == n - 1) {
                for (int a = n-1; a>=0; --a) {
                    if (datos[a] == 0) cout << "azul ";
                    else if (datos[a] == 1) cout << "rojo ";
                    else if (datos[a] == 2) cout << "verde ";
                }
                cout << endl;

            }
            else if (k < n - 1) {
                k++;
                resolver(datos, n, k, colores);
                --k;
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
    if (n == 0)
        return false;

    vector<int> colores = { 0,1,2 };
    vector<int> datos(n);
    resolver(datos, n, 0, colores);

    cout << endl;

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
