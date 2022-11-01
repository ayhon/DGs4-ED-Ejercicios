/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

/*
 * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
 * modificar el código contenido entre las etiquetas <answer>
 * y </answer>. Toda modificación fuera de esas etiquetas está
 * prohibida, pues no será corregida.
 *
 * Tampoco esta permitido modificar las líneas que contienen
 * las etiquetas <answer> y </answer>, obviamente :-)
 */

/*@ <answer>
 * Nombre y Apellidos: Fernando Isaías Leal Sánchez
 *@ </answer> */

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

/*@ <answer> */

class Polinomio {
private:
    struct monomio {
        int coef;
        int exp;
    };
    vector<monomio> data;

    int bbin(int exp){ 
        int ini = 0, fin = data.size();
        while(ini < fin){
            int mid = (ini+fin)/2;
            if(exp <= data[mid].exp)
                fin = mid;
            else ini = mid + 1;
        }
        return ini;
    }
    void insert(int idx, monomio m){
        data.insert(data.begin()+idx,m);
    }
    // int mypow(int valor, int exp){
    //     if(exp == 0) return 1;
    //     if(exp == 1) return valor;
    //     if(exp == 2) return valor * valor;

    // }
public:
    void sumaMono(int coef, int exp) { 
        int idx = bbin(exp);
        if(idx < (int)data.size() && data[idx].exp == exp){
            data[idx].coef += coef;
			if(data[idx].coef == 0){
				data.erase(data.begin()+idx);
			}
		}
        else insert(idx,{coef,exp});
    }
    
    /*
    Horners rule

    f(x) = ax² + bx + c = (ax + b)x + c
    3x^2 + 6x + 2 = (3x + 6)x + 2
    x^5 + 2x^3 = ((((1*x)x) + 2)x)x)x
    
    */
    int64_t evalua(int valor) const {
        int64_t res = 0;
        // for(int cexp = data.back().exp, idx = data.size()-1; cexp>=0; cexp--){
        //     int c = 0;
        //     if(cexp == data[idx].exp){
        //         c= data[idx].coef;
        //         idx--;
        //     }    
        //     res = res * valor + c;
        // }
        int64_t pot = 1, exp_pot = 0;
        for(int i = 0; i < (int)data.size(); i++){
            if(exp_pot < data[i].exp){
                for(; exp_pot < data[i].exp; exp_pot++)
                    pot *= valor;
            }
            res += pot * data[i].coef;
        }
        return res;
    }
};


bool resuelveCaso() {
  int coef, exp;
  cin >> coef >> exp;
  
  if (!cin)
      return false;
  
  // leemos el polinomio, monomio a monomio
  Polinomio poli;
  while (coef != 0 || exp != 0) {
      poli.sumaMono(coef, exp);
      cin >> coef >> exp;
  }
  
  int N;
  cin >> N;
  while (N--) {
      // evaluamos para un nuevo valor
      int valor;
      cin >> valor;
      cout << poli.evalua(valor);
      if (N) cout << ' ';
  }
  cout << '\n';
  return true;
}

/*@ </answer> */

int main() {
  
#ifndef DOMJUDGE
  std::ifstream in("casos.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  while (resuelveCaso()) {}
  
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Comentar si no se trabaja en Visual Studio
  system("PAUSE");
#endif
  
  return 0;
}



