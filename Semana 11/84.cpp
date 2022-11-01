//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

void resuelveCaso() {
	map<int, int> mapeo;
	vector<pair<string, int>> instructions;
	int ln; cin >> ln;
	while(ln != 0){
		string inst; cin >> inst;
		int a = -1;
		if(inst != "RETURN")
			cin >> a;
		instructions.push_back({inst,a});
		mapeo[ln] = instructions.size();
		cin >> ln;
	}
	for(auto &[ln, count] : mapeo){
		auto &[inst, op] = instructions[count-1];
		cout << count*10 << " "
		 	 << inst << " "
			 << (inst == "RETURN"? "" : to_string(mapeo[op]*10))
			 << '\n';
	}
	cout << "---\n";
}

int main() {
	int T; cin >> T;
	for(int caso = 1; caso <= T; caso++) {
		// cout << "Case #" << caso <<":\n";
		resuelveCaso();
	}
	return 0;
}

