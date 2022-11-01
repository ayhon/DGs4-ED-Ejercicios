/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

/*
 * MUY IMPORTANTE: Para realizar este ejercicio solo puedes
 * modificar el código contenido entre las etiquetas <answer>
 * y </answer>. Toda modificación fuera de esas etiquetas está
 * prohibida, pues no será corregida.
 *
 * Tampoco esta permitido modificar las líneas que contienen
 * las etiquetas <answer> y </answer>, obviamente :-)
 */

//@ <answer>
// Nombre y Apellidos: Fernando Leal
//@ </answer>

/*
 * Implementa las operaciones pedidas en el ejercicio al final de
 * este fichero, entre las etiquetas.
 */

#include <cassert>
#include <iostream>
#include <fstream>

class ListLinkedDouble {
	private:
		struct Node {
			int value;
			Node *next;
			Node *prev;
		};

	public:
		ListLinkedDouble() : num_elems(0) {
			head = new Node;
			head->next = head;
			head->prev = head;
		}

		ListLinkedDouble(const ListLinkedDouble &other) : ListLinkedDouble() {
			copy_nodes_from(other);
			num_elems = other.num_elems;
		}

		~ListLinkedDouble() { delete_nodes(); }

		void push_front(const int &elem) {
			Node *new_node = new Node{elem, head->next, head};
			head->next->prev = new_node;
			head->next = new_node;
			num_elems++;
		}

		void push_back(const int &elem) {
			Node *new_node = new Node{elem, head, head->prev};
			head->prev->next = new_node;
			head->prev = new_node;
			num_elems++;
		}

		void pop_front() {
			assert(num_elems > 0);
			Node *target = head->next;
			head->next = target->next;
			target->next->prev = head;
			delete target;
			num_elems--;
		}

		void pop_back() {
			assert(num_elems > 0);
			Node *target = head->prev;
			target->prev->next = head;
			head->prev = target->prev;
			delete target;
			num_elems--;
		}

		int size() const { return num_elems; }

		bool empty() const { return num_elems == 0; };

		const int &front() const {
			assert(num_elems > 0);
			return head->next->value;
		}

		int &front() {
			assert(num_elems > 0);
			return head->next->value;
		}

		const int &back() const {
			assert(num_elems > 0);
			return head->prev->value;
		}

		int &back() {
			assert(num_elems > 0);
			return head->prev->value;
		}

		const int &operator[](int index) const {
			assert(0 <= index && index < num_elems);
			Node *result_node = nth_node(index);
			return result_node->value;
		}

		int &operator[](int index) {
			assert(0 <= index && index < num_elems);
			Node *result_node = nth_node(index);
			return result_node->value;
		}

		ListLinkedDouble &operator=(const ListLinkedDouble &other) {
			if (this != &other) {
				delete_nodes();
				head = new Node;
				head->next = head->prev = head;
				copy_nodes_from(other);
				num_elems = other.num_elems;
			}
			return *this;
		}

		void display(std::ostream &out) const;

		void display() const {
			display(std::cout);
		}

		void display_reverse(std::ostream &out) const;

		void display_reverse() const {
			display_reverse(std::cout);
		}

		// Nuevo método. Debe implementarse abajo
		void interchange2();

	private:
		Node *head;
		int num_elems;

		Node *nth_node(int n) const;
		void delete_nodes();
		void copy_nodes_from(const ListLinkedDouble &other);

};

ListLinkedDouble::Node *ListLinkedDouble::nth_node(int n) const {
	int current_index = 0;
	Node *current = head->next;

	while (current_index < n && current != head) {
		current_index++;
		current = current->next;
	}

	return current;
}

void ListLinkedDouble::delete_nodes() {
	Node *current = head->next;
	while (current != head) {
		Node *target = current;
		current = current->next;
		delete target;
	}

	delete head;
}

void ListLinkedDouble::copy_nodes_from(const ListLinkedDouble &other) {
	Node *current_other = other.head->next;
	Node *last = head;

	while (current_other != other.head) {
		Node *new_node = new Node{current_other->value, head, last};
		last->next = new_node;
		last = new_node;
		current_other = current_other->next;
	}
	head->prev = last;
}

void ListLinkedDouble::display(std::ostream &out) const {
	out << "[";
	if (head->next != head) {
		out << head->next->value;
		Node *current = head->next->next;
		while (current != head) {
			out << ", " << current->value;
			current = current->next;
		}
	}
	out << "]";
}

void ListLinkedDouble::display_reverse(std::ostream &out) const {
	out << "[";
	if (head->prev != head) {
		out << head->prev->value;
		Node *current = head->prev->prev;
		while (current != head) {
			out << ", " << current->value;
			current = current->prev;
		}
	}
	out << "]";
}

std::ostream &operator<<(std::ostream &out, const ListLinkedDouble &l) {
	l.display(out);
	return out;
}

// ----------------------------------------------------------------
// ¡No modificar nada importante por encima de esta línea!

// Implementa a continuación el método pedido.
//@ <answer>

void ListLinkedDouble::interchange2() {
	Node* curr = head->next;

	while(curr != head && curr->next != head){
		// prevNode <-> 1 <-> 2 <-> nextNode
		Node * nextNode = curr->next->next; 
		Node * prevNode = curr->prev;
		curr->next->next = curr;
		curr->prev = curr->next;

		curr->prev->prev = prevNode;
		prevNode->next = curr->prev;

		curr->next = nextNode;
		nextNode->prev = curr;

		curr = nextNode;
	}
}

using namespace std;

bool resuelveCaso() {
	int n; cin >> n;
	if(n==0) return false;

	ListLinkedDouble l;
	for(int i = 0; i < n; ++i){
		int aux; cin >> aux;
		l.push_back(aux);
	}

	l.interchange2();
	cout << l << '\n';

	return true;
}

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------
int main() {

#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se necesita
	// system("PAUSE");
#endif

	return 0;
}



