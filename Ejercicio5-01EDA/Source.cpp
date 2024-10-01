// Nombre del alumno: Muxu Rubia Luque
// Usuario del Juez: VJ53


#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>
#include <string>
using namespace std;

// función que resuelve el problema
string resolver(string dato) {
    stack<char> pila;
    for (auto dato : dato) {
        //pila vacia
        if (pila.empty() && (dato == '(' || dato == ')' ||
            dato == '{' || dato == '}' || dato == '[' || dato == ']')) pila.push(dato);

        //pila no vacia
        else {
            //Si la entrada es una apertura se añade a la pila
            if (dato == '(' || dato == '{' || dato == '[') pila.push(dato);

            //si la entrada es un cierre se comprueba si el ultimo es la apertura que le corresponde
            // y si es asi, se elimina el ultimo y no se inserta el dato
            if (dato == ')' && pila.top() == '(') {
                pila.pop();
            }
            else if (dato == '}' && pila.top() == '{') {
                pila.pop();
            }
            else if (dato == ']' && pila.top() == '[') {
                pila.pop();
            }

            //Si el ultimo dato no coincide en apertura con el que se quiere insertar
            //se inserta el dato
            else if (dato == ')' || dato == '}' || dato == ']') pila.push(dato);

        }
    }

    if (pila.empty()) return "SI";
    else return "NO";

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    string datos;
    cin >> datos;
    if (!std::cin)
        return false;

    cout << resolver(datos) << endl;

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