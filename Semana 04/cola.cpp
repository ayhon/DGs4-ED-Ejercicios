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
 * Comienza poniendo el nombre de los que participáis en la solución:
 *
 *  Estudiante 1:
 *  Estudiante 2: Fernando Isaias Leal Sánchez
 *  Estudiante 3: Jaime Jacobo Romo González
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

/* ===================================================
 * Implementad aquí debajo vuestro algoritmo
 * ===================================================
 *@ <answer> */


bool resuelveCaso() {
   // leemos la entrada
   int N, k;
   cin >> N >> k;
   
   if (!cin)
      return false;
   
   vector<int> v(N), out;
   for(auto & e : v ) cin >> e;

    int idMax = 0, usadoMax = 0;
    for(int i = 0; i < k; ++i)
        idMax = (v[idMax] <= v[i]? i : idMax);


    deque<int> d;


/**
5 4 3 1 10 7 8 5 7 X
        **--------
        8 7



*/
    usadoMax = 1;
    for(int i = idMax + 1; i < k; ++i){
        while(!d.empty() && v[d.back()] <= v[i]){
            d.pop_back();
        } // Elemento en lista de candidatos
                
        d.push_back(i);
    }

    for(int i = k; i < N; i++){
        if(i - idMax == k){ // Encontar nuevo máximo
            for(int j = 0; j < usadoMax; ++j){
                out.push_back(v[idMax]);
            }
            idMax = d.front(); 
            d.pop_front();
            usadoMax = 0;
        }

        // Procesar nuevo elemento
        if(v[i] >= v[idMax]){ // Actualizamos nuevo máximo 
            for(int j = 0; j < usadoMax; ++j)
                out.push_back(v[idMax]);
            idMax = i;
            usadoMax = 0;
        }
        else{ // El elemento es menor, y el mayor todavía se puede usar
            while(!d.empty() && v[d.back()] <= v[i]) // Elemento en lista de candidatos
                d.pop_back();
            d.push_back(i);
        }
        usadoMax++;
    }
    for(int j = 0; j < usadoMax; ++j)
        out.push_back(v[idMax]);

    cout << out[0];
    for(int i = 1 ; i < out.size(); i++) 
        cout << " " << out[i];
    cout << '\n';
    return true;
}

/*@ </answer> */

int main() {
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

   while (resuelveCaso());

#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   // Descomentar si se trabaja en Visual Studio
   // system("PAUSE");
#endif
   return 0;
}

