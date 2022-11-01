//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

class ConteoVotos{
public:
	void nuevo_estado(string const& nombre, int num_compromisarios){
		checkIsNew(nombre);
		info[nombre] = {num_compromisarios};
	}
	void sumar_votos(string const& estado, string const& partido, int num_votos){
		checkExists(estado);

		InfoEstado& info_est = info[estado]; // O(1)
		int & votos = info_est.votos[partido]; // O(1)
		
		votos += num_votos;
		if(votos > info_est.votos_ganador){
			if(info_est.votos_ganador != -1){
				auto it = resultado.find(info_est.ganador);
				it->second -= info_est.num_compromisarios;
				if(it->second == 0) resultado.erase(it);
			}
			info_est.ganador = partido;
			info_est.votos_ganador = votos;
			resultado[partido] += info_est.num_compromisarios;
		}
	}
	string ganador_en(string const& estado) const {
		checkExists(estado);
		return info.at(estado).ganador;
	}
	vector<pair<string, int>> resultados() const {
		vector<pair<string,int>> res;
		for(auto & p : resultado)
			res.push_back(p);
		return res;
	}
private:
	struct InfoEstado{
		int num_compromisarios = 0;
		unordered_map<string, int> votos;
		string ganador;
		int votos_ganador = -1;
	};
	map<string, int> resultado;
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

