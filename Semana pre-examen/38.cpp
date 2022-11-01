//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

class carnet_puntos{
public:
	carnet_puntos(){
		con_puntos.resize(16,0);
	}
	void nuevo(string const& dni){
		if(data.count(dni)) throw domain_error("Conductor duplicado");
		data[dni] = 15;
		con_puntos[15]++;
	}
	void quitar(string const& dni, int ptos){
		if(!data.count(dni)) throw domain_error("Conductor inexistente");

		int old_pts = data[dni];
		int new_pt = max(old_pts - ptos, 0);

		data[dni] = new_pt;

		con_puntos[old_pts]--;
		con_puntos[new_pt]++;
	}
	int consultar(string const& dni) const {
		if(!data.count(dni)) throw domain_error("Conductor inexistente");

		return data.at(dni);
	}
	int cuantos_con_puntos(int puntos) const {
		if(puntos > 15 || puntos < 0) throw domain_error("Puntos no validos");
		return con_puntos[puntos];
	}

private:
	// Conductores -> puntos
	unordered_map<string, int> data;
	
	// puntos -> conductores
	vector<int> con_puntos;
};

bool resuelveCaso() {
	string command; cin >> command;
	if(!cin) return false;

	carnet_puntos c;
	string dni;
	int puntos, sol;
	while(command != "FIN"){
		try {
			if(command == "nuevo"){
				cin >> dni;
				c.nuevo(dni);
			} else if (command == "quitar"){
				cin >> dni >> puntos;
				c.quitar(dni,puntos);
			} else if (command == "consultar"){
				cin >> dni;
				sol = c.consultar(dni);
				cout << "Puntos de " << dni << ": " << sol << '\n';
			} else if (command == "cuantos_con_puntos"){
				cin >> puntos;
				sol = c.cuantos_con_puntos(puntos);
				cout << "Con " << puntos << " puntos hay " << sol << '\n';
			}
		}
		catch(domain_error & e){
			cout << "ERROR: " << e.what() << '\n';
		}

		cin >> command;
	}
	cout << "---\n";
	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}

