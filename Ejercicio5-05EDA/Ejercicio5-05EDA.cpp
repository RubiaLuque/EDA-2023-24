
#include <iostream>
#include <iomanip>
#include <fstream>
#include "queue_eda.h"
using namespace std;

template <class T>
class queue_plus : public queue<T> {
    using Nodo = typename queue<T>::Nodo;
    
public:
    void invertir() {

        while(this->prim->sig->sig != this->ult) {
            //Nos guardamos referencias al nodo actual y dos nodos mas alla para no perderlos
            Nodo* aux = this->prim;
            Nodo* auxSigSig = this->prim->sig->sig;
            //El nodo actual se convierte en el siguiente
            this->prim = this->prim->sig;
            //El nodo siguiente se vuelve el actual
            this->prim->sig = aux;
            this->prim = auxSigSig
        }
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int n;
    queue_plus<int> q;
    cin >> n;
    if (!std::cin) return false;
    
    //Leer la cola
    while (n != 0) {
        q.push(n);
        cin >> n;
    }

    // Llamada a la funcion pedida
    q.invertir();

    // Muestro la cola y ya de paso se vacía
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }

    cout << endl;

    return true;
}

//#define DOMJUDGE
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