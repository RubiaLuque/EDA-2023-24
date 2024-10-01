
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

struct Data {
    bool caucasico;
    int numPares;
};

Data caucasico(const vector<int>& v, int ini, int fin) {
    //pIz y pDr indican el numero de elementos pares en la izquierda y la derecha
    int n = fin -ini;
    //Un vector con un elemento es caucasico por definicion
    if (n == 1)// 1 elemento
    {   
        return { true, 0 };
    }
    //Aumenta el numero de pares segun corresponda cuando quedan 2 elementos
    else if (n == 2) {
        if (v[ini] % 2 == 0 && v[fin - 1] % 2 == 0) {
            return { true,2 };
        }
        else {
            if (v[ini] % 2 == 0) return { true,1 };
            else if (v[fin - 1] % 2 == 0) return { true,1 };
            else return { true,0 };
        }
        
    }
    //Resto de casos
    else {
        Data iz, dr;
        
        int mitad = (ini + fin) / 2;

        iz = caucasico(v, ini, mitad);
        dr = caucasico(v, mitad, fin);

        //Comprueba si la resta, en valor absoluto del numero de pares de la izquierda y la derecha es, como mucho, 2
        return { (abs(iz.numPares - dr.numPares) <= 2) && iz.caucasico && dr.caucasico, iz.numPares + dr.numPares };

    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    if (n == 0) return false;
    vector<int> sec(n);
    for (int& e : sec) cin >> e;
    
    cout << (caucasico(sec, 0, n).caucasico ? "SI" : "NO") << endl;
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
    //system("PAUSE");
#endif

    return 0;
}