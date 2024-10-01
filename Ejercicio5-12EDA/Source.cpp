// Nombre del alumno: Muxu Rubia Luque
// Usuario del Juez: VJ53


#include <iostream>
#include <iomanip>
#include <fstream>
#include <list>
using namespace std;


// función que resuelve el problema
void resolver(list<int>& datos, int num) {
    for (auto it = datos.begin(); it != datos.end();) {
        if ((*it) == num) {
            it = datos.erase(it);
            
        }
        else {
            ++it;
        }
    }
}

//#define DOMJUDGE
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    list<int> datos; 
    int dato;
    cin >> dato;
    while (dato != -1) {
        datos.push_back(dato);
        cin >> dato;
    }

    int num;
    cin >> num;

    for (auto elem : datos) {
        cout << elem << ' ';
    }
    cout << endl;

    resolver(datos, num);

    // escribir sol
    for (auto it = datos.begin(); it != datos.end(); ++it) {
        cout << (*it) << ' ';
    }
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

    int numCasos;
    cin >> numCasos;
    int i = 0;

    while (i < numCasos) {
        resuelveCaso();
        ++i;
    }
        


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}