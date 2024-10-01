//Muxu Rubia Luque
//VJ53

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    for (auto e : v) out << e;
    return out;
}

bool esValida(const vector<int>& sol, int k, vector<int> const& tareas) {
    // Se mira si ese alumno puede seguir haciendo tareas o ya las tiene asignadas
    bool valida = tareas[sol[k]] != 0;

    //Si sí puede seguir haciendo tareas, se mira que no este haciendo la tarea en el segundo puesto de la misma
    if (valida) {
        if (k % 2 != 0) {
            valida = sol[k - 1] != sol[k];
        }
        return valida;
    }

    return false;
}

//Se hace una estimacion del coste maximo de la tarea 
int estimacionOp(vector<int> maximos, int k, int n) {
    int estimacion = 0; 
    for (int i = k; i < n; ++i) {
        estimacion += maximos[i / 2];
    }
    return estimacion;
}

// función que resuelve el problema

//Se devuelve la suma de las puntuaciones de los alumnos que realizaran cada tarea
//Se busca que la suma sea máxima, ya que ello indica que la realizan alumnos que le han dado mayor puntuacion
void resolver(vector<int>& sol, vector<vector<int>> const& preferencias, int numTareas, int alumnos, int k,
    vector<int>& tareas, int valor, int& mejorValor) {

    //Para cada alumno, se recorre la puntuacion asignada a cada tarea
    for (int a = 0; a < alumnos; ++a) {
        sol[k] = a;
        valor += preferencias[a][k / 2];

        if (esValida(sol, k, tareas)) {
            //Este caso se cumple cuando ya no quedan mas tareas por procesar
            if (k == numTareas - 1) {
                if (valor > mejorValor) mejorValor = valor;
            }
            else if (k < numTareas - 1) {
                --tareas[sol[k]];
                int est = estimacionOp(sol, k, numTareas);
                if (est + mejorValor > mejorValor) {
                    resolver(sol, preferencias, numTareas, alumnos, k + 1, tareas, valor, mejorValor);
                }
                ++tareas[sol[k]];
            }
        }

        valor -= preferencias[a][k / 2];
    }


}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    // n: numero de tareas
    // a: numero de alumnos
    // t: max de tareas que puede realizar un alumno
    int n, a, t;
    cin >> n >> a >> t;

    if (n == 0 && a == 0 && t == 0) return false;
    //vector que para cada alumno, contiene un vector con el numero de tareas
    vector<vector<int>> preferencias(a, vector<int>(n));
    //Vector que almacena los maximos
    vector<int> maximos(n * 2, -1);

    for (int i = 0; i < a; ++i)
        for (int j = 0; j < n; ++j) {
            cin >> preferencias[i][j]; //se asigna la puntuacion del alumno i a la tarea j
        }

    //Vector que contendrá a tupla solucion: [a0, a1...] siendo cada elemento el alumno que realiza cada tarea.
    // Como cada tarea se puede realizar hasta 2 veces, las dos primeras componentes son para la primera tarea, 
    // las dos siguientes para la segunda, y asi sucesivamente
    vector<int> sol(n * 2);

    //Vector con el numero de tareas que puede realizar cada alumno. Sirve para llevar un conteo de cuantas tareas
    // esta realizando cada alumno durante la ejecucion. Este vector actua como marcador del numero de tareas 
    // restantes para cada alumno
    vector<int> tareas(a, t);
    int mejorValor = -1;

    resolver(sol, preferencias ,n*2 ,a ,0 , tareas,0, mejorValor);
    // Imprimir solucion
    cout << mejorValor << '\n';
    
    return true;
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
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