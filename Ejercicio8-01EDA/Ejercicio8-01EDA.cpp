
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <map>
#include <set>
using namespace std;

using Conductores = unordered_map<string, int>; //Conductores con dni y puntos
using Puntos = map<int, int>; //Puntos del 0 al 15 con el numero de conductores que los poseen

class carnet_puntos {
private:
    Conductores conductores;
    Puntos puntos;
public:
    //Añade nuevo conductor
    void nuevo(string dni) {
        if (conductores.find(dni) != conductores.end()) {
            throw domain_error("Conductor duplicado");
        }
        //Se añade con 15 puntos por defecto
        conductores.insert({ dni, 15 });

        if (puntos.find(15) == puntos.end()) puntos[15] = 1;
        else puntos[15]++;
    }

    //Le quita puntos a un conductor tras infraccion
    void quitar(string dni, int ptos) {
        if (conductores.find(dni) == conductores.end()) {
            throw domain_error("Conductor inexistente");
        }
        //Constante
        int ptosIni = conductores[dni];

        conductores[dni] -= ptos;

        int ptosNuevo = conductores[dni];

        //Si se le han quitado mas puntos de los que tenia, se pone a 0
        if ((conductores[dni]) < 0) { 
            conductores[dni] = 0; 
            ptosNuevo = 0;
        }

        //Se cambia el numero de conductores con puntos en el map de puntos
        puntos[ptosIni]--;

        if (puntos.find(ptosNuevo) == puntos.end()) puntos[ptosNuevo] = 1;
        else puntos[ptosNuevo]++;

    }

    //Consulta cuantos puntos tiene el conductor con DNI dni y los devuelve
    int consultar(string dni) {
        if (conductores.find(dni) == conductores.end()) {
            throw domain_error("Conductor inexistente");
        }

        //Constante
        return conductores[dni];
    }

    //Cuantos conductores tienen ptos puntos
    int cuantos_con_puntos(int ptos) {
        if (ptos < 0 || ptos > 15) {
            throw domain_error("Puntos no validos");
        }
        
        if (puntos.find(ptos) == puntos.end()) {
            puntos[ptos] = 0;
        }
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
