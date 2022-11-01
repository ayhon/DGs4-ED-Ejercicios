//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

const string INVALID = "DeporteNoValido__";
bool esDeporte(string const& s){ return !islower(s[0]); }

bool resuelveCaso() {
	string input; cin >> input;
	if(!cin) return false;

	string deporte;
	unordered_map<string, string> clasif;
	unordered_map<string, int> conteo;
	if(input != "_FIN_") do{
		if(esDeporte(input)) {
			deporte = input;
			conteo[deporte] = 0;
		}
		else { // Es un nombre
			if(clasif.count(input)){
				if(clasif[input] != deporte) 
					clasif[input] = INVALID;
			}
			else clasif[input] = deporte;
		}
		cin >> input;
	} while(input != "_FIN_");

	for(auto const& [nombre,deporte] : clasif)
		if(deporte != INVALID) conteo[deporte]++;

	vector<pair<int, string>> resultados;
	for(auto const& [deporte, num] : conteo)
		resultados.push_back({num, deporte});

	sort(resultados.begin(), resultados.end(), [](pair<int, string> const& p1, pair<int, string> const& p2){
		return p1.first > p2.first || (p1.first == p2.first && p1.second < p2.second);
	});

	for(auto& [num, deporte] : resultados)
		cout << deporte << " " << num << '\n';
	
	cout << "---\n";

	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}

