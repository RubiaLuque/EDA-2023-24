

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

/*
Se trata de un problema que sigue el esquema de la mochila real.

Lo mejor para este problema es no tener en cuenta el orden y tan solo decidir si coges o no una cancion, importante si se elige para
la cara A, B o no se elige en sí.
La tupla solucion es un vector con valores int desde 0 a 2 que significan lo explicado arriba de manera que:
- 0: no se elige
- 1: cara A
- 2: cara B
para todas las canciones

*/

struct Cancion {
    int duracion;
    int puntos;
};

struct Solucion {
    vector<int> tupla;
    int k = 0;
    int n = 0;
    int ocupacionA = 0;
    int ocupacionB = 0;
    int puntuacion = 0;
    int mejorPuntuacion = -1;

    Solucion(int n) : tupla(vector<int>(n)), n(n) {};
};

void resolver(Solucion& sol, vector<Cancion> const& canciones, int duracion, vector<int> const& maxPuntosDesde) {
    //Se intenta para la cara A
    if ((sol.ocupacionA + canciones[sol.k].duracion) <= duracion) {
        sol.tupla[sol.k] = 1; //Un 1 indica que se ha introducido en la cara A
        sol.ocupacionA += canciones[sol.k].duracion;
        sol.puntuacion += canciones[sol.k].puntos;
        //Se mira si se esta al final del arbol
        if (sol.k == sol.n-1) {
            //PARTE DE OPTIMIZACION:
            if (sol.puntuacion > sol.mejorPuntuacion) sol.mejorPuntuacion = sol.puntuacion;
        }
        else {
            sol.k++; 
            //PARTE DE PODA:
            //Antes de hacer la recursion comprobamos que lo que nos va a aportar esa rama es mejor o no de lo que ya tenemos,
            //en caso de que no lo sea, nos evitamos recorrer esa parte del arbol, ganando en eficiencia
            if (sol.puntuacion + maxPuntosDesde[sol.k] > sol.mejorPuntuacion)
                resolver(sol, canciones, duracion, maxPuntosDesde);
            sol.k--;
        }
        sol.ocupacionA -= canciones[sol.k].duracion;
        sol.puntuacion -= canciones[sol.k].puntos;
    }

    //Se intenta para la cara B
    if (sol.ocupacionA != sol.ocupacionB && (sol.ocupacionB + canciones[sol.k].duracion) <= duracion) {
        sol.tupla[sol.k] = 2; //Un 2 indica que se ha introducido en la cara B
        sol.ocupacionB += canciones[sol.k].duracion;
        sol.puntuacion += canciones[sol.k].puntos;
        //Se mira si se esta al final del arbol
        if (sol.k == sol.n-1) {
            //PARTE DE OPTIMIZACION:
            if (sol.puntuacion > sol.mejorPuntuacion) sol.mejorPuntuacion = sol.puntuacion;
        }
        else {
            sol.k++;
            if (sol.puntuacion + maxPuntosDesde[sol.k] > sol.mejorPuntuacion)
                resolver(sol, canciones, duracion, maxPuntosDesde);
            sol.k--;
        }
        sol.ocupacionB -= canciones[sol.k].duracion;
        sol.puntuacion -= canciones[sol.k].puntos;
    }

    //No se coge la cancion
    sol.tupla[sol.k] = 0;
    if (sol.k == sol.n-1) {
        //PARTE DE OPTIMIZACION:
        if (sol.puntuacion > sol.mejorPuntuacion) sol.mejorPuntuacion = sol.puntuacion;
    }
    else {
        sol.k++;
        //PARTE DE PODA:
        if (sol.puntuacion + maxPuntosDesde[sol.k] > sol.mejorPuntuacion)
            resolver(sol, canciones, duracion, maxPuntosDesde);
        sol.k--;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, duracion; //n: numero de canciones, duracion: duracion max de cada cara
    cin >> n;
    if (n == 0) return false;
    cin >> duracion;
    vector<Cancion> canciones(n);
    for (int i = 0; i < n; ++i)
        cin >> canciones[i].duracion >> canciones[i].puntos;

    Solucion sol(n);
    
    vector<int> maxPuntosDesde(n);
    maxPuntosDesde[n - 1] = canciones[n-1].puntos;
    for (int i = n - 2; i >= 0; --i) {
        maxPuntosDesde[i] += canciones[i].puntos + maxPuntosDesde[i+1];
    }

    resolver(sol, canciones, duracion, maxPuntosDesde);
    
    cout << sol.mejorPuntuacion << endl;
    return true;
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso());

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}
