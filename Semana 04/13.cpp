//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

void invertirSeq(vector<char> & s, int ini, int fin){
	/* assert(fin <= (int)s.size()); */
	/* assert(ini >= 0); */
	/* assert(ini <= ini); */
	if(fin-ini <= 1) return;

	reverse(s.begin()+ini,s.begin()+fin);
}

bool esVocal(char c){
	int l = tolower(c);
	return l == 'a' 
		|| l == 'e'
		|| l == 'i'
		|| l == 'o'
		|| l == 'u';
	
}

void primeraEtapaDecodificacion(vector<char> & s){
	stack<char> p; // Para los elementos del final
	queue<char> q; // Para los elementos del principio
	for(int i = 0; i < (int)s.size(); i++){
		if(i%2 == 0) // No se invirtió su orden
			q.push(s[i]);
		else // Su orden fue invertido
			p.push(s[i]);
	}
	// At this point, q.size() + p.size() == original s.size() 
	int idx = 0;
	while(!q.empty()){
		s[idx] = q.front();
		idx++;
		q.pop();
	}
	while(!p.empty()){
		s[idx] = p.top();
		idx++;
		p.pop();
	}
}

// Igual que primera etapa de codificación
void segundaEtapaDecodificacion(vector<char> & s){ 
	int j = 0;
	for(int i = 0; i < (int)s.size(); ++i){
		if(esVocal(s[i])){
			invertirSeq(s,j,i);
			j = i+1;
		}
	}
	invertirSeq(s,j,s.size());
}

bool resuelveCaso() {
	string input; getline(cin,input);
	if(!cin) return false;
	if(input == "") {
		cout << input << '\n';
		return true;
	}
	// Garantizamos que input tiene al menos un caracter

	vector<char> s;
	for(char & c : input)
		s.push_back(c);

	primeraEtapaDecodificacion(s);
	segundaEtapaDecodificacion(s);

	for(auto & e : s) cout << e;
	cout << '\n';

	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}

