
//Muxu Rubia Luque
//VJ53

#include <iostream>
#include <iomanip>
#include <fstream>
#include "list_eda.h"
using namespace std;


template <class T>
class list_plus : public list<T> {
    using Nodo = typename list<T>::Nodo;

public:
    //Coste lineal en base al numero de elementos de la lista en caso peor -> O(n) siendo n el #elems de la lista
    //Recorre la lista varias veces para asignar los diferentes nodos
    void adelantar(int pos, int length, int newPos) {
        int n = this->size();
        Nodo* final = this->fantasma;
        //posicion de origen o destino del segmento no validas, lista vacia o segmento no valido
        if (length == 0 || pos > n - 1 || newPos < 0 || n == 0 || newPos == pos) {
            return;
        }
        //el segmento se sale de la lista
        else if (pos + length > n) {
            //Se cogen los n - pos elementos
            for (int i = 0; i <= n - 1; ++i) {
                final = final->sig;
            }

        }
        //resto de casos
        else {
            for (int i = 0; i < pos + length; ++i) {
                final = final->sig;
            }

        }

        Nodo* principio = this->fantasma;
        for (int i = 0; i <= pos; ++i) {
            principio = principio->sig;
        }

        //nodo de la nueva posicion y su anterior
        Nodo* newPosi = this->fantasma;
        Nodo* ant_newPos = this->fantasma;

        for (int i = 0; i <= newPos; ++i) {
            ant_newPos = newPosi;
            newPosi = newPosi->sig;
        }

        //Se enlazan los nodos anterior y posterior a los del segmento entre si
        principio->ant->sig = final->sig;
        final->sig->ant = principio->ant;

        //se colocan los nodos en el lugar que les corresponde
        ant_newPos->sig = principio;
        principio->ant = ant_newPos;

        newPosi->ant = final;
        final->sig = newPosi;
    }
};

//#define DOMJUDGE
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    char e;
    int n, pos, length, dif;
    list_plus<char> l;

    // leer los datos de la entrada
    cin >> n >> pos >> length >> dif;
    for (int i = 1; i <= n; ++i) {
        cin >> e;
        l.push_back(e);
    }
    int newPos = pos - dif;
    l.adelantar(pos, length, newPos);

    // Le damos una vuelta para comprobar que la lista está bien formada
    for (int i = 0; i < l.size(); ++i) {
        e = l.back();
        l.pop_back();
        l.push_front(e);
    }

    // Ahora imprimimos la lista y de paso la dejamos vacía (tb para probar su consistencia)
    while (!l.empty()) {
        cout << l.front() << " ";
        l.pop_front();
    }
    cout << endl;
}


//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input1.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}
