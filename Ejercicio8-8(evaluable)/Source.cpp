//Muxu Rubia Luque
//VJ53
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

struct datos {
    int nCompromisarios = 0;
    unordered_map<string, int> partidosE;
    string masVotado = "";
};

using Estado = unordered_map<string, datos>;
using Partido = map<string, int, less<string>>;
//Complejidad total es O(N + logN) siendo N el numero de partidos que han tenido votos y que se almacenan en el 
// map ordenado partidos
class ConteoVotos {

private:
    Estado estados;
    Partido partidos;
public:
    //Complejidad constante porque insertar un elemento en un unordered map tiene dicha complejidad
    void nuevo_estado(const string& nombre, int num_compromisarios) {
        if (estados.find(nombre) != estados.end()) {
            throw domain_error("Estado ya existente");
        }
        datos d;
        d.nCompromisarios = num_compromisarios;
        d.masVotado = "";

        estados.insert({ nombre, d });
    }

    //Complejidad logarítmica porque se hace un acceso a un map ordenado para insertar un nuevo elemento
    //Complejidad O(log N) siendo N el numero de elementos que tiene dicho map ordenado, que es partidos
    void sumar_votos(const string& estado, const string& partido, int num_votos) {
        if (estados.find(estado) == estados.end()) {
            throw domain_error("Estado no encontrado");
        }
        estados[estado].partidosE[partido] += num_votos;
        if (estados[estado].masVotado == "") {
            estados[estado].masVotado = partido;
            partidos[partido] += estados[estado].nCompromisarios;
        }
        else {
            string& masVotado = estados[estado].masVotado;
            //Se actualiza el partido mas votado si ya habia uno antes
            if (estados[estado].partidosE[partido] > estados[estado].partidosE[masVotado]) {

                partidos[partido] += estados[estado].nCompromisarios;
                partidos[masVotado] -= estados[estado].nCompromisarios;
                if (partidos[masVotado] <= 0) partidos.erase(masVotado);

                masVotado = partido;
            }

        }
        
    }

    //Complejidad constante porque los accesos al map estados son constantes al ser un unordered map
    string ganador_en(const string& estado) const {
        auto it = estados.find(estado);
        if (it == estados.end()) {
            throw domain_error("Estado no encontrado");
        }
        return it->second.masVotado;
    }

    //Complejidad lineal O(N), siendo N el numero total de partidos con compromisarios
    vector<pair<string, int>> resultados() const {
        vector<pair<string, int>> resultado;
        for (auto partido : partidos) {
            resultado.push_back(partido);
        }
        return resultado;
    }

};


bool resuelveCaso() {
    string comando;
    cin >> comando;
    if (!cin) return false;

    ConteoVotos elecciones;

    while (comando != "FIN") {
        try {
            if (comando == "nuevo_estado") {
                string estado;
                int num_compromisarios;
                cin >> estado >> num_compromisarios;
                elecciones.nuevo_estado(estado, num_compromisarios);
            }
            else if (comando == "sumar_votos") {
                string estado;
                string partido;
                int num_votos;
                cin >> estado >> partido >> num_votos;
                elecciones.sumar_votos(estado, partido, num_votos);
            }
            else if (comando == "ganador_en") {
                string estado;
                cin >> estado;
                string ganador = elecciones.ganador_en(estado);
                cout << "Ganador en " << estado << ": " << ganador << "\n";
            }
            else if (comando == "resultados") {
                for (const auto& par : elecciones.resultados()) {
                    cout << par.first << " " << par.second << "\n";
                }
            }
        }
        catch (std::exception& e) {
            cout << e.what() << "\n";
        }
        cin >> comando;
    }

    cout << "---\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
