//Muxu Rubia Luque VJ53

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

//Tiene un coste logaritmico O(log n) siendo n el numero de elementos del vector porque no lo recorre entero, 
// sino que lo divide en subvectores dividiendo por la mitad cada vez 
// función que resuelve el problema
int resolver(vector<int> v, int ini, int fin) {
    
    int a = fin - ini;
    if (a < 2) return ini; //vector de 1 elemento
    else {

        int mid = (ini + fin) / 2; //al ser fin impar, siempre va a dar el del medio al truncarse la division

        //caso base
        if (v[mid]<v[mid + 1] && v[mid]>v[mid - 1])
            return mid;

        //casos mitad par
        if (mid % 2 == 0 && v[mid]<v[mid+1])
            return resolver(v, ini, mid);
        
        else if(mid%2 ==0 && v[mid]==v[mid+1])
            return resolver(v, mid, fin);

        //casos mitad impar
        if(mid%2 != 0 && v[mid] == v[mid + 1])
           return resolver(v, ini, mid-1);

        else if(mid%2 !=0 && v[mid] == v[mid-1])
            return resolver(v, mid+1, fin);

    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    vector<int> v(n);
    for (int& e : v) cin >> e;

    // Llamada a la función resolver
    int sol = resolver(v, 0, n);

    // Mostrar el resultado
    cout << sol << endl;
}


#define DOMJUDGE
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