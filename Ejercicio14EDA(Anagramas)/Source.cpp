// Muxu Rubia Luque
// VJ53


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;
void merge(string& pal, int ini, int fin, int mid) {
    int n1 = mid - ini;
    int n2 = fin - mid;

    vector<char> v1;
    vector<char> v2;

    for (int i = 0; i < n1; ++i)
        v1.push_back(pal[ini + i]);

    for (int j = 0; j < n2; ++j)
        v2.push_back(pal[mid + j]);

    int i = 0, j = 0;
    for (int k = ini; k < fin; ++k) {
        //si se ha agotado v2 o queda v1 siendo su elemento mas pequeño o igual al de v2
        if (j >= n2 || (i < n1 && v1[i] <= v2[j])) {
            pal[k] = v1[i];
            ++i;
        }
        else {
            pal[k] = v2[j];
            ++j;
        }
    }

}

void mergesort(string& pal, int ini, int fin) {
    //mergesort con complejidad n*log n --> O(n*logn)
    int mid;
    int n = fin - ini;
    if (n>1) {
        mid = (ini + fin) / 2;
        mergesort(pal, ini, mid);
        mergesort(pal, mid, fin);
        merge(pal, ini, fin, mid);
    }

}

//El coste final es de O(n*log n)
// funcio?n que resuelve el problema
bool resolver(string pal1, string pal2) {
    if (pal1.size() != pal2.size()) return false;

    mergesort(pal1, 0, pal1.size());
    mergesort(pal2, 0, pal2.size());

    int i = 0;
    while (i < pal1.size()) {
        if (pal1[i] != pal2[i]) return false;
        i++;
    }

    return true;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuracio?n, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    string pal1;
    string pal2;
    cin >> pal1;
    cin >> pal2;
    bool sol = resolver(pal1, pal2);
    // escribir sol
    if (sol) cout << "SI" << endl;
    else cout << "NO" << endl;

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
    system("PAUSE");
#endif

    return 0;
}