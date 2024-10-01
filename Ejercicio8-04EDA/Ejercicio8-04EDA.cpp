
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <unordered_map>
#include <list>
using namespace std;

struct Iteradores {
    int puntos;
    std::list<string>::iterator it;
};

using Conductores = unordered_map<string, Iteradores>; //Conductores con dni y puntos
using Puntos = vector<list<string>>; //Puntos del 0 al 15 con el numero de conductores que los poseen
//using ListaDNI = unordered_map<int, vector<string>>; //Unordered map con el numero posible de puntos y los dni de los
                                                    // conductores que tienen dichos puntos

class carnet_puntos {
private:
    Conductores conductores;
    Puntos puntos = vector<list<string>>(16); //Tiene 16 posiciones porque va de 0 a 15

public:
    //Añade nuevo conductor
    void nuevo(string dni) {
        if (conductores.find(dni) != conductores.end()) {
            throw domain_error("Conductor duplicado");
        }
        //Se añade con 15 puntos por defecto
        puntos[15].push_front(dni); //Constante

        auto it = puntos[15].begin(); //El iterador nos va a permitir acceder mas tarde sin tener que hacer una busqueda
        conductores.insert({ dni, {15,it} }); //Constante

    }

    //Le quita puntos a un conductor tras infraccion
    void quitar(string dni, int ptos) {
        if (conductores.find(dni) == conductores.end()) {
            throw domain_error("Conductor inexistente");
        }

        //Constante
        int ptosIni = conductores[dni].puntos;

        conductores[dni].puntos -= ptos;

        int ptosNuevo = conductores[dni].puntos;

        //Si se le han quitado mas puntos de los que tenia, se pone a 0
        if ((conductores[dni].puntos) < 0) {
            conductores[dni].puntos = 0;
            ptosNuevo = 0;
        }
        //No se hace nada si no se puede perder mas puntos de los que tiene
        if (ptosIni == ptosNuevo) return;

        //Se cambia el numero de conductores con puntos en el map de puntos
        //Constante, se accede directamente al iterador sin hacer busqueda
        conductores[dni].it = puntos[ptosIni].erase(conductores[dni].it);
        

        //Constante
        puntos[ptosNuevo].push_front(dni);
        auto it = puntos[ptosNuevo].begin(); 
        //Se cambia el iterador al nuevo
        conductores[dni].it = it; //Constante
    }

    //Recuperar puntos
    void recuperar(string dni, int ptos) {
        if (conductores.find(dni) == conductores.end()) {
            throw domain_error("Conductor inexistente");
        }

        //Constante
        int ptosIni = conductores[dni].puntos;

        conductores[dni].puntos += ptos;

        int ptosNuevo = conductores[dni].puntos;

        //Si se le han quitado mas puntos de los que tenia, se pone a 0
        if ((conductores[dni].puntos) > 15) {
            conductores[dni].puntos = 15;
            ptosNuevo = 15;
        }

        //No se hace nada si al recuperar puntos ya los tenia todos
        if (ptosIni == ptosNuevo) return;

        //Se cambia el numero de conductores con puntos en el map de puntos
        //Constante
        conductores[dni].it = puntos[ptosIni].erase(conductores[dni].it);

        //Constante
        puntos[ptosNuevo].push_front(dni);
        auto it = puntos[ptosNuevo].begin();
        //Se cambia el iterador al nuevo
        conductores[dni].it = it; //Constante
    }

    //Consulta cuantos puntos tiene el conductor con DNI dni y los devuelve
    int consultar(string dni) {
        if (conductores.find(dni) == conductores.end()) {
            throw domain_error("Conductor inexistente");
        }

        //Constante
        return conductores[dni].puntos;
    }

    //Cuantos conductores tienen ptos puntos
    int cuantos_con_puntos(int ptos) {
        if (ptos < 0 || ptos > 15) {
            throw domain_error("Puntos no validos");
        }

        //Tamaño de la lista
        //Constante
        return puntos[ptos].size();
    }

    list<string> lista_por_puntos(int ptos) {
        if (ptos < 0 || ptos > 15) {
            throw domain_error("Puntos no validos");
        }

        //Se devuelve la lista tal cual, ya que se han ido insertando en el orden pedido
        //Constante
        return puntos[ptos];
    }

};

bool resuelveCaso() {
    std::string orden, dni;
    int punt;
    std::cin >> orden;
    if (!std::cin)
        return false;

    carnet_puntos dgt;

    while (orden != "FIN") {
        try {
            if (orden == "nuevo") {
                cin >> dni;
                dgt.nuevo(dni);
            }
            else if (orden == "quitar") {
                cin >> dni >> punt;
                dgt.quitar(dni, punt);
            }
            else if (orden == "recuperar") {
                cin >> dni >> punt;
                dgt.recuperar(dni, punt);
            }
            else if (orden == "consultar") {
                cin >> dni;
                punt = dgt.consultar(dni);
                cout << "Puntos de " << dni << ": " << punt << '\n';
            }
            else if (orden == "cuantos_con_puntos") {
                cin >> punt;
                int cuantos = dgt.cuantos_con_puntos(punt);
                cout << "Con " << punt << " puntos hay " << cuantos << '\n';
            }
            else if (orden == "lista_por_puntos") {
                cin >> punt;
                auto const& lista = dgt.lista_por_puntos(punt);
                cout << "Tienen " << punt << " puntos:";
                for (auto const& dni : lista)
                    cout << ' ' << dni;
                cout << '\n';
            }
            else
                cout << "OPERACION DESCONOCIDA\n";
        }
        catch (std::domain_error e) {
            std::cout << "ERROR: " << e.what() << '\n';
        }
        std::cin >> orden;
    }
    std::cout << "---\n";
    return true;
}

int main() {

    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // restablecimiento de cin
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    //system("pause");
#endif
    return 0;
}
