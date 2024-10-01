
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

/*
Tupla solucion: [G0, G1, ..., Gn-1] donde Gi es el grupo que va a actuar en la posicion i-esima

La matriz:
0 1 1
0 0 1
0 0 0

significa los consentimientos de tocar inmediatamente despues que los otros grupos siendo que el grupo 0 acepta tocar
despues del 1 y el 2, el grupo 1 solamente depsues del 2 y el grupo 3 no acepta tocar tras ningun otro grupo.
La diagonal corresponde con cada grupo consigo mismo, por lo que es 0 porque no tiene sentido el consentimiento de tocar
tras sí mismo.

Se pide encontrar la solucion que maximice los beneficios, no todas las posibles soluciones que haya. Dichos beneficios vienen
dados por la matriz: (esta expresada de forma que cada grupo corresponde a una columna, en los casos de prueba son filas y está 
implementado de dicha manera)

160 10 20
10 20 30
140 20 10

El grupo 0 da de beneficio 10 si actua el primero, 20 si actua el segundo y 30 si actua el tercero -> Cada fila representa
el beneficio que aporta cada grupo según la posicion en la que toquen.

No hay vetos, es decir, todos los grupos aceptan tocar detras de cualquier otro.
*/

bool esValida(const vector<int>& soluc, int k, const vector<bool>& elegidos, const vector<vector<bool>>& consentimientos) {
    //Se mira si se cumplen los requisitos de los grupos
    return (!elegidos[soluc[k]] && (k == 0 || consentimientos[soluc[k]][soluc[k - 1]]));
}

// función que resuelve el problema
void resolver(vector<int>& soluc, int k, int n, int ingresos, int &mejoresIngresos, vector<bool>& elegidos, 
    const vector<vector<int>>& beneficios, const vector<vector<bool>>& consentimientos, const vector<int>& mejoresBeneficios, 
    const vector<int>& mejoresBeneficiosDesde) {

    //Recorrido sobre los artistas y combinaciones entre ellos
    for (int i = 0; i < n; ++i) {
        soluc[k] = i; //Se pone el valor del grupo actual en la solucion en la posicion que le corresponde para comprobar si es valida
        //Se pregunta si es valida o no dicha solucion
        if (esValida(soluc, k, elegidos, consentimientos)) {
            //Se acatualizan los beneficios acumulados hasta el momento usando la matriz que nos dan como entrada
            //Beneficio que aporta el grupo i al tocar tras k
            ingresos += beneficios[i][k]; 
            //Se marca el grupo i como que ya ha sido elegido y por tanto no puede volverse a elegir
            elegidos[i] = true; 

            //Comprobacion que se hace cuando se está al final del arbol
            if (k == n - 1) {
                //PARTE DE OPTIMIZACION:
                //Se actualizan los ingresos maximos (o beneficios maximos) si se ha conseguido una mejoria con respecto
                // a un valor anterior
                if (ingresos > mejoresIngresos) mejoresIngresos = ingresos;
            }
            else {
                //PARTE DE PODA:
                //Donde estaría un metodo de optimacion optimiesta, tenemos en su lugar el vector de mejoresBeneficiosDesde
                if (ingresos + mejoresBeneficiosDesde[k+1] > mejoresIngresos) {
                    resolver(soluc, k + 1, n, ingresos, mejoresIngresos, elegidos, beneficios, consentimientos, mejoresBeneficios, mejoresBeneficiosDesde);
                }
            }
            ingresos -= beneficios[i][k]; //Se restan los beneficios porque se pasa a otra rama y se debe volver a empezar
            elegidos[i] = false; //Se desmarca como elegido porque se va a dar otra vuelta
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n; //num artistas
    cin >> n;
    vector<vector<int>> beneficios(n, vector<int>(n));
    vector<vector<bool>> consentimientos(n, vector<bool>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> beneficios[i][j];

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            int b;
            cin >> b;
            consentimientos[i][j] = b;
        }

    //Vector con el maximo beneficio que se obtiene de cada columna de la matriz de beneficios
    vector<int> mejoresBeneficios(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (beneficios[j][i] > mejoresBeneficios[i]) mejoresBeneficios[i] = beneficios[j][i];
        }
    }

    //Suma de los beneficios desde una determinada posicion
    //Se usa como marcador para la poda
    vector<int> mejoresBeneficiosDesde(n);
    mejoresBeneficiosDesde[n - 1] = mejoresBeneficios[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        mejoresBeneficiosDesde[i] += mejoresBeneficiosDesde[i + 1] + mejoresBeneficios[i];
    }

    vector<int> soluc(n); //Tupla solucion
    int k = 0;
    int ingresos = 0;
    int mejoresIngresos = -1;
    vector<bool> elegidos(n); //tabla con numero fijo de artistas, cada pos del array es un artista
    resolver(soluc, k,n,ingresos, mejoresIngresos, elegidos, beneficios, consentimientos, mejoresBeneficios, mejoresBeneficiosDesde);
    if (mejoresIngresos == -1) cout << "NEGOCIA CON LOS ARTISTAS\n";
    else cout << mejoresIngresos << endl;
}

//#define DOMJUDGE
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
    //system("PAUSE");
#endif

    return 0;
}
