//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

void resuelveCaso() {

}

int main() {
	cout << (4 ^ 5) << '\n';
	ifstream archivo;
	archivo.open("example.txt");
	if(archivo.is_open()){
		string aux; archivo >> aux;
		cout << aux;
		cout << "\n----\n";

		getline(archivo, aux);
		cout << aux;
		cout << "\n----\n";

		char c; archivo.get(c);
		cout << c;
		cout << "\n----\n";

		archivo.close();
	}
	int arr[34];
	arr[2] = 1;
	cout << arr[2] << '\n';
	return 0;
}
