//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

bool resuelveCaso() { // Coste O(max(n,m))
	int n; cin >> n; // 1e5
	if (!cin) return false;

	unordered_map<string, vector<int>> cuentas;
	for(int i = 0; i < n; ++i){ // O(n)
		string juego; cin >> juego;
		cuentas[juego].push_back(i+1); // O(1), pues unordered
	}

	int m; cin >> m; // 1e5
	for(int i = 0; i < m; i++){ // O(m)
		int k;
		string juego;
		cin >> k >> juego;

		vector<int> & cuenta = cuentas[juego]; // O(1) pues unordered
		cout << (k <= (int)cuenta.size()? to_string(cuenta[k-1]) : "NO JUEGA") << '\n';
	}
	cout << "---\n";
	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}

