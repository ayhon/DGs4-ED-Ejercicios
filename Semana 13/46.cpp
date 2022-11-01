//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

class Urgencias{
public:
	Urgencias(){
		sala.resize(3);
	}
	void nuevo_paciente(string const& paciente, int gravedad){

	}
private:
	vector<list<string>> sala;
	unordered_map<string, int> posicion;
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

