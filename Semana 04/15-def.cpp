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
 *  Estudiante 1: Jaime Jacobo Romo González
 *  Estudiante 2: Jinqing Cai
 *  Estudiante 3: Fernando Isaías Leal Sánchez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;

/* ===================================================
 * Implementad aquí debajo vuestro algoritmo
 * ===================================================
 *@ <answer> */
using namespace std;

bool resuelveCasoN2() {
    int n, k, aux; cin >> n >> k;
    if (!cin) return false;

    vector<int> v;

    for (int i = 0; i < n; ++i) {
        cin >> aux;
       
        v.push_back(aux);

        if (i + 1 >= k) {
            int Max = aux;

            for (int j = i - 1; i - j < k; --j) {
                Max = max(Max, v[j]);
            }

            if (i != k - 1) {
                cout << ' ';
            }
            
            cout << Max;
        }
    }

    cout << "\n";

    return true;
}

bool resuelveCaso() {
	int n, k, aux;
	cin >> n >> k;
	if (!cin) return false;

	queue <int> q;
	deque <int> dq;

	// Guardamos en una cola los datos a procesar y en una doble cola los posibles máximos que puede tener nuestro
	// segmento actual. La doble cola siempre tendrá elementos en orden decreciente, luego en caso de tener que actualizar
	// el máximo, será el principio de esta.
	int maxi = 0,
		num,
		i;

	for (i = 0; i < k; ++i) {
		/// Guardamos los k primeros datos, que generan el primer output
		cin >> num;

		/// Guadar el maximo de esta primera cadena de k elementos
		maxi = max(maxi, num);

		/// Dejar en la cola solamente los posibles maximos, ordenados de manera creciente desde atras hacia delante
		while (!dq.empty() && num > dq.back()) {
			/// Quitamos los elementos que son menores que el elemento actual, que no va a ser posible maximo
			/// Porque el elemento actual ya es mayor, entonces no desempeñan ninguna función en futuro
			dq.pop_back();
		}

		/// Añadir el elemento actual como un posible máximo en futuro
		dq.push_back(num);

		/// Añadir elemento a la cola
		q.push(num);
	}

	/// Imprimir el primer máximo
	cout << maxi;

	while (i < n) {
		cin >> num;

		/// Es el elemento a a quitar ahora
		aux = q.front();
		q.pop();

		/// Trabajamos siempre con un segmento de k elementos
		q.push(num);

		maxi = max(maxi, num); /// Actualizamos el máximo actual

		while (!dq.empty() && num > dq.back()) {
			dq.pop_back();  
            /// Actualizamos la cola
			/// Quitamos solamente aquellos que son menor estrictamente que elemento actual, 
			///		permitiendo el caso de multiple maximo iguales
		}

		/// Posible maximo para mas adelante
		dq.push_back(num);

		if (maxi == aux) { /// Si el máximo actual ya no pertenece a nuestro segmento actualizamos
			dq.pop_front();

			/// Si no hay mas posibles maximos, marcar como maximo el elemento actual
			/// Y si no, seria el siguiente elemento de la cola, porque está ordenado de mayor a menor de izquierda a derecha
			if (dq.empty()) maxi = num;
			else maxi = dq.front();
		}

		cout << ' ' << maxi;
		++i;
	}

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
