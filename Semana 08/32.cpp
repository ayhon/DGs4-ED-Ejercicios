//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

bool resuelveCaso() {
	int n; cin >> n;
	if(n == 0) return false;

	map<string, int> notas;
	vector<string> nombres;
	for(int i = 0; i < n; ++i){
		string key, aux;
		getline(cin, key);
		getline(cin, key);
		cin >> aux;

		if(notas.find(key) == notas.end())
			nombres.push_back(key);

		int value = (aux == "CORRECTO"? 1 : -1);
		notas[key] += value;
	}

	sort(nombres.begin(), nombres.end());
	for(string const& nombre : nombres)
		if(notas[nombre] != 0) cout << nombre << ", " << notas[nombre] << '\n';

	cout << "---\n";
	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}

