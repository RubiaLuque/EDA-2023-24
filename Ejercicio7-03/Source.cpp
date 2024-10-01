// Nombre del alumno: Muxu Rubia Luque
// Usuario del Juez: VJ53


#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <set>
#include <climits>
using namespace std;

using big_int = long long int;

//Guarda el numero del capitulo y el indice donde ha aparecido, comenzando en 0
//Seria unordered_map<indice, capitulo>
using Series = unordered_map<int, big_int>;

// función que resuelve el problema
int resolver(Series& capitulos) {
    //Se lee cuantos capitulos se han estado observando
    int num_caps;
    cin >> num_caps;

    int max = INT_MIN;
    //Comienzo del segmento que se esta observando
    int ini = 0;

    for (int i = 0; i < num_caps; ++i) { //La i es el final del segmento que se esta observando
        //Se lee el numero del capitulo
        big_int cap;
        cin >> cap;
        bool repetido = false;

        //Se mira si esta repetido
        for (int x = ini; x < i; ++x) {
            if (capitulos.find(x) == capitulos.end()) {
                capitulos.insert({ i, cap });
            }
            else {
                repetido = true;
            }

        }

        //si esta repetido, se actualiza ini al indice siguiente de la primera aparicion


        //Si el capitulo no estaba registrado anteriormente, se registra en el indice que ha aparecido




    }

    return max;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada

    Series series;
    int sol = resolver(series);
    // escribir sol
    cout << sol << "\n";

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}