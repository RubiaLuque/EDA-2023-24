#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;
using Diccionario = map<string, int>;

//Coste O(logN*logN) por la busqueda y la insercion de elementos en el map, siendo N el numero de elementos
// del diccionario con mayor tamaño
void leerDiccionario(Diccionario& diccionario) {
    char c;
    string clave;
    int valor;
    cin.get(c);
    while (c != '\n') {
        cin.unget();
        cin >> clave >> valor;
        if (diccionario.find(clave) == diccionario.end()) {
            diccionario.insert({ clave, valor });
        }

        cin.get(c);
    }
}

//Coste O(N*logA + A*logN + M + m + C), siendo:
// -N : numero de elementos del nuevo diccionario
// -A : numero de elementos del antiguo diccionario
// -M : numero de elementos del vector mas
// -m : numero de elementos del vector menos
// -C : numero de elementos del vector cambios
void resultado(Diccionario const& a, Diccionario const& n) {
    vector<string> mas;
    vector<string> menos;
    vector<string> cambio;

    //Se recorren en orden los pares clave-valor del nuevo diccionario
    for (auto& valorN : n) {
        auto it = a.find(valorN.first);

        //No esta en el diccionario antiguo
        if (it == a.end()) {
            mas.push_back(valorN.first);
        }
        //Si esta en el diccionario antiguo, pero cambiada
        else if ((*it).second != valorN.second) {
            cambio.push_back(valorN.first);
        }
    }
    
    //Se han eliminado entradas
    for (auto& valorA : a) {
        auto it = n.find(valorA.first);

        //No esta en el nuevo
        if (it == n.end()) {
            menos.push_back(valorA.first);
        }
    }

    if (cambio.empty() && mas.empty() && menos.empty()) cout << "Sin cambios\n";
    else {
        for (auto a : mas) {
            if (a == mas.front()) cout << "+ ";
            cout << a << " ";
            if (a == mas.back()) cout << "\n";
        }

        for (auto m : menos) {
            if (m == menos.front()) cout << "- ";
            cout << m << " ";
            if (m == menos.back()) cout << "\n";
        }

        for (auto c : cambio) {
            if (c == cambio.front()) cout << "* ";
            cout << c << " ";
            if (c == cambio.back()) cout << "\n";
        }
    }

}

void resuelveCaso() {
    Diccionario antiguo;
    Diccionario nuevo;
    leerDiccionario(antiguo);
    leerDiccionario(nuevo);
    
    resultado(antiguo, nuevo);
    cout << "---\n";
}


int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numCasos; char c;
    std::cin >> numCasos;
    cin.get(c);
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}
