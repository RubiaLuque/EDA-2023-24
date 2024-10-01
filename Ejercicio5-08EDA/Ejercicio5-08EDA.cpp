#include <iostream>
#include <iomanip>
#include <fstream>
#include "queue_eda.h"
using namespace std;


template <class T>
class queue_plus : public queue<T> {
    using Nodo = typename queue<T>::Nodo;

public:
    void cuela(const int p, queue_plus<T>& colegas) {
        //Se modifica la cola inicial, no se crea nada nuevo

        //Nos guardamos el primer elemento de la cola para recuperarlo despues
        Nodo* primAux = this->prim;

        while (this->prim->elem != p) {
            this->prim = this->prim->sig;
            if (this->prim == this->ult && this->prim->elem != p) { //No se hace nada porque no esta p en la cola
                this->prim = primAux; //Se devuelve prim al principio
                return;
            }
        }

        //Nos guardamos el siguiente al primer nodo actual
        Nodo* primSigAux = this->prim->sig;
        //El siguiente del amigo pringao es el primer colega
        this->prim->sig = colegas.prim;
        //Detras del ultimo colega va el siguiente de la cola inicial
        colegas.ult->sig = primSigAux;
        //Se devuelve el primer elemento de la cola al inicial
        this->prim = primAux;

        this->nelems += colegas.nelems;
        //Se pone colegas a nullptr para que no haya problemas de comparticion de memoria
        colegas.prim = nullptr;
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    queue_plus<int> q; //Cola inicial
    cin >> n;
    if (n == -1) return;
    while (n != -1) {
        q.push(n);
        cin >> n;
    }

    int pringao; 
    cin >> pringao;

    queue_plus<int> colegas;
    int colega;
    cin >> colega;
    while (colega != -1) {
        colegas.push(colega);
        cin >> colega;
    }
    
    // escribir cola inicial
    for (int i = 0; i < q.size(); ++i) {
        cout << q.front() << " ";
        n = q.front();
        q.pop();
        q.push(n);
    }
    cout << "\n";

    // llamada a metodo
    q.cuela(pringao, colegas);

    
    // Ahora imprimimos la cola y de paso la dejamos vacía
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }

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
    cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}
