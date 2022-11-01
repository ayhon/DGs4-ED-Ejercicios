#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <map>
using namespace std;

class Tienda
{
    /*
    
    Adquisición y venta de productos
    Productos identificados por string (sin espacios)
    Unidades de productos en almacen
    Lista de espera en orden de llegada
    Clientes como string
    Fecha como string

    Fechas en formato YYYY/MM/DD
                      0123456789
    */
public:
    int cuantos(string const &prod) const
    {
        return almacen.at(prod).cantidad;
    }

    bool hay_esperando(string const &prod) const
    {
        return !almacen.at(prod).lista_espera.empty();
    }

    vector<string> adquirir(string const &prod, string const &fecha, int cant)
    {
        vector<string> rv;
        if (hay_esperando(prod))
        {
            int servidos = min((int)almacen[prod].lista_espera.size(), cant);
            almacen[prod].cantidad -= servidos;
            for (int i = 0; i < servidos; ++i)
            {
                rv.push_back(almacen[prod].lista_espera.front());
                almacen[prod].lista_espera.pop();
            }
        }

        almacen[prod].existencias[fecha] += cant;
        almacen[prod].cantidad += cant;

        return rv;
    }
    // <hayExistencias?, fecha>
    pair<bool, string> vender(string const &prod, string const &cliente)
    {
        if (cuantos(prod) > 0)
        {
            string const &fecha = almacen[prod].existencias.begin()->first;
            almacen[prod].existencias[fecha]--;
            almacen[prod].cantidad--;
            return {true, fecha};
        }
        else
        {
            almacen[prod].lista_espera.push(cliente);
            return {false, ""};
        }
    }

private:
    /*
    prod → cantidad
    prod → fecha
    prod → lista_espera
    lista_espera por orden de llegada


    almacen: prod -> existencias(fecha → cantidad) / lista_espera(lista clientes)
    */
    struct InfoProd
    {
        int cantidad;
        map<string, int> existencias;
        queue<string> lista_espera;
    }; 
    unordered_map<string, InfoProd> almacen;
};

void
caso(string const &init)
{
    string op;
    op = init;
    string d,m,y, prod, cliente;
    int cant;
    Tienda t;
    while (op != "FIN")
    {
        if(op == "vender"){
            cin >> prod >> cliente;
            auto p = t.vender(prod,cliente);
            cout << (p.first? "VENDIDO" : "EN ESPERA") << '\n';
        }
        else if(op == "adquirir"){
            cin >> prod;
            scanf("%s/%s/%s",&d, &m, &y);
            cin >> cant;
            auto v = t.adquirir(prod, y+'/'+m+'/'+d, cant);
            cout << "PRODUCTO ADQUIRIDO";
            for(auto const& e : v){
                cout << " " << e;
            }
            cout << '\n';
        }
        else if(op == "cuantos"){
            cin >> prod;
            cout << t.cuantos(prod) << '\n';
        }
        else if(op == "hay_esperando"){
            cin >> prod;
            cout << (t.hay_esperando(prod)? "SI" : "NO") << '\n';
        }

        cin >> op;
    }
    cout << "---\n";
}

int main()
{
    string op;
    cin >> op;
    while (!cin)
    {
        caso(op);
        cin >> op;
    }
    return 0;
}