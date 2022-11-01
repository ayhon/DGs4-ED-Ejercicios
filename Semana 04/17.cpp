/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

/*
 * Implementación del TAD Lista mediante listas enlazadas dobles.
 *
 * Esta versión incluye la sobrecarga de operadores <<, [] y asignación.
 */

#include <cassert>
#include <iostream>
#include <string>
using namespace std;

class ListLinkedDouble {
	private:
		struct Node {
			char value;
			Node *next;
			Node *prev;
		};

	public:
		ListLinkedDouble() : num_elems(0) {
			head = new Node;
			head->next = head;
			head->prev = head;
			cursor = head;
		}

		ListLinkedDouble(const ListLinkedDouble &other) : ListLinkedDouble() {
			copy_nodes_from(other);
			num_elems = other.num_elems;
		}

		~ListLinkedDouble() { delete_nodes(); }

		void push_front(const char &elem) {
			Node *new_node = new Node{elem, head->next, head};
			head->next->prev = new_node;
			head->next = new_node;
			num_elems++;
		}

		void push_back(const char &elem) {
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

		const char &front() const {
			assert(num_elems > 0);
			return head->next->value;
		}

		char &front() {
			assert(num_elems > 0);
			return head->next->value;
		}

		const char &back() const {
			assert(num_elems > 0);
			return head->prev->value;
		}

		char &back() {
			assert(num_elems > 0);
			return head->prev->value;
		}

		const char &operator[](int index) const {
			assert(0 <= index && index < num_elems);
			Node *result_node = nth_node(index);
			return result_node->value;
		}

		char &operator[](int index) {
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

		void display() const { display(std::cout); }

		void flechaDerecha(){
			if(cursor->next != head)
				cursor = cursor->next;
		}

		void supr(){
			if(cursor->next != head){
				Node* toElim = cursor->next;

				toElim->next->prev = toElim->prev;
				toElim->prev->next = toElim->next;

				delete toElim;
			}
		}
		
		void write(char c){
			Node* newNode = new Node{c, cursor->next, cursor};
			newNode->prev->next = newNode->next->prev = newNode;
			cursor = newNode;
		}

		void inicio(){
			cursor = head;
		}

		void fin(){
			cursor = head->prev;
		}

	private:
		Node *head;
		Node * cursor;
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
	if (head->next != head) {
		out << head->next->value;
		Node *current = head->next->next;
		while (current != head) {
			out << current->value;
			current = current->next;
		}
	}
}

std::ostream &operator<<(std::ostream &out, const ListLinkedDouble &l) {
	l.display(out);
	return out;
}

bool resuelveCaso(){
	string input; cin >> input;
	if(!cin) return false;

	ListLinkedDouble typewritter;
	for(char const& c : input){
		switch(c){
			case '-':
				typewritter.inicio();
				break;
			case '+':
				typewritter.fin();
				break;
			case '*':
				typewritter.flechaDerecha();
				break;
			case '3':
				typewritter.supr();
				break;
			default:
				typewritter.write(c);
				break;
		}
	}
	typewritter.display();
	cout << '\n';
	return true;
}

int main(){
	while(resuelveCaso());
	return 0;
}
