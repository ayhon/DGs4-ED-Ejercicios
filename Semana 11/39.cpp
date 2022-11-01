//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

class ControlAlumnos{
public:
	void alta(string a, string p){
		int punt = 0;
		if(prof_de.count(a)){
			punt = alumnos_de[prof_de[a]][a];
			alumnos_de[prof_de[a]].erase(a);
		}
		alumnos_de[p][a] = punt;
		prof_de[a] = p;
	}
	bool es_alumno(string a, string p) const{
	 	return prof_de.count(a) && prof_de.at(a) == p;
	}
	int puntuacion(string a) const { 
		assert_registered_student(a);

		return alumnos_de.at(prof_de.at(a)).at(a);
	}
	void actualizar(string a, int n){
		assert_registered_student(a);

		alumnos_de[prof_de[a]][a] += n;
	}
	list<string> examen(string p, int n) const {
		list<string> sol;
		if(alumnos_de.count(p)) for(auto & [a, nota] : alumnos_de.at(p))
			if (nota >= n) sol.push_back(a);
		return sol;
	}
	void aprobar(string a) {
		assert_registered_student(a);

		alumnos_de[prof_de[a]].erase(a);
		prof_de.erase(a);
	}
private:
	//          { profes → { alumno → puntos } }
	unordered_map<string, map<string, int>> alumnos_de;
	unordered_map<string, string> prof_de;
	void assert_registered_student(string a) const {
		if(!prof_de.count(a))
			throw domain_error("El alumno "+a+" no esta matriculado");
	}
};

bool resuelveCaso() {
	string command; cin >> command;
	if(!cin) return false;

	ControlAlumnos c;
	while(command != "FIN"){
		try{
			string a, p;
			int n;
			if (command == "alta"){
				cin >> a >> p;
				c.alta(a,p);
			} else if (command == "es_alumno"){
				cin >> a >> p;
				printf("%s %ses alumno de %s\n",
						a.c_str(),
						(c.es_alumno(a,p)? "" : "no "),
						p.c_str()
					  );
			} else if (command == "puntuacion"){
				cin >> a;
				printf("Puntuacion de %s: %d\n",a.c_str(),c.puntuacion(a));
			} else if (command == "actualizar"){
				cin >> a >> n;
				c.actualizar(a,n);
			} else if (command == "examen"){
				cin >> p >> n;
				list<string> alumnos = c.examen(p,n);
				cout << "Alumnos de " << p << " a examen:\n";
				for(string & s : alumnos){
					cout << s << '\n';
				}
			} else if (command == "aprobar"){
				cin >> a;
				c.aprobar(a);
			}
		}
		catch(domain_error &e){
			cout << "ERROR\n";
		}

		cin >> command;
	}

	cout << "---\n";
	return true;

}

int main() {
	while(resuelveCaso());
	return 0;
}


