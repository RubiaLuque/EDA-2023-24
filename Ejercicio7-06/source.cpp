
//Muxu Rubia Luque
//VJ53

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;


struct Problema {
    bool resuelto;
    int tiempo;
    int numFallos;
};

using umapP = unordered_map<string, Problema>;

struct Equipo{
    int numResueltos;
    int tiempoTotal;
    umapP problemas;
};

using umapE = unordered_map<string, Equipo>;

struct Resultado {
    string nombreEquipo;
    int numResueltos;
    int tiempoTotal;
};

//Coste total de O(N*logN + M) siendo N el numero de equipos y M el numero total de subidas de problemas
void procesaEnvios(vector<Resultado>& resultados) {
    string equipo, problema, veredicto;
    int minuto;

    umapE equipos;

    //lectura de entrada
    cin >> equipo;
    //Complejidad O(M) siendo M el numero de subidas de ejercicios
    while (equipo != "FIN") {
        cin >> problema >> minuto >> veredicto;

        auto itEquipo = equipos.find(equipo);

        //Si el equipo no estaba registrado:
        if (itEquipo == equipos.end()) {
            Problema p; 
            Equipo e;
            //Problema correcto
            if (veredicto == "AC") {
                p.resuelto = true;
                p.numFallos = 0;
                p.tiempo = minuto;

                e.numResueltos = 1;
                e.tiempoTotal = minuto;
            }
            else {
                p.resuelto = false;
                p.numFallos = 1;
                p.tiempo = minuto;

                e.numResueltos = 0;
                e.tiempoTotal = 0;
            }
            //Se inserta el problema directamente porque si no hay equipo, no hay problemas resueltos por ellos
            e.problemas.insert({ problema, p }); //O(1)

            equipos.insert({equipo, e});
        }
        //Ya estaba el equipo registrado
        else {
            //No habian subido el problema
            auto itProblema = itEquipo->second.problemas.find(problema); //Cada equipo tiene un umap de problemas
            if (itProblema == itEquipo->second.problemas.end()) {
                Problema p;
                //Problema correcto
                if (veredicto == "AC") {
                    p.resuelto = true;
                    p.numFallos = 0;
                    p.tiempo = minuto;

                    itEquipo->second.numResueltos += 1;
                    itEquipo->second.tiempoTotal += minuto;
                }
                //Problema incorrecto
                else {
                    p.resuelto = false;
                    p.numFallos = 1;
                    p.tiempo = minuto;

                }
                itEquipo->second.problemas.insert({ problema, p });
            }
            //Ya habian subido el problema
            else {
                //Correcto de antes
                    //No se hace nada
                //Incorrecto de antes
                if(!itProblema->second.resuelto){
                    //Correcto ahora
                    if (veredicto == "AC") {
                        itProblema->second.resuelto = true;
                        itProblema->second.tiempo = minuto;

                        itEquipo->second.numResueltos += 1;
                        itEquipo->second.tiempoTotal += minuto + 20 * (itProblema->second.numFallos);
                    }
                    //Incorrecto ahora tambien
                    else {
                        itProblema->second.resuelto = false;
                        itProblema->second.numFallos += 1;
                        itProblema->second.tiempo = minuto;
                    }
                }
            }

        }

        cin >> equipo;
    }

    //procesamiento de datos
    //Complejidad O(N), siendo N el numero de equipos
    for (auto equipo : equipos) {
        resultados.push_back({equipo.first, equipo.second.numResueltos, equipo.second.tiempoTotal});
    }

    //Complejidad O(N*logN), siendo N el numero de equipos
    std::sort(resultados.begin(), resultados.end(), [](const Resultado& r1, const Resultado& r2) {
        if (r1.numResueltos > r2.numResueltos) {
            return true;
        }
        else if (r1.numResueltos == r2.numResueltos) {
            if (r1.tiempoTotal < r2.tiempoTotal) return true;

            else if (r1.tiempoTotal == r2.tiempoTotal) {
                return r1.nombreEquipo < r2.nombreEquipo;
            }
            else return false;
        }
        else return false;

        });
    
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    
    vector<Resultado> resultados;
    procesaEnvios(resultados);

    // Se imprime la salida
    //Complejidad O(N) siendo N el numero de equipos
    for (int i = 0; i < resultados.size(); ++i) {
        cout << resultados[i].nombreEquipo << " " << resultados[i].numResueltos << " " 
            << resultados[i].tiempoTotal << endl;
    }
        cout << "---\n";
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input.txt");
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