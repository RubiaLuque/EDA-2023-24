// Plantilla para el ejercicio de Venta de libros

#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <map>
#include <unordered_map>
#include <utility>
#include <list>
#include <algorithm>

using namespace std;

struct DatosLibros {
    int numEjemplares = 0;
    int numVentas = 0;
    list<string>::iterator it = {};
};

using Libros = unordered_map<string, DatosLibros>; //Libros y numeros de ejemplares por cada uno
using Top = map<int, list<string>, greater<int>>; //Ventas y libros con dicho numero de ventas

class VentaLibros {
private:
    Libros libros;
    Top top;
public:
    //Constante
    void nuevoLibro(int numEjemplares, string libro) {
        //Si no estaba en el sistema se inserta
        if(libros.find(libro) == libros.end()) //Constante
            libros.insert({ libro, {numEjemplares, 0, {} } });

        //Si ya estaba, se añaden los ejemplares
        else {
            libros[libro].numEjemplares += numEjemplares; //Constante
        }
    }

    //Logaritmico en el numero de elementos en top
    void comprar(string libro) {
        //Si el libro no esta, se produce error
        if (libros.find(libro) == libros.end()) { //Constante
            throw invalid_argument("Libro no existente");
        }
        //Si está, pero no le quedan ejemplares se lanza otro error
        else if (libros[libro].numEjemplares == 0) {
            throw out_of_range("No hay ejemplares");
        }
        //No se cumple lo anterior: se compra de manera normal
        else {
            libros[libro].numEjemplares--; //Se elimina un ejemplar 
            
            if (top.find(libros[libro].numVentas) == top.end()) { //Logaritmico
                top[1].push_front(libro); //Van del mas actual comprado al menos actual si ambos libros tienen mismas ventas
                libros[libro].it = top[1].begin(); //Constante
                libros[libro].numVentas++; //Constante

            }
            else { //Si ya estaba en el map de comprados, se elimina de su numero de ventas antigua y se 
                //añade a la nueva

                //Se elimina de la lista de ventas anterior
                top[libros[libro].numVentas].erase(libros[libro].it);
                //Se le suma 1 venta mas
                libros[libro].numVentas++; //Constante
                top[libros[libro].numVentas].push_front(libro); //Constante
                //Se le reasigna el iterador al actual numro de ventas
                libros[libro].it = top[libros[libro].numVentas].begin();

            }
        }
    }

    //Constante
    bool estaSistema(string libro) {
        auto it = libros.find(libro);
        return it != libros.end();
    }

    //Constante
    void elimLibro(string libro) {
        top[libros[libro].numVentas].erase(libros[libro].it); //Constante
        libros.erase(libro); //Constante
    }

    //Constante O(1)
    int numEjemplares(string libro) {
        return libros[libro].numEjemplares;
    }

    //Lineal en numero de vueltas al bucle: 10
    list<string> top10() {
        list<string> top10;
        int i = 0;
        auto it = top.begin();
        while (i < 10 && it != top.end()) {
            for (auto it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2) {
                top10.push_back((*it2));
                ++i;
            }
            if(it != top.end())
                ++it;
        }
        return top10;
    }

};

// Muestra el contenido de una lista
template <class T>
void mostrar(list<T> const& l) {
    for (auto const& e : l) {
        cout <<"    " << e << '\n';
    }
}

bool resuelveCaso() {
    int numOp;

    cin >> numOp;
    if (!cin) return false;

    VentaLibros amazon;

    string operacion, titulo;

    for (int i = 0; i < numOp; ++i) {
        cin >> operacion;
        cin.ignore(1); // saltar blanco
        if (operacion == "nuevoLibro") {
            int unidades;
            cin >> unidades;
            cin.ignore(1);
            getline(cin, titulo);
            amazon.nuevoLibro(unidades, titulo);
        }
        else if (operacion == "comprar") {
            getline(cin, titulo);
            try {
                amazon.comprar(titulo);
            }
            catch (out_of_range const& e) {
                cout << e.what() << '\n';
            }
            catch (invalid_argument const& e) {
                cout << e.what() << '\n';
            }
        }
        else if (operacion == "estaLibro") {
            getline(cin, titulo);
            if (amazon.estaSistema(titulo)) {
                cout << "El libro " << titulo << " esta en el sistema\n";
            }
            else {
                cout << "No existe el libro " << titulo << " en el sistema\n";
            }
        }
        else if (operacion == "elimLibro") {
            getline(cin, titulo);
            amazon.elimLibro(titulo);
        }
        else if (operacion == "numEjemplares") {
            getline(cin, titulo);
            if (amazon.estaSistema(titulo)) {
                cout << "Existen " << amazon.numEjemplares(titulo) << " ejemplares del libro " << titulo << '\n';
            }
            else {
                cout << "No existe el libro " << titulo << " en el sistema\n";
            }
        }
        else if (operacion == "top10") {
            cout << "TOP10\n";
            mostrar(amazon.top10());
        }
    }
    // fin del caso
    cout << "---\n";
    return true;

}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

    while (resuelveCaso());
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
