//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

bool noPremio(vector<int> const& h, int i, int j, int k){
	return (i < j && j < k) && (h[j] >= h[k] && h[k] >= h[i]);
}

bool resolver(vector<int> alturas){
	int mayor = -1, mediano = -1; // -1 centinela, pues alturas[i] >= 0
	stack<int> pila; pila.push(alturas.back()); // Así, pila empieza no siendo vacía

	for(int i = alturas.size()-2; i >= 0; --i){
		if(alturas[i] <= mediano) return false; // No hay premio
	
		if(!pila.empty() && pila.top() <= alturas[i]){  // No debería ser necesario el pila.empty()
			mayor = alturas[i];
			do{
				mediano = pila.top();
				pila.pop();
			}while(!pila.empty() && pila.top() <= mayor);
			pila.push(mayor); // Así, nos aseguramos de que pila no está vacía
		}
		else { // pila.top() > alturas[i] o la pila está vacía
			pila.push(alturas[i]); // Así nos aeguramos de que pila no está vacía
		}
	}
	return true; // No hay trio sin premio
}

bool resuelveCaso() {
	int n; cin >> n;
	if(!cin) return false;

	vector<int> alturas(n); // Hasta 1e9, cabe en entero
	for(auto & e : alturas) cin >> e;

	bool sol = resolver(alturas);

	cout << (sol? "SIEMPRE PREMIO" : "ELEGIR OTRA") << '\n';

	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}

