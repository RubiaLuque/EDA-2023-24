#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;


using Pelicula = string;
using Actor = string;

struct DatosPelicula {
    Actores actores;
    int numEmisiones=0;
};

using Actores = map<Actor, int, less<string>>;
using RepartosPeliculas = unordered_map<Pelicula, DatosPelicula>;

//Se leen todas las peliculas con sus respectivos repartos
//Coste O(P*P*A*logA*logA), siendo A el numero de actores y P el numero de peliculas
void leerRepartos(int numPeliculas, RepartosPeliculas& peliculas) {
    Pelicula peli; int numActores;
    Actor actor; int minutos;

    for (int i = 0; i < numPeliculas; ++i) {
        cin >> peli; cin >> numActores;
        
        //Si no esta registrada la pelicula, se añade
        if (peliculas.find(peli) == peliculas.end()) {
            peliculas.insert(peli, {}); //El nombre de la pelicula y un struct con un map por ahora vacio
        }
        //Se añaden los actores participantes en dicha pelicula al reparto
        for (int j = 0; j < numActores; ++j) {
            cin >> actor >> minutos;
            //Si el actor no habia aparecido antes en esta pelicula, se añade
            if (peliculas[peli].actores.find(actor) == peliculas[peli].actores.end()) {
                peliculas[peli].actores.insert({{ actor, minutos }, 0});
            }
        }
    }
}


void procesarEmisiones(RepartosPeliculas & repartos, vector<string> const& secEmisiones) {
    //Se suman las emisiones
    for (auto& i : secEmisiones) {
        //Si la pelicula esta entre los datos que se han leido, se suma 1 al numero de emisiones
        if (repartos.find(i) != repartos.end()) {
            repartos[i].numEmisiones++;
        }
    }

    //Para cada pelicula se multiplica el numero de emisiones por el tiempo en pantalla de cada actor
    for (auto& p : repartos) {
        for (auto& a : repartos[p.first].actores) {
            a.second *= p.second.numEmisiones;
        }
        
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int numPelis, numEmisiones;
    cin >> numPelis;
    if (numPelis == 0)
        return false;

    // Lectura de los repartos de las peliculas
    RepartosPeliculas repartos;
    leerRepartos(numPelis, repartos);

    // Lectura de la secuencia de peliculas emitidas en vector<string>
    cin >> numEmisiones;
    vector<string> secEmisiones(numEmisiones);
    for (string& s : secEmisiones) cin >> s;

    procesarEmisiones(repartos, secEmisiones);

    //to-do
    string mejorPelicula;


    return true;
}


//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("data.txt");
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