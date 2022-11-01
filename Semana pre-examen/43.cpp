//Author: Ayhon
#include <bits/stdc++.h>
using namespace std; 
class iPud{
public:
	void addSong(string const& S,string const& A,int D){
		auto it = info.find(S); if(it != info.end()) throw domain_error("addSong"); 
		info[S].duracion = D;
		info[S].artista = A;
		info[S].nombre = S;
		info[S].pos_todo = todo.end();
		info[S].pos_done = done.end();
	}
	void addToPlaylist(string const& S){
		auto it = info.find(S);
		if(it == info.end()) throw domain_error("addToPlay");

		if(it->second.pos_todo == todo.end()){
			it->second.pos_todo = todo.insert(todo.end(),it->second.nombre);
			dur_playlist += it->second.duracion;
		}
	}
	string current() const {
		if(todo.empty()) throw domain_error("current");
		return todo.front();
	}
	void play(){
		if(!todo.empty()){
			string const& s = todo.front();
			auto & info_s = info[s];
			if(info_s.pos_done != done.end())
				done.erase(info_s.pos_done);

			dur_playlist -= info_s.duracion;
			todo.pop_front();
			info_s.pos_done = done.insert(done.end(), info_s.nombre);
			info_s.pos_todo = todo.end();
		}
	}
	int totalTime() const {
		return dur_playlist;
	}
	list<string> recent(int N){
		list<string> res;
		for(auto & r : done){
			res.push_back(r);
			if((int)res.size() == N) break;
		}
		return res;

	}
	void deleteSong(string S){
		if(info.count(S)){
			auto & info_s = info[S];
			if(info_s.pos_todo != todo.end()){
				todo.erase(info_s.pos_todo);
				dur_playlist -= info_s.duracion;
			}
			if(info_s.pos_done != done.end()) done.erase(info_s.pos_done);
			info.erase(S);
		}
	}
private:
	struct InfoCancion{
		string nombre;
		string artista;
		int duracion = 0;
		list<string>::iterator pos_todo;
		list<string>::iterator pos_done;
	};
	map<string, InfoCancion> info;
	list<string> todo;
	list<string> done;
	int dur_playlist;
};

bool resuelveCaso() {
	string op; cin >> op;
	if(!cin) return false;

	string s, a; int n;
	iPud p; 

	while(op != "FIN"){
		try{
			if(op == "addSong"){
				cin >> s >> a >> n;
				p.addSong(s,a,n);
			} else if(op ==  "addToPlaylist"){
				cin >> s;
				p.addToPlaylist(s);
			} else if(op ==  "current"){
				p.current();
			} else if(op ==  "play"){
				try{
					auto curr = p.current();
					cout << "Sonando " << curr << '\n';
					p.play();
				}
				catch(domain_error & e){
					cout << "No hay canciones en la lista\n";
				}
			} else if(op ==  "totalTime"){
				int tmp = p.totalTime();
				cout << "Tiempo total " << tmp << '\n';
			} else if(op ==  "recent"){
				cin >> n;
				auto v = p.recent(n);
				cout << "Las " << n << " más recientes\n";
				for(auto c : v){
					cout << "    " << c << '\n';
				}

			} else if(op ==  "deleteSong"){
				cin >> s;
				p.deleteSong(s);
			}
		} catch(domain_error& e){
			cout << "ERROR " << e.what() << '\n';
		}
		cin >> op;
	}
	cout << "---\n";
	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}
