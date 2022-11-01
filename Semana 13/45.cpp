//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

using empleo = string;
using nombre = string;

class OficinaEmpleo{
private:
	unordered_map<empleo, list<nombre>> empleos;
	using InfoEmpleado = map<empleo, list<nombre>::iterator>;
	unordered_map<nombre, InfoEmpleado> empleados;
public:
	void altaOficina(nombre const& nom, empleo const& emp){ // O(logn) con n capacidades de emp
		auto & capacidades = empleados[nom]; 
		if(!capacidades.count(emp)){ // El empleo para el que se apunta es nuevo
			auto & lista = empleos[emp];
			capacidades.insert({emp,lista.insert(lista.end(), nom)});
		}
	}

	nombre ofertaEmpleo(empleo const& emp){
		auto it = empleos.find(emp);
		if(it == empleos.end())
			throw domain_error("No existen personas apuntadas a este empleo");
		nombre afortunado = it->second.front();
		for(auto & [capacidad, it] : empleados[afortunado]){ // O(n) n numero empleos de afortunado
			auto & lista = empleos[capacidad];
			lista.erase(it);
			if(lista.empty())
				empleos.erase(capacidad);
		}
		empleados.erase(afortunado);
		return afortunado;
	}

	vector<string> listadoEmpleos(nombre const& nom) const { // O(n) con n lista de empleos
		auto it = empleados.find(nom);
		if(it == empleados.end())
			throw domain_error("Persona inexistente");
		vector<string> res;
		for(auto & [emp, _] : it->second)
			res.push_back(emp);
		return res;
	}
};

bool resuelveCaso() {
	string op; cin >> op;
	if(!cin) return false;
	string nombre, empleo;
	OficinaEmpleo paro;
	while(op != "FIN"){
		try{
			if(op == "altaOficina"){
				cin >> nombre >> empleo;
				paro.altaOficina(nombre,empleo);
			}
			else if (op == "ofertaEmpleo"){
				cin >> empleo;
				string afortunado = paro.ofertaEmpleo(empleo);
				cout << empleo << ": " << afortunado << '\n';
			}
			else if(op == "listadoEmpleos"){
				cin >> nombre;
				auto v = paro.listadoEmpleos(nombre); 
				cout << nombre << ":";
				for(auto s : v){
					cout << " " << s;
				}
				cout << '\n';
			}
		}
		catch(domain_error& e){
			cout << "ERROR: " << e.what() << '\n';
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

