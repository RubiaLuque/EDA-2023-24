// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

bool esValida(const vector<char>& sol, int k) {
    bool valida = true;
    int i = 0;
    while (i < k && valida) {
        if (sol[i] == sol[k]) valida = false;
        else i++;
    }

    return valida;
}

// función que resuelve el problema
void resolver(vector<char>& sol, int m, int n, int k) { //m: numero de letras a usar, n: numero de letras combinadas
    for (int i = 0; i < m; ++i) {
        sol[k] = i + 97; //En char 'a' equivale a int 97

        //Se comprueba si es valida o no viendo si hay repeticiones
        if (esValida(sol, k)) {

            if (k == n - 1) { //Se mira si es solucion
                for (int a = 0; a < n; ++a) {
                    cout << sol[a];
                }
                cout << endl;
            }
            else if (k < n - 1) {
                resolver(sol, m, n, k + 1);
            }
        }

    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int m, n;
    cin >> m >> n;

    if (!std::cin)
        return false;

    vector<char> datos(n);
    resolver(datos,m, n, 0);
    cout << endl; //Separar casos de prueba
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