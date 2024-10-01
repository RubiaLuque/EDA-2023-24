// Nombre del alumno Muxu Rubia Luque
// Usuario del Juez VJ53


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_RESERVAS = 50000;
class Teatro {
public:
    bool nueva_reserva(int inicio, int fin, string nombre) {
        if (num_reservas >= MAX_RESERVAS) return false;
        else {
            //Buscar por la derecha

            //Buscar por la izquierda
        }


        //for (auto reserva : reservas) {
        //    if ((inicio >= reserva.inicio && inicio <= reserva.fin) ||
        //        (fin >= reserva.inicio && fin <= reserva.fin)) {
        //        return false;
        //    }
        //    else if (inicio <= reserva.inicio && fin >= reserva.fin) return false;
        //}

        //
        ////Se añade la nueva reserva si es posible hacerla
        //reservas.push_back({ inicio, fin, nombre });
        //num_reservas++;
        return true;

    }

    //Coste lineal en numero de reservas
    string nombre_reserva(int num_butaca) {
        for (auto reserva : reservas) {
            if (num_butaca <= reserva.fin && num_butaca >= reserva.inicio) 
                return reserva.nombre;
        }

        return "";
    }

private:
    struct Reserva {
        int inicio;
        int fin;
        string nombre;
    };

    vector<Reserva> reservas;
    int num_reservas =0;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int N, Q;
    cin >> N >> Q;
    if (N == 0 && Q==0)
        return false;

    Teatro t;
    for (int i = 0; i < N; ++i) {
        int ini, fin;
        string nombre;
        cin >> ini >> fin >> nombre;
        bool sol = t.nueva_reserva(ini, fin, nombre);
        sol ? cout << '.' : cout << 'X';
    }
    cout << '\n';

    for (int i = 0; i < Q; ++i) {
        int butaca;
        cin >> butaca;
        string sol = t.nombre_reserva(butaca);
        (sol == "") ? cout << "LIBRE\n" : cout << sol << '\n';
    }

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
    system("PAUSE");
#endif

    return 0;
}
