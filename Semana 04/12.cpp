//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

void resolver(queue<int> & cola){
	// Puedo usar una cola y una pila o una cola doble
	// Elijo usar la cola doble
	deque<int> d;
	while(!cola.empty()){
		int aux = cola.front();
		if(aux >= 0){ // Número es positivo
			d.push_front(aux);
		}
		else{ // Número es negativo
			d.push_back(aux);
		}
		cola.pop();
	}
	while(!d.empty()){
		cola.push(d.back());
		d.pop_back();
	}
}

bool resuelveCaso() {
	int n; cin >> n;
	if(n == 0) return false;
	
	queue<int> cola;
	for(int i = 0; i < n; ++i){
		int aux; cin >> aux;
		cola.push(aux);
	}

	resolver(cola);

	cout << cola.front(); cola.pop();
	for(int i = 1; i < n; ++i){
		cout << " " << cola.front(); cola.pop();
	}
	cout << '\n';

	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}

