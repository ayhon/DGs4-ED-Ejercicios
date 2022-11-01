//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

struct InfoPeli{
	string nombre;
	unordered_map<string, int> act;
	// nombre → tmpo pantalla
};

bool resuelveCaso() {
	int p; cin >> p; // p <= 1e4
	if(p == 0) return false;

	unordered_map<string, InfoPeli> info_pelis;
	string titulo;
	for(int i = 0; i < p; ++i){ // 1e4
		int a;
		cin >> titulo >> a;
		info_pelis[titulo].nombre = titulo;
		for(int j = 0; j < a; ++j){ // 50
			string nombre; int tmp_act;
			cin >> nombre >> tmp_act;
			info_pelis[titulo].act[nombre] = tmp_act;
		}
	} // 1e5

	unordered_map<string, int> ap_act;
	unordered_map<string, int> ap_film;
	int e; cin >> e;
	int maxi = 0;
	string ganadora = titulo;
	for(int i = 0; i < e; ++i){ // 1e5
		string nombre_pelicula;
		cin >> nombre_pelicula;
		ap_film[nombre_pelicula]++;
		if(ap_film[nombre_pelicula] >= maxi){
			maxi = ap_film[nombre_pelicula];
			ganadora = nombre_pelicula;
		}
		for(auto & [nombre, tmp] : info_pelis[nombre_pelicula].act){ // 59
			ap_act[nombre]+=tmp;
		}
	} // 1e6

	cout << maxi << " " << ganadora << '\n';

	set<string> swin; // Set of winners
	int mst = 0; // max screen time
	for(auto & [actor, tmp] : ap_act){ // 1e6
		if(tmp > mst){
			swin.clear();
			mst = tmp;
			swin.insert(actor);
		}
		else if (tmp == mst)
			swin.insert(actor);
	}
	cout << mst;
	for(auto & name : swin) cout << " " << name;
	cout << '\n';

	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}
