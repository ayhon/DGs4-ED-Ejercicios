//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

/*

Toda diagonal descendente tiene componentes iguales

[
	[1, 2, 3],
	[4, 5, 6],
	[7, 8, 9]
]

*/
bool es_toeplitz(const list<list<int>> & mat){
	// No está permitida la copia de los elementos a una estructura
	// auxiliar. No se dice nada de que no se pueda usar una 
	// estructura auxiliar en la resolución del problema.
	
	int n = mat.size(),
		m = mat.begin()->size();
	vector<int> cols;

	for(auto rit = mat.rbegin(); rit != mat.rend(); ++rit){
		cols.push_back(*rit->begin()); // Añadimos los elem de la primera col
	}
	cols.pop_back(); // Quitamos el elem en (0,0)
	for(int elem : *mat.begin()){
		cols.push_back(elem); // Añadimos los elem de la primera fila
	}
	// assert((int)cols.size() == n+m-1);

	auto it1 = ++mat.begin();
	for(int i = 1; i < n; ++i){
		auto it2 = ++it1->begin();
		for(int j = 1; j < m; ++j){
			if(*it2 != cols[n-i+j-1]) return false;
			it2++;
		}
		it1++;
	}
	return true;
}

bool resuelveCaso() {
	int aux; cin >> aux;
	if(aux == 0) return false;

	list<list<int>> mat;
	do{
		list<int> act;
		do{
			act.push_back(aux);
			cin >> aux;
		} while(aux != 0);
		mat.push_back(act);
		cin >> aux;
	} while (aux != 0);
	
	cout << (es_toeplitz(mat)? "SI" : "NO" ) << '\n';

	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}

