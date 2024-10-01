#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

using TablaRefs = map<string, list<int>>;

//En total, el coste seria O(N*P*C*logM)
//Donde:
/*
- N es el numero de lineas que se leen de entrada
- M el numero de palabras de la linea mas larga en caso peor
- C el numero de letras de la palabra mas larga en caso peor
- M el numero de elementos que contiene el mapa en caso peor
*/
void referencias(int numLineas, TablaRefs& refs) {
    string palabra;
    char c;
    //Coste lineal con respecto al numero de lineas que haya en la entrada
    for (int numLinea = 1; numLinea <= numLineas; numLinea++) {
        cin.get(c);
        while (c != '\n') { //Coste lineal con respecto al numero de palabras que se encuentren en la lista
            cin.unget(); // Se vuelve a dejar c en cin (por si era la 1ª letra de la linea)
            cin >> palabra;
            if (palabra.size() > 2) {
                //Itera sobre la palabra para modificarla toda por su variante en minuscula
                //Coste lineal con respecto al numero de letras que tenga la palabra
                transform(palabra.begin(), palabra.end(), palabra.begin(),
                    [](char c) {return tolower(c); });

                //Si ya estaba registrada, se añade el numero de linea a la lista si este no se habia puesto
                if (refs.find(palabra) != refs.end() && refs[palabra].back()!= numLinea) {
                    refs[palabra].push_back(numLinea); //Coste constante
                }
                else { //No existe la palabra
                    //Coste logaritmico con respecto al numero de elementos del mapa
                    refs.insert({ palabra, {numLinea} });  
                }
                
            }

            cin.get(c);
        }
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    char c;
    cin >> n;
    cin.get(c); // Me salto el \n de detrás del N
    if (n == 0)
        return false;

    TablaRefs refs;
    referencias(n, refs);

    // escribir sol
    for (auto ref : refs) {
        cout << ref.first << " ";
        for (auto num : ref.second) {
            cout << num << " ";
        }

        cout << "\n";
    }

    cout << "---\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso())
        ;

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}