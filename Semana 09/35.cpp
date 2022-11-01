//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

void resuelveCaso() {
	int m, curr; cin >> m;

	int res = 0, last = 0; // 1 2 3 3 2 1 
	unordered_map<int, int> cont;

	for(int j = 0; j < m; ++j){
		cin >> curr;
		if(cont.count(curr))
			last = max(last, cont[curr] + 1);
		cont[curr] = j;
		res = max(res, j - last + 1);
	}
	cout << res << '\n';
}

int main() {
	int t; cin >> t;
	while(t--){
		resuelveCaso();
	}
	return 0;
}

