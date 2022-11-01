//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

bool resuelveCaso() {
	int n, k; cin >> n >> k;
	if(n == 0 && k == 0) return false;

	queue<int> alumnos;
	for(int i = 1; i <= n; i++)
		alumnos.push(i);

	int sol = 0;
	while(!alumnos.empty()){
		for(int i = 0; i < k; i++){
			alumnos.push(alumnos.front());
			alumnos.pop();
		}
		sol = alumnos.front();
		alumnos.pop();
	}

	cout << sol << '\n';

	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}
