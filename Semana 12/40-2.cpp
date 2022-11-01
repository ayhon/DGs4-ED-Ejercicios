//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

class ConteoVotos{
public:
	void nuevo_estado(string const& nombre, int num_compromisarios){
		checkIsNew(nombre);
		compr[nombre] = num_compromisarios;
	}
	void sumar_votos(string const& estado, string const& partido, int num_votos){
		checkExists(estado);
		votos[estado][partido] += num_votos;
	}
	string ganador_en(string const& estado) const {
		checkExists(estado);
		string res; int maxi = 0;
		for(auto & [partido, punt] : votos.at(estado)){
			if(punt > maxi){
				maxi = punt;
				res = partido;
			}
		}
		return res;

	}
	vector<pair<string, int>> resultados() const {
		vector<pair<string,int>> res;
		map<string, int> conteo;
		for(auto & [estado, n_compr] : compr)
			conteo[ganador_en(estado)] += n_compr;
		for(auto & p : conteo)
			res.push_back(p);
		return res;
	}
private:
	/* struct InfoEstado{ */
	/* }; */
	unordered_map<string, int> compr;
	unordered_map<string, map<string, int>> votos;

	void checkExists(string const& nombre) const{
		if(!compr.count(nombre)) throw domain_error("Estado no encontrado");
	}
	void checkIsNew(string const& nombre) const{
		if(compr.count(nombre)) throw domain_error("Estado ya existente");
	}
};

void resuelveCaso() {

}

int main() {
	int T; cin >> T;
	for(int caso = 1; caso <= T; caso++) {
		// cout << "Case #" << caso <<":\n";
		resuelveCaso();
	}
	return 0;
}

