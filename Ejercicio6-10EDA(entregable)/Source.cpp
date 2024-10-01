//Muxu Rubia Luque VJ53

#include <iostream>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

struct Rio{
    int caudal;
    int numTramos;
};

//Coste O(V) siendo V los vertices del arbol, que se recorren solo 1 vez
Rio resolver(bintree<int> const& arb) {
    Rio r;
    //Arbol vacio
    if (arb.empty()) {
        r.caudal = 0;
        r.numTramos = 0;
    }
    //Arbol sin hijos (solo raiz) -> un manantial
    else if (arb.right().empty() && arb.left().empty()) {
      
        r.caudal = 1;
        r.numTramos = 0;
    }
    //Arbol con hijos -> cruze de afluentes o presa
    else { 
        Rio ri = resolver(arb.left());
        Rio rd = resolver(arb.right());
        
        //Para asegurarnos de que no haya un numero negativo en r.caudal usamos std::max con el numero 0
        r.caudal = std::max(rd.caudal + ri.caudal - arb.root(), 0);
        r.numTramos = rd.numTramos + ri.numTramos;
        if (r.caudal >= 3) r.numTramos++;
    }
    return r;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    bintree<int> arb;
    arb = leerArbol(-1); // -1 es la repr. de arbol vacio
    
    //Se hacen las operaciones solo en los hijos de la raiz original del arbol
    //para que no se sumen entre sí los caudales que llegan a la raiz, ya que lo que haya
    //despues de la misma no nos interesa
    cout << resolver(arb.left()).numTramos + resolver(arb.right()).numTramos << endl;
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
    //system("PAUSE");
#endif

    return 0;
}

