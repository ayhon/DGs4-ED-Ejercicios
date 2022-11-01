//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

bool resuelveCaso() {
	int n; cin >> n;
	if(n == 0) return false;
	
	unordered_map<int, set<string>> names;
	unordered_map<string, int> left;

	for(int i = 0; i < n; ++i){
		string name; cin >> name;
		int x; cin >> x;
		while(x != 0){
			names[x].insert(name);
			left[name]++;
			cin >> x;
		}
	}

	int x;
	bool noGanador = true;
	vector<string> winners;
	while(noGanador){
		cin >> x; 
		for(string const& name : names[x]){
			left[name]--;
			if(left[name] == 0) {
				noGanador = false;
				cout << name << " ";
			}
		}
	}
	cout << '\n';

	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}

