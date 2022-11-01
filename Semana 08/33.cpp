//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

void tolower(string & s){
	for(char & c : s) c = tolower(c);
}

bool resuelveCaso() {
	int n; cin >> n;
	if( n == 0) return false;

	map<string, vector<int>> refs;
	vector<string> words;
	string line; getline(cin, line); // Quitarsse el \n sobrante

	for(int i =0; i < n; ++i){
		getline(cin, line);
		stringstream ss(line); // Conseguimos la linea actual

		string word;
		while(ss >>  word){ // Por cada palabra en la linea
			tolower(word); // Normalizar
			if(word.length() <= 2) continue; // Filtrar

			if(refs.find(word) == refs.end()) 
				words.push_back(word); // Añadir a palabras validas
			if(refs[word].empty() || refs[word].back() != i+1) 
				refs[word].push_back(i+1); // Añadir referencia
		}
	}

	sort(words.begin(), words.end()); // Ordenar alfabéticamente
	for(string const& word : words){ // Imprimir por pantalla
		cout << word;
		for(int ref : refs[word]) cout << " " << ref;
		cout << '\n';
	}

	cout << "---\n";  // NO TE OLVIDES DEL --- !!!
	return true;
}

int main() {
	while( resuelveCaso());
	return 0;
}

