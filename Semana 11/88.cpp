//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

const int PenWA = 20;

struct InfoProblema{
	int intentos = 0;
	bool resuelto = false;
};

struct InfoEquipo{
	int puntuacion = 0;
	int resueltos = 0;
	string nombre;
	unordered_map<string, InfoProblema> problemas;
	// penaliz problemas: problema → Puntos
};

ostream& operator<<(ostream & out, InfoEquipo const& ie){
	out << ie.nombre << " " << ie.resueltos << " " << ie.puntuacion;
	return out;
}

void resuelveCaso() {
	string nombre_equipo, nombre_problema, veredicto;
	int tiempo_envio;

	unordered_map<string, InfoEquipo> info_equipos;
	// nombre -> Info

	cin >> nombre_equipo;
	while(nombre_equipo != "FIN"){
		cin >> nombre_problema >> tiempo_envio >> veredicto;
		auto & info =  info_equipos[nombre_equipo];
		auto & problema = info.problemas[nombre_problema];
		info.nombre = nombre_equipo;
		problema.intentos++;
		if(veredicto == "AC"){
			if(!problema.resuelto){
				info.puntuacion += tiempo_envio + PenWA * (problema.intentos-1);
				info.resueltos++;
				problema.resuelto = true;
			}
		}
		cin >> nombre_equipo;
	}

	vector<InfoEquipo> final_score;
	for(auto & [n_equipo, info] : info_equipos){
		final_score.push_back(info);
	}
	sort(final_score.begin(), final_score.end(),
		[](InfoEquipo const& ie1, InfoEquipo const& ie2){
			if(ie1.resueltos > ie2.resueltos)
				return true;
			if(ie1.puntuacion < ie2.puntuacion)
				return true;
			if(ie1.nombre < ie2.nombre)
				return true;
			return false;
	});
	for(auto & info : final_score)
		cout << info << '\n';

}

int main() {
	int T; cin >> T;
	for(int caso = 1; caso <= T; caso++) {
		// cout << "Case #" << caso <<":\n";
		resuelveCaso();
	}
	return 0;
}
