//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

class Persona {
	int age;
	string name;

public:
	Persona() : Persona(0,""){}
	Persona(int a, string s) : age(a), name(s) {}

	int getAge() const { return age; }
	void setAge(int a){ age = a; }

	string getName() const { return name; }
	void setName(string s) { name = s; }
};

ostream & operator<<(ostream & out, Persona const& p){
	out << p.getName();
	return out;
}

class BoundedPredicate {
	int mini;
	int maxi;
public:
	BoundedPredicate(int l, int h) : mini(l), maxi(h) {}

	bool operator()(Persona const& p){
		return p.getAge() >= mini && p.getAge() <= maxi;
	}
};

class ListLinkedDouble {
private:
   struct Node {
      Persona value;
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
   
   void push_front(const Persona &elem) {
      Node *new_node = new Node{elem, head->next, head};
      head->next->prev = new_node;
      head->next = new_node;
      num_elems++;
   }
   
   void push_back(const Persona &elem) {
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
   
   const Persona &front() const {
      assert(num_elems > 0);
      return head->next->value;
   }
   
   Persona &front() {
      assert(num_elems > 0);
      return head->next->value;
   }
   
   const Persona &back() const {
      assert(num_elems > 0);
      return head->prev->value;
   }
   
   Persona &back() {
      assert(num_elems > 0);
      return head->prev->value;
   }
   
   const Persona &operator[](int index) const {
      assert(0 <= index && index < num_elems);
      Node *result_node = nth_node(index);
      return result_node->value;
   }
   
   Persona &operator[](int index) {
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
   
   Node* removeNode(Node * node);
   
   template <class Predicate>
   void remove_if(Predicate pred);

private:
   Node *head;
   int num_elems;
   
   Node *nth_node(int n) const;
   void delete_nodes();
   void copy_nodes_from(const ListLinkedDouble &other);
      
};

ListLinkedDouble::Node* ListLinkedDouble::removeNode(Node* node){
	Node* aux = node->next;
    node->next->prev = node->prev;
    node->prev->next = node->next;
	return aux;
}

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

template <class Predicate>
void ListLinkedDouble::remove_if(Predicate pred){
	if(this->empty()) return;

	Node* curr = head->next;
	while(curr != head){
		if(pred(curr->value))
			curr = removeNode(curr);
		else 
			curr = curr->next;
	}
}

void ListLinkedDouble::display(std::ostream &out) const {
   if (head->next != head) {
      out << head->next->value << '\n';
      Node *current = head->next->next;
      while (current != head) {
         out << current->value << '\n';
         current = current->next;
      }
   }
   out << "---";
}

std::ostream &operator<<(std::ostream &out, const ListLinkedDouble &l) {
   l.display(out);
   return out;
}

Persona leerPersona(){
	int age; cin >> age;
	char trailingSpace; cin.get(trailingSpace);
	string name; getline(cin, name);
	return {age, name};
}

ListLinkedDouble leerListaPersonas(int n){
	ListLinkedDouble rv;
	for(int i = 0; i < n; i++)
		rv.push_back(leerPersona());
	return rv;
}

bool resuelveCaso() {
	int n, maxi, mini;
	cin >> n >> mini >> maxi;
	if(n == 0 && mini == 0 && maxi == 0) return false;

	ListLinkedDouble listaPersonas = leerListaPersonas(n);

	listaPersonas.remove_if( [mini,maxi](Persona const& p){return p.getAge() < mini || p.getAge() > maxi;} );

	cout << listaPersonas << '\n';
	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}

