// Nombre del alumno: Muxu Rubia Luque
// Usuario del Juez: VJ53


#include <iostream>
#include <iomanip>
#include <fstream>
#include <deque>
using namespace std;

using Cola = deque<int>;
//Algoritmo de coste lineal O(N), siendo N el numero de datos que contiene la cola doble
// ya que tanto push back como push front tienen coste lineal

// función que resuelve el problema
Cola resolver(int N) {
    int dato;
    Cola cola;


    for (int i = 0; i < N; ++i) {
        cin >> dato;
        if (dato <= 0) cola.push_front(dato);
        else cola.push_back(dato);
    }

    return cola;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int N; 
    cin >> N;
    if (N ==0)
        return false;

    Cola sol = resolver(N);

    // escribir sol
    for (auto it = sol.begin(); it != sol.end(); ++it)
        cout << (*it) << ' ';

    cout << endl;
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


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
