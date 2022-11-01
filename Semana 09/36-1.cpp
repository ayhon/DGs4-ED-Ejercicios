//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

bool resuelveCaso() {
	int n; cin >> n;
	if(n == 0) return false;
	
	unordered_map<string, unordered_set<int>> nums(n);

	for(int i = 0; i < n; ++i){
		string name; cin >> name;
		int x; cin >> x;
		while(x != 0){
			nums[name].insert(x);
			cin >> x;
		}
	}

	int x;
	bool noGanador = true;
	set<string> winners;
	while(noGanador){
		cin >> x;
		for(auto [name, s] : nums){
			s.erase(x);
			if(s.empty()){
				noGanador = false;
				winners.insert(name);
			}
		}
	}
	
	for(string const& name : winners)
		cout << name << " ";
	cout << '\n';

	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}

