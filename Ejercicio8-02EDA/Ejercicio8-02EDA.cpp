// Plantilla para el ejercicio del Consultorio Médico

#include <iomanip>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>
#include <map>
#include <set>
using namespace std;

using Medico = string;
using Paciente = string;
using Fechas = map<int, set<int, int, less<int>>, less<int>>;

class fecha {
private:
    int dia, hora, minuto;
    Fechas fechas;

public:
    fecha(int d, int h, int m) {
        dia = d;
        hora = h; 
        minuto = m;

        //Logaritmico
        fechas[d].insert({ h,m });
    }

    

};

class Consultorio {
private:
    
public:
    void nuevoMedico(Medico m) {

    }

    void pideConsulta(Paciente p, Medico m, fecha f) {

    }

    Paciente siguientePaciente(Medico m) {

    }

    void atiendeConsulta(Medico m) {

    }

    //devuelve la lista de pacientes que tienen cita el dia d
    void listaPacientes(Medico m, fecha f) {

    }
};


int casos = 0;
bool resuelve() {

    int N;
    cin >> N;
    if (!cin) return false;

    string inst; Medico med; Paciente pac; int d, h, m; char c;
    Consultorio con;

    for (int i = 0; i < N; ++i) {
        try {
            cin >> inst;
            if (inst == "nuevoMedico") {
                cin >> med;
                con.nuevoMedico(med);
            }
            else if (inst == "pideConsulta") {
                cin >> pac >> med >> d >> h >> c >> m;
                con.pideConsulta(pac, med, fecha(d, h, m));
            }
            else if (inst == "siguientePaciente") {
                cin >> med;
                pac = con.siguientePaciente(med);
                cout << "Siguiente paciente doctor " << med << '\n';
                cout << pac << '\n';
            }
            else if (inst == "atiendeConsulta") {
                cin >> med;
                con.atiendeConsulta(med);
            }
            else if (inst == "listaPacientes") {
                cin >> med >> d;
                auto vec = con.listaPacientes(med, fecha(d, 0, 0));
                cout << "Doctor " << med << " dia " << d << '\n';
                for (auto p : vec) {
                    cout << p.second << ' ' << p.first << '\n';
                }
            }
            else
                assert(false);
        }
        catch (invalid_argument e) { cout << e.what() << '\n'; }
    }
    cout << "---\n";

    return true;
}

int main() {
    while (resuelve());

    return 0;
}
