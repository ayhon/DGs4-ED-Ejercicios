//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

const string INVALID = "_not_valid_";

bool esDeporte(string const& s){
	return !islower(s[0]);
}

bool resuelveCaso() {
	string input; cin >> input;
	if(!cin) return false;


	unordered_map<string, string> clasif;
	unordered_map<string, int> sol;
	string deporte;
	if(input != "_FIN_") do{
		if(esDeporte(input)) {
			deporte = input;
			sol[deporte] = 0;
		}
		else {
			if(clasif.count(input)){
				if(clasif[input] != deporte) 
					clasif[input] = INVALID;
			}
			else clasif[input] = deporte;
		}
		cin >> input;
	} while(input != "_FIN_");

	for(auto& [nombre, deporte]: clasif){
		if(deporte != INVALID)
			sol[deporte]++;
	}
	vector<pair<int, string>> resultados;
	for(auto& [deporte, num] : sol){
		resultados.push_back({num, deporte});
	}

	sort(resultados.begin(), resultados.end());
	reverse(resultados.begin(), resultados.end());

	for(auto& [num, deporte] : resultados)
		cout << deporte << " " << num << '\n';
	
	cout << "---\n";

	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}

