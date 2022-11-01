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
   *  Estudiante 1:
   *  Estudiante 2:
   *@ </answer> */

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <assert.h>
using namespace std;

/*@ <answer> */
class Hora {
private:
    int seg = 0;

public:
    Hora(int s = 0) : seg(s) {
        /// Que no sea superior a un dia
        assert(s < 24 * 60 * 60);
    }

    void print(ostream& salida) const {
        salida << setfill('0') << setw(2) << seg / 3600 << ':' << setw(2) << seg % 3600 / 60 << ':' << setw(2) << seg % 60;
    }

    void read(istream& entrada) {
        int hora, min;
        char aux;
        entrada >> hora >> aux >> min >> aux >> seg;
        seg += hora * 3600 + min * 60;
    }

    int getSeg() const { return this->seg; }

    bool operator<(const Hora& h1) const {
        return this->seg < h1.getSeg();
    }

    bool operator==(const Hora& h1) const {
        return this->seg == h1.getSeg();
    }

    Hora operator+(const Hora& h1) const {
        return Hora(seg + h1.getSeg());
    }
};

inline std::ostream& operator<<(std::ostream& salida, Hora const& h) {
    h.print(salida);
    return salida;
}

inline std::istream& operator>>(std::istream& entrada, Hora& h) {
    h.read(entrada);
    return entrada;
}

// clase con los datos de una película
class Pelicula {
public:
    Pelicula(){}
    Pelicula(string _titulo, Hora _inicio, Hora _duracion) :
        titulo(_titulo), inicio(_inicio), duracion(_duracion) {}

    Hora getFin() const{ return inicio + duracion; }
    string getTitulo() const{ return titulo; }

    bool operator<(Pelicula const& p){
        if (this->getFin() == p.getFin()) 
            return this->titulo < p.getTitulo();
        return this->getFin() < p.getFin();
    }

    void print(ostream & salida) const {
        salida << this->getFin() << " " << titulo;
    }

private:
    Hora inicio, duracion;
    string titulo;
};

inline ostream& operator<<(ostream& salida, Pelicula const& p) {
    p.print(salida);
    return salida;
}

istream& operator>>(istream& entrada, Pelicula& p) {
    string titulo;
    Hora inicio, duracion;
    entrada >> inicio >> duracion;
    entrada.ignore(1); // saltar el blanco
    getline(entrada, titulo); // el título puede tener blancos, no leerlo con >>
    p = Pelicula(titulo, inicio, duracion);
    return entrada;
}

bool resuelveCaso() {
    int numPeliculas;
    cin >> numPeliculas;

    if (numPeliculas == 0)
        return false;

    vector<Pelicula> pelis(numPeliculas);
    for (auto& p : pelis) {
        cin >> p;
    }

    // simplemente hay que ordenar
    sort(pelis.begin(), pelis.end());

    for (auto const& p : pelis) {
        cout << p << '\n';
    }
    cout << "---\n";
    return true;
}

/*@ </answer> */

int main() {

#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
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