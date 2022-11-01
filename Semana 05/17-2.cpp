//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

bool resuelveCaso() {
	string input; cin >> input;
	if(!cin) return false;

	list<char> typewritter;
	list<char>::iterator cursor = typewritter.begin();
	for(char const& c : input){
		switch(c){
			case '-':
				// Inicio
				cursor = typewritter.begin();
				break;
			case '+':
				// Fin
				cursor = typewritter.end();
				break;
			case '*':
				// Flecha derecha
				if(cursor != typewritter.end()) 
					++cursor;
				break;
			case '3':
				// Suprimir
				if(cursor != typewritter.end()) 
					cursor = typewritter.erase(cursor);
				break;
			default:
				// Escribir 
				cursor = typewritter.insert(cursor,c);
				++cursor;
				break;
		}
	}
	for(char c : typewritter) cout << c;
	cout << '\n';
	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}
