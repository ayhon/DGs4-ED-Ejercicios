/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

/*
 * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
 * modificar el código contenido entre las etiquetas <answer>
 * y </answer>. Toda modificación fuera de esas etiquetas está
 * prohibida, pues no será corregida.
 *
 * Tampoco esta permitido modificar las líneas que contienen
 * las etiquetas <answer> y </answer>, obviamente :-)
 */

/*@ <answer>
 * Comienza poniendo el nombre de los componentes del grupo:
 *
 *  Estudiante 1: Fernando Isaías Leal Sánchez
 *  Estudiante 2: CaJinqing Cai
 *  Estudiante 3: Mattéo Galfré
 *  Estudiante 4: Jaime Romo González
 *@ </answer> */

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
using namespace std;

/*@ <answer> */
//hola mateo :D
class Hora {
private:
    long long seg = 0;

public:

    Hora() {}
    Hora(int s) : seg(s) {}

    void print (ostream & salida) const {
        salida << setfill('0') << setw(2) << seg / 3600 << ':' << setw(2) << seg % 3600 / 60 << ':' << setw(2) << seg % 60;
	}

    void read(istream & entrada) {
        int hora, min;
        char aux;
        entrada >> hora >> aux >> min >> aux >> seg;
        seg += hora * 3600 + min * 60;
	}

    int getSeg() const { return this->seg; } 

    bool operator<(const Hora & h1) const {
        return this->seg < h1.getSeg();
    }
};

inline ostream & operator<<(ostream & salida, Hora const& h) {
     h.print(salida);
     return salida;
}

inline istream & operator>>(istream & entrada, Hora & h) {
    h.read(entrada);
    return entrada;
}


// devuelve la posición del primer valor no menor que h
// o v.size() si todos son menores
int buscarHora(vector<Hora> const& v, Hora const& h) {
    auto it = lower_bound(v.begin(), v.end(), h);

    return (it == v.end() ? -1 : it - v.begin());
}

bool resuelveCaso() {
  
    int nHoras, nConsultas;
    cin >> nHoras >> nConsultas;
  
    if (nHoras == 0 && nConsultas == 0)
        return false;
  
      // crea el vector con el horario y le da valor
    vector<Hora> trenes(nHoras);
    for (int i = 0; i < nHoras; ++i) {
        cin >> trenes[i];
    }
  
    Hora h;
    for (int i = 0; i < nConsultas; ++i) {
        cin >> h;
        int pos = buscarHora(trenes, h);
        if (pos != -1) cout << trenes[pos] << "\n";
        else  cout << "NO\n";
    }
  
    cout << "---\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("caso.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Comentar si no se trabaja en Visual Studio
    system("PAUSE");
#endif

    return 0;
}
