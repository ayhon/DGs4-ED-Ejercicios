/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

/*
 * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
 * modificar el código contenido entre las etiquetas <answer>
 * y </answer>. Toda modificación fuera de esas etiquetas no
 * será corregida.
 *
 * Tampoco esta permitido modificar las líneas que contienen
 * las etiquetas <answer> y </answer>, obviamente :-)
 */

//@ <answer>
// Nombre y Apellidos:
//@ </answer>

#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include <vector>
#include <utility>

/*
   Implementación del TAD Conjunto mediante árboles binarios de búsqueda
   */

template <typename T>
class SetTree {
	public:
		SetTree() : root_node(nullptr), num_elems(0) {}
		SetTree(const SetTree &other)
			: num_elems(other.num_elems), root_node(copy_nodes(other.root_node)) {}
		~SetTree() { delete_nodes(root_node); }

		void insert(const T &elem) {
			auto [new_root, inserted] = insert(root_node, elem);
			root_node = new_root;
			if (inserted) {
				num_elems++;
			}
		}

		bool contains(const T &elem) const { return search(root_node, elem); }

		void erase(const T &elem) {
			auto [new_root, removed] = erase(root_node, elem);
			root_node = new_root;
			if (removed) {
				num_elems--;
			}
		}

		int size() const { return num_elems; }
		bool empty() const { return num_elems == 0; }

		SetTree &operator=(const SetTree &other) {
			if (this != &other) {
				num_elems = other.num_elems;
				delete_nodes(root_node);
				root_node = copy_nodes(other.root_node);
			}
			return *this;
		}

		void display(std::ostream &out) const {
			out << "{";
			display(root_node, out);
			out << "}";
		}

		// nuevos métodos, impleméntalos abajo, en el sitio reservado para ello
		T min() const;
		void erase_min();

	private:
		struct Node {
			T elem;
			Node *left, *right;

			Node(Node *left, const T &elem, Node *right)
				: left(left), elem(elem), right(right) {}
		};

		Node *root_node;
		int num_elems;

		void erase_min(Node * root, Node * last);
		T min(Node * root) const;
		static std::pair<bool,T> lower_bound(Node * root, T const& e);

		static Node *copy_nodes(const Node *node) {
			if (node == nullptr) {
				return nullptr;
			} else {
				return new Node(copy_nodes(node->left), node->elem,
						copy_nodes(node->right));
			}
		}

		static void delete_nodes(const Node *node) {
			if (node != nullptr) {
				delete_nodes(node->left);
				delete_nodes(node->right);
				delete node;
			}
		}

		static std::pair<Node *, bool> insert(Node *root, const T &elem) {
			if (root == nullptr) {
				return {new Node(nullptr, elem, nullptr), true};
			} else if (elem < root->elem) {
				auto [new_root_left, inserted] = insert(root->left, elem);
				root->left = new_root_left;
				return {root, inserted};
			} else if (root->elem < elem) {
				auto [new_root_right, inserted] = insert(root->right, elem);
				root->right = new_root_right;
				return {root, inserted};
			} else {
				return {root, false};
			}
		}

		static bool search(const Node *root, const T &elem) {
			if (root == nullptr) {
				return false;
			} else if (elem == root->elem) {
				return true;
			} else if (elem < root->elem) {
				return search(root->left, elem);
			} else {
				return search(root->right, elem);
			}
		}

		static std::pair<Node *, bool> erase(Node *root, const T &elem) {
			if (root == nullptr) {
				return {root, false};
			} else if (elem < root->elem) {
				auto [new_root_left, erased] = erase(root->left, elem);
				root->left = new_root_left;
				return {root, erased};
			} else if (root->elem < elem) {
				auto [new_root_right, erased] = erase(root->right, elem);
				root->right = new_root_right;
				return {root, erased};
			} else {
				return {remove_root(root), true};
			}
		}

		static Node *remove_root(Node *root) {
			Node *left_child = root->left, *right_child = root->right;
			delete root;
			if (left_child == nullptr && right_child == nullptr) {
				return nullptr;
			} else if (left_child == nullptr) {
				return right_child;
			} else if (right_child == nullptr) {
				return left_child;
			} else {
				auto [lowest, new_right_root] = remove_lowest(right_child);
				lowest->left = left_child;
				lowest->right = new_right_root;
				return lowest;
			}
		}

		static std::pair<Node *, Node *> remove_lowest(Node *root) {
			assert(root != nullptr);
			if (root->left == nullptr) {
				return {root, root->right};
			} else {
				auto [removed_node, new_root_left] = remove_lowest(root->left);
				root->left = new_root_left;
				return {removed_node, root};
			}
		}

		static void display(Node *root, std::ostream &out) {
			if (root != nullptr) {
				if (root->left != nullptr) {
					display(root->left, out);
					out << ", ";
				}
				out << root->elem;
				if (root->right != nullptr) {
					out << ", ";
					display(root->right, out);
				}
			}
		}
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const SetTree<T> &set) {
	set.display(out);
	return out;
}

using namespace std;
// ----------------------------------------------------------------
// ¡No modificar nada importante por encima de esta línea!

// Implementa a continuación los métodos pedidos. Puedes declarar otros
// métodos dentro de la clase, implementándolos aquí debajo.
// Completa también la implementación de la función resuelve().
//@ <answer>

template <typename T>
T SetTree<T>::min(Node * root) const {
	if(root == nullptr) return T(); // Garantizado por SetTree no vacio

	if(root->left == nullptr) return root->elem;
	else return min(root->left);
}

template <typename T>
T SetTree<T>::min() const {
	return min(root_node);
}

template <typename T>
void SetTree<T>::erase_min(Node * root, Node * last) {
	if(root == nullptr) return; // Garantizado por SetTree no vacio

	if(root->left != nullptr) 
		return erase_min(root->left, root);

	if(last != nullptr)
		last->left = root->right;
	else 
		this->root_node = root->right; // root->right is now head
	delete root;
}

template <typename T>
void SetTree<T>::erase_min() {
	erase_min(root_node, nullptr);
}

template <class T>
void resuelve(T centinela) {
	int k; cin >> k;
	T elem;
	SetTree<T> conjunto;
	cin >> elem;
	while (elem != centinela) {
		if(conjunto.size() < k)
			conjunto.insert(elem);
		else if(elem > conjunto.min() && !conjunto.contains(elem)){
			conjunto.erase_min();
			conjunto.insert(elem);
		}
		cin >> elem;
	}
	cout << conjunto << '\n';

}
//@ </answer>

// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
	char tipo;
	cin >> tipo;

	if (!cin)
		return false;

	if (tipo == 'N') { // el caso es de números
		resuelve(-1);
	} else { // el caso es de cadenas
		resuelve(string("FIN"));
	}
	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Visual Studio
	// system("PAUSE");
#endif
	return 0;
}

