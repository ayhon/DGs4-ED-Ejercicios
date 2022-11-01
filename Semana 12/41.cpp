//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

class carnet_puntos{
public:
	carnet_puntos() : con_puntos(MAX_PTOS+1){}
	void nuevo(string dni){ // O(1)
		checkDniNew(dni);

		add(dni, MAX_PTOS);
	}
	void quitar(string dni, int puntos){ // O(1)
		info_conductor info = checkDniExists(dni);
		if(puntos == 0) return;

		con_puntos[info.puntos].erase(info.pos); // O(1)
		add(dni, max(0, info.puntos - puntos));
	}
	void recuperar(string dni, int puntos){ // O(1)
		info_conductor info = checkDniExists(dni);
		if(puntos == 0) return;

		con_puntos[info.puntos].erase(info.pos);
		add(dni, max(MAX_PTOS, info.puntos + puntos));
	}
	int consultar(string dni) const { // O(1)
		info_conductor info = checkDniExists(dni);
		return info.puntos;
	}
	int cuantos_con_puntos(int puntos){ // O(1)
		checkPtos(puntos);

		return con_puntos.at(puntos).size();
	}
	list<string> const& lista_por_puntos(int puntos) const { // O(1)
		checkPtos(puntos);

		return con_puntos.at(puntos);
	}
private:
	struct info_conductor{
		int puntos;
		list<string>::iterator pos;
	};

	const int MAX_PTOS = 15;
	vector<list<string>> con_puntos; // de 0 a 15
	unordered_map<string,info_conductor> info_de;

	void checkDniNew(string dni) const {
		if(info_de.count(dni)) 
			throw domain_error("Conductor duplicado");
	}
	info_conductor checkDniExists(string dni) const {
		auto it = info_de.find(dni);
		if(it == info_de.end()) 
			throw domain_error("Conductor inexistente");
		return it->second;
	}
	void checkPtos(int puntos) const {
		if(0 > puntos || puntos > 15) 
			throw domain_error("Puntos no validos");
	}
	void add(string dni, int puntos){ // O(1)
		list<string> & lista = con_puntos[puntos]; // O(1)
		auto it = lista.insert(lista.end(), dni); // O(1)
		info_de[dni] = {puntos, it}; // O(1)
	}
};

bool resuelveCaso() {
	string op; cin >> op;
	if(!cin) return false;
	carnet_puntos c;

	string dni; int puntos;
	while(op != "FIN"){
		try{
			if(op == "nuevo"){
				cin >> dni;
				c.nuevo(dni);
			}else if(op == "quitar"){
				cin >> dni >> puntos;
				c.quitar(dni,puntos);
			}else if(op == "recuperar"){
				cin >> dni >> puntos;
				c.recuperar(dni,puntos);
			}else if(op == "consultar"){
				cin >> dni;
				cout << "Puntos de " << dni << ": " << c.consultar(dni);
			cout << '\n';
			}else if(op == "cuantos_con_puntos"){
				cin >> puntos;
				cout << "Con "<< puntos << " puntos hay " << c.cuantos_con_puntos(puntos);
			cout << '\n';
			}else if(op == "lista_por_puntos"){
				cin >> puntos;
				cout << "Tienen " << puntos << " puntos:\n";
				for(string id : c.lista_por_puntos(puntos)){
					cout << id;
					cout << '\n';
				}
			}
		}
		catch(domain_error& e){
			cout << "ERROR: " << e.what() << '\n';
		} 


		cin >> op;
	}

	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}

