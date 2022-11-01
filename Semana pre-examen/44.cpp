//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

using Book = string;

/*
 map libro → (# ejemplares, # ventas)
 vector top10 libros:
  → Se va incrementando
  → Ordenados por (Uds vendidas, momento venta)
*/

class BookManager{
public:
	/* BookManager(): top(10){} */
	void nuevoLibro(int n, Book x){
		dict[x].stock += n;
	}
	void comprar(Book x){
		auto it = dict.find(x);
		if (it == dict.end()) throw invalid_argument("Libro no existente");
		BookInfo & info = it->second;
		if (info.stock == 0) throw out_of_range("No hay ejemplares");
		info.stock--;
		info.sold++;

		if(top.empty()) top.push_back(x);
		else if(dict[top.back()].sold < info.sold || top.size() < 10){
			auto it = find(top.begin(), top.end(), x);
			if(it == top.end()){
				if(top.size() < 10) 
					top.push_back(x);
				else{
					int i;
					for(i = top.size()-1; i >= 1 && dict[top[i]].sold <= info.sold; --i)
						top[i-1] = top[i];
					top[i] = x;
				}
			}
			else{
				int i;
				for(i = top.size()-1; i >= 0 && top[i] != x; --i);
				i--;
				for(; i >= 0 && dict[top[i]].sold <= info.sold; --i) 
					swap(top[i], top[i+1]);
			}
		}

	}
	bool estaLibro(Book x){
		return dict.count(x);
	}
	void elimLibro(Book x){
		auto it = dict.find(x);
		if(it != dict.end())
			dict.erase(it);
	}
	int numEjemplares(Book x){
		auto it = dict.find(x);
		if(it == dict.end()) throw invalid_argument("Libro no existente");
		return it->second.stock;
	}
	vector<Book> const& top10(){
		return top;
	}

private:
	struct BookInfo{
		int stock = 0;
		int sold = 0;
	};
	unordered_map<Book, BookInfo> dict;
	vector<Book> top;
};

bool resuelveCaso() {
	int t; cin >> t;
	if(!cin) return false;
	cin.ignore();

	BookManager b;

	string op; Book x; int n;
	for(int i = 0; i < t; ++i){
		cin >> op; cin.ignore();
		try{
			if(op == "nuevoLibro"){
				cin >> n; cin.ignore(); getline(cin,x);
				b.nuevoLibro(n,x);
			}
			else if (op == "comprar"){
				getline(cin,x);
				b.comprar(x);
			}
			else if (op == "estaLibro"){
				getline(cin,x);
				printf(b.estaLibro(x)? "El libro %s esta en el sistema\n" : "No existe el libro %s en el sistema\n", x.c_str());
			}
			else if (op == "elimLibro"){
				getline(cin,x);
				b.elimLibro(x);
			}
			else if (op == "numEjemplares"){
				getline(cin,x);
				try{
					cout << "Existen " << b.numEjemplares(x) << " ejemplares del libro " << x << '\n';
				}
				catch(invalid_argument& e){
					cout << "No existe el libro " << x << " en el sistema\n";
				}
			}
			else if (op == "top10"){
				/* getline(cin,x); */
				cout << "TOP10\n";
				for(Book book : b.top10())
					cout << "    " << book << '\n';
			}
		}
		catch(exception& e){
			cout << e.what() << '\n';
		}
	}

	cout << "---\n";
	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}

