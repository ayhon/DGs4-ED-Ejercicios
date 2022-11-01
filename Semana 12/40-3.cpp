//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

class ConteoVotos{
public:
	void nuevo_estado(string const& nombre, int num_compromisarios){
		checkIsNew(nombre);
		info[nombre] = {num_compromisarios,{}}; // O(1)
	}
	void sumar_votos(string const& estado, string const& partido, int num_votos){
		checkExists(estado);
		info[estado].votos[partido] += num_votos; // O(1) + 
	}
	string ganador_en(string const& estado) const {
		checkExists(estado);
		string res; int maxi = 0;
		for(auto & [partido, punt] : info.at(estado).votos){ // O(partidos)
			if(punt > maxi){
				maxi = punt;
				res = partido;
			}
		}
		return res;
	}
	vector<pair<string, int>> resultados() const { // O(estados x partidos)
		vector<pair<string,int>> res;
		map<string, int> conteo;
		for(auto & [estado, info_est] : info) // O(estados x partidos)
			conteo[ganador_en(estado)] += info_est.num_compromisarios; // O(partidos)
		for(auto & p : conteo)
			res.push_back(p);
		return res;
	}
private:
	struct InfoEstado{
		int num_compromisarios;
		map<string, int> votos;
	};
	unordered_map<string, InfoEstado> info;

	void checkExists(string const& nombre) const{
		if(!info.count(nombre)) throw domain_error("Estado no encontrado");
	}
	void checkIsNew(string const& nombre) const{
		if(info.count(nombre)) throw domain_error("Estado ya existente");
	}
};

bool resuelveCaso() {
	string op; cin >> op;
	if(!cin) return false;
	ConteoVotos c;

	while(op != "FIN"){
		try{
			if(op == "nuevo_estado"){
				string estado; int compr;
				cin >> estado >> compr;
				c.nuevo_estado(estado, compr);
			}
			else if (op == "sumar_votos"){
				string estado, partido; int votos;
				cin >> estado >> partido >> votos;
				c.sumar_votos(estado,partido,votos);
			}
			else if (op == "ganador_en"){
				string estado; cin >> estado;
				string ganador = c.ganador_en(estado);
				cout << "Ganador en " << estado << ": " << ganador << '\n';;
			}
			else if (op == "resultados"){
				for(auto & [estado, compr] : c.resultados()){
					cout << estado << " " << compr << '\n';
				}
			}
		}
		catch(domain_error& e){
			cout << e.what() << '\n';
		}
		cin >> op;
	}

	cout << "---\n";
	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}

