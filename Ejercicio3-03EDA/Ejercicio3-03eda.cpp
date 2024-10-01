// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

bool esValida(const vector<int>& sol, int k) {
    bool correcto = true;
    int i = 0;
    while (i < k && correcto) {
        //Se verifica que no compartan diagonal ni columna o fila
        if (sol[i] == sol[k] || abs(sol[k] - sol[i]) == k - i) correcto = false;
        else i++;
    }

    return correcto;
}

// función que resuelve el problema
void resolver(vector<int>& sol, int k, int n, int& numFormas) {
    //Para podar basta con recorrer la mitad de soluciones, ya que son simetricas con respecto de la diagonal
    for (int i = 0; i < n/2; ++i) {
        sol[k] = i;
        if (esValida(sol, k)) {
            if(k == n/2-1)
                numFormas += 2;
            else {
                if(i < n/2)
                    resolver(sol, k+1, n, numFormas);
            }
        }
    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n; 
    cin >> n;

    vector<int> sol(n);
    int numFormas = 0;
    resolver(sol, 0, n,numFormas);
    // escribir sol
    cout << numFormas << endl;

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