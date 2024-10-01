
#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <stdexcept>
#include <list>
#include <unordered_map>
using namespace std;

using cancion = std::string;
using artista = std::string;

using ListaReproduccion = list<cancion>; //Almacena solo las canciones de la lista de reproduccion
using Recientes = list<cancion>; //Almacena solamente las ultimas canciones esuchadas en orden

struct DatosCancion {
    int tiempoDuracion;
    ListaReproduccion::iterator playlistIt;
    Recientes::iterator recientesIt;
};

//Almacena todas las canciones con un iterador a la lista de arriba que le corresponda y un int con su tiempo de duracion
using Canciones = unordered_map<cancion, DatosCancion>;

class iPud {
private:
    
    ListaReproduccion playlist;
    Recientes recientes;
    int tiempoTotal = 0;
    Canciones canciones;

public:
    void addSong(cancion cancion, artista artista, int duracion) {
        //Constante
        if (canciones.find(cancion) != canciones.end()) {
            throw invalid_argument("addSong");
        }
        //Constante
        canciones.insert({ cancion,{duracion, playlist.end(), recientes.end()}});
    }

    void addToPlaylist(cancion cancion) {
        //Constante
        if (canciones.find(cancion) == canciones.end()) {
            throw invalid_argument("addToPlaylist");
        }

        //Se mira a ver si ya estaba en la playlist
        if (canciones[cancion].playlistIt != playlist.end()) return;

        //Si no lo estaba, se añade al final
        //Constante
        playlist.push_back(cancion);
        auto& it = --playlist.end(); //Iterador al ultimo elemento de la lista
        canciones[cancion].playlistIt = it;

        //Se suma la duracion de la cancion al tiempo total de la playlist
        //Constante
        tiempoTotal += canciones[cancion].tiempoDuracion;

    }

    string current() {

        if (playlist.size() == 0) {
            throw invalid_argument("current");
        }

        //Constante
        return playlist.front();


    }

    cancion play() {
        //Si la playlist esta vacia, no tiene efecto
        if (playlist.empty()) {
            throw invalid_argument("play");
        }

        
        //Se le resta el tiempo de dicha cancion al tiempo total
        tiempoTotal -= canciones[playlist.front()].tiempoDuracion;
        //Se añade en la lista de reproducciones
        recientes.push_back(playlist.front());
        //Se cambia el iterador de la cancion por el de la otra lista
        canciones[playlist.front()].recientesIt = --recientes.end();
        //Se elimina de la lista de playlist
        //Su iterador de playlist pasa a estar fuera de la lista
        canciones[playlist.front()].playlistIt = playlist.end();
        playlist.pop_front();

        return recientes.back();
    }

    int totalTime() {
        //Constante
        return tiempoTotal;
    }

    //Lineal en tiempo de N o del numero de elementos de recientes si este es menor que N
    list<cancion> recent(int N) {
        list<cancion> aux;

        auto it = recientes.begin();
        int i = 0;
        while (i < N && it != recientes.end()) {
            aux.push_front(*it);
            if(it != recientes.end())
                ++it;
            ++i;
        }

        return aux;
    }

    void deleteSong(cancion cancion) {
        //Constante
        if (canciones.find(cancion) == canciones.end()) {
            return;
        }

        //Se trata de borrar de ambas listas ya que puede estar en una de ellas
        //Constante porque se le pasa un iterador
        if(canciones[cancion].playlistIt != playlist.end())
            canciones[cancion].playlistIt = playlist.erase(canciones[cancion].playlistIt);

        if(canciones[cancion].recientesIt != recientes.end())
            canciones[cancion].recientesIt = recientes.erase(canciones[cancion].recientesIt);
        //Constante
        canciones.erase(cancion);
    }
};

bool resuelve() {
    string operacion;
    cin >> operacion;
    if (!cin)
        return false;
    cancion tit; artista aut; int dur;
    iPud ipud;
    while (operacion != "FIN") {
        try {
            if (operacion == "addSong") {
                cin >> tit >> aut >> dur;
                ipud.addSong(tit, aut, dur);
            }
            else if (operacion == "addToPlaylist") {
                cin >> tit;
                ipud.addToPlaylist(tit);
            }
            else if (operacion == "current") {
                tit = ipud.current(); // aunque no se hace nada, puede producir error
            }
            else if (operacion == "play") {
                try {
                    string tocando = ipud.current(); // para saber si la lista es vacía
                    ipud.play();
                    cout << "Sonando " << tocando << '\n';
                }
                catch (invalid_argument e) {
                    cout << "No hay canciones en la lista\n";
                }
            }
            else if (operacion == "totalTime") {
                cout << "Tiempo total " << ipud.totalTime() << '\n';
            }
            else if (operacion == "recent") {
                int N;
                cin >> N;
                auto lista = ipud.recent(N);
                if (lista.empty())
                    cout << "No hay canciones recientes\n";
                else {
                    cout << "Las " << lista.size() << " mas recientes\n";
                    for (auto const& s : lista)
                        cout << "    " << s << '\n';
                }
            }
            else if (operacion == "deleteSong") {
                cin >> tit;
                ipud.deleteSong(tit);
            }
            else { // operacion desconocida
                assert(false);
            }
        }
        catch (invalid_argument e) {
            cout << "ERROR " << e.what() << '\n';
        }
        cin >> operacion;
    }
    cout << "---\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelve());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    //system("pause");
#endif
    return 0;
}
