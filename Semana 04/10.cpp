//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

/* char open(char const& c){ */
/* 	switch(c){ */
/* 		case ')': */
/* 			return '('; */
/* 			break; */
/* 		case ']': */
/* 			return '['; */
/* 			break; */
/* 		case '}': */
/* 			return '{'; */
/* 			break; */
/* 	} */
/* 	return ' '; */
/* } */

bool resuelveCaso() {
	string input; getline(cin,input);
	if(!cin) return false;

	stack<char> pila;
	bool error = false;
	for(char const& c : input){
		switch(c){
			case '(':
			case '[':
			case '{':
				pila.push(c);
				break;
			case ')':
				error = (pila.empty()) || (pila.top() != '(');
				if(!error) pila.pop();
				break;
			case ']':
				error = (pila.empty()) || (pila.top() != '[');
				if(!error) pila.pop();
				break;
			case '}':
				error = (pila.empty()) || (pila.top() != '{');
				if(!error) pila.pop();
				break;
		}

		if(error) break;
	}

	cout <<  (!pila.empty() || error? "NO" : "SI") << '\n';

	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}

