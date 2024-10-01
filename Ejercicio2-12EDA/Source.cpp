
/*
Nombre completo: Muxu Rubia Luque VJ53

*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema
char resolver(const vector<char>& sec, char prim, char ult, int ini, int fin) {
    int n = fin - ini; //Para delimitar el segmento que se quiere tratar
    //prim y ult son los delimitadores de las letras
    if (n == 1) { //Queda 1
        return ult -1;
    }
    else if (n == 2) { //Quedan 2 elementos
        int mitad = (ini + fin) / 2;
        char med = (ult + prim) / 2;
        if (sec[mitad] == med) return ult-1;
        else return prim+1;

    }
    else {
        int mitad = (ini + fin) / 2;

        //Si la letra de la mitad del segmento coincide con la esperada, se busca por la derecha
        char med = (ult + prim) / 2;
        if (sec[mitad] == med) {
            return resolver(sec, med, ult, mitad, fin);
        }
        else {
            //Si no coincide, se busca por la izquierda
            return resolver(sec, prim, med, ini, mitad);
        }
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    char prim, ult, n;
    cin >> prim >> ult;
    n = ult - prim;
    vector<char> sec(n);
    for (char& e : sec) cin >> e;
    cout << resolver(sec, prim, ult, 0, sec.size()) << endl;
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
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