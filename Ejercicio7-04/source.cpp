#include <iostream>
#include <fstream>
#include <cctype>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>
#include <set>

using namespace std;

using Alumnos = unordered_map<string, string>; //Alumno y primer deporte elegido
using Deportes = unordered_map<string, set<string>>; //Deporte y alumnos

struct Data {
    string deporte = "";
    int numAlumnos = 0;
};

void resolver(string const& primerDeporte, Deportes& deportes) {
    string deporte, alumno;
    deporte = primerDeporte;
    Alumnos alumnos; //unordered map de alumnos y primer deporte que han elegido

    while (deporte != "_FIN_") {
        //El deporte no se encontraba registrado
        if (deportes.find(deporte) == deportes.end()) {
            deportes.insert({ deporte,{} }); //Se inserta el nuevo deporte con un set vacio de alumnos
        }

        cin >> alumno;
        while (!isupper(alumno[0]) && alumno != "_FIN_") {

            auto it = deportes[deporte].find(alumno); //iterador que apunta al alumno que se ha leido de entrada

            //Si el alumno no estaba inscrito en ese deporte anteriormente
            if ((it) == deportes[deporte].end()) {

                //Se comprueba que no este en otro deporte mirando si se encuentra en el map de alumnos y deportes
                if (alumnos.find(alumno) == alumnos.end()) {
                    deportes[deporte].insert({ alumno });
                    alumnos.insert({alumno, deporte});
                }
                //Si estaba en otro deporte, no se inserta y se borra de donde estuviese
                else {
                    string dep = alumnos[alumno];
                    deportes[dep].erase({ alumno });
                }
            }

            cin >> alumno;
        }
        //El ultimo alumno que lee es el deporte de la siguiente pagina
        deporte = alumno;
    }

    //Los datos que nos interesan se guardan en un vector
    vector<Data> aux;
    for (auto& elem : deportes) {
        Data d; 
        d.deporte = elem.first; //Nombre del deporte
        d.numAlumnos = elem.second.size(); //numero de elementos que tiene el set
        aux.push_back(d);
    }

    //Se ordenan en base al numero de alumnos apuntados correctamente y el nombre del deporte
    sort(aux.begin(), aux.end(), [&](Data& a, Data& b) {
        if (a.numAlumnos > b.numAlumnos) return true;

        else if (a.numAlumnos == b.numAlumnos) {
            if (a.deporte < b.deporte) return true;
            else return false;
        }
        else return false;
        });

    //Se escribe por pantalla los resultados
    for (auto e : aux) {
        cout << e.deporte << " " << e.numAlumnos << "\n";
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    string primerDeporte;
    cin >> primerDeporte;
    if (!cin) return false;

    Deportes deportes;
    resolver(primerDeporte, deportes);

    cout << "---\n";
    return true;
}

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
#endif

    return 0;
}