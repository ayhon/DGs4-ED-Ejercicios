//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

struct Accidente{
	string fecha = "";
	int num = -1;
	bool operator<(Accidente that){
		return this->num < that.num;
	}
	bool operator<=(Accidente that){
		return this->num <= that.num;
	}
};

bool resuelveCaso() {
	int N; cin >> N; // N \in [1, 2.5e5]
	if(!cin) return false;
	
	vector<Accidente> v(N);
	for(auto & e : v) cin >> e.fecha >> e.num;

	stack<Accidente> pila;
	for(auto & acc : v){
		while(!pila.empty() && pila.top() <= acc)
			pila.pop();

		cout << (!pila.empty()? pila.top().fecha : "NO HAY") << '\n';

		pila.push(acc);
	}
	cout << "---\n";
	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}

