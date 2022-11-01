#include <cassert>
#include <iostream>
using namespace std;

template <typename Elem>
class Dequeue
{
private:
    struct Node
    {
        Elem value;
        Node *next;
        Node *prev;
    };

public:
    Dequeue()
    {
        head = new Node;
        head->next = head;
        head->prev = head;
    }

    Dequeue(const Dequeue &other) : Dequeue() { copy_nodes_from(other); }

    ~Dequeue() { delete_nodes(); }

    void push_front(const Elem &elem)
    {
        Node *new_node = new Node{elem, head->next, head};
        head->next->prev = new_node;
        head->next = new_node;
    }

    void push_back(const Elem &elem)
    {
        Node *new_node = new Node{elem, head, head->prev};
        head->prev->next = new_node;
        head->prev = new_node;
    }

    void pop_front()
    {
        assert(head->next != head);
        Node *target = head->next;
        head->next = target->next;
        target->next->prev = head;
        delete target;
    }

    void pop_back()
    {
        assert(head->next != head);
        Node *target = head->prev;
        target->prev->next = head;
        head->prev = target->prev;
        delete target;
    }

    bool empty() const { return head->next == head; };

    const Elem &front() const
    {
        assert(head->next != head);
        return head->next->value;
    }

    Elem &front()
    {
        assert(head->next != head);
        return head->next->value;
    }

    const Elem &back() const
    {
        assert(head->next != head);
        return head->prev->value;
    }

    Elem &back()
    {
        assert(head->next != head);
        return head->prev->value;
    }

    Dequeue &operator=(const Dequeue &other)
    {
        if (this != &other)
        {
            delete_nodes();
            head = new Node;
            head->next = head->prev = head;
            copy_nodes_from(other);
        }
        return *this;
    }

    void entremezclar(Dequeue &that)
    {
        Node* a = this->head->next;
        Node* b = that.head->next;
        while(a != this->head && b != that.head){
            b = b->next;
            a = insert_after(a,b->prev);
            a = a->next;
        }

        a = a->prev;
        while(b != that.head){
            // Entonces, a == this.head->prev
            b = b->next;
            a = insert_after(a,b->prev);
        }
    }

    // void entremezclar(Dequeue &that)
    // {
    //     Dequeue nueva;
    //     Node a = this.head->next;
    //     Node b = that.head->next;
    //     bool turnA = true;
    //     while (a != this.head && b != that.head)
    //     {
    //         if (turnA)
    //         {
    //             nueva.push_back(a.elem);
    //             a = a->next;
    //         }
    //         else
    //         {
    //             nueva.push_back(b.elem);
    //             b = b->next;
    //         }
    //     }
    //     while (a != this.head)
    //     {
    //         nueva.push_back(a.elem)
    //         a = a->next;
    //     }
    //     while (a != that.head)
    //     {
    //         nueva.push_back(b.elem)
    //         b = b->next;
    //     }
    //     this = nueva;
    //     that = Dequeue();
    // }

    void display(ostream & out) const {
        Node* curr = head->next;
        if(curr != head) out << curr->value;
        curr = curr->next;
        while(curr != head){
            out << " " << curr->value;
            curr = curr->next;
        }
    }

private:
    Node *head;

    void delete_nodes();
    void copy_nodes_from(const Dequeue &other);

    void erase(Node* n){
        n->prev->next = n->next;
        n->next->prev = n->prev;
    }

    Node* insert_after(Node* pos, Node* n){
        erase(n); // Quitamos n de la lista en la que estaba antes
        
        Node* sig = pos->next; // El siguiente elemento de la lista
        
        sig->prev = pos->next = n; // Colocamos n entre medias
        n->next = sig; // Que el proximo de n sea sig
        n->prev = pos; // Que el previo a n sea pos
        return n; 
    }
};

template <typename Elem = int>
ostream & operator<<(ostream & out, Dequeue<Elem> const& d){
    d.display(out);
    return out;
}

template <typename Elem>
void Dequeue<Elem>::delete_nodes()
{
    Node *current = head->next;
    while (current != head)
    {
        Node *target = current;
        current = current->next;
        delete target;
    }

    delete head;
}

template <typename Elem>
void Dequeue<Elem>::copy_nodes_from(const Dequeue &other)
{
    Node *current_other = other.head->next;
    Node *last = head;

    while (current_other != other.head)
    {
        Node *new_node = new Node{current_other->value, head, last};
        last->next = new_node;
        last = new_node;
        current_other = current_other->next;
    }
    head->prev = last;
}

#include <iostream>
using namespace std;

void test1(){

    Dequeue<int> d,e;
    d.push_back(1);
    d.push_back(3);
    d.push_back(5);
    d.push_back(7);
    d.push_back(9);
    d.push_back(11);

    e.push_back(2);
    e.push_back(4);
    e.push_back(6);
    e.push_back(8);
    e.push_back(10);
    e.push_back(12);

    d.entremezclar(e);
    cout << d << '\n' << e << '\n';
    cout << "Test 1 completed\n";
}

void test2(){
    Dequeue<int> d,e;
    d.push_back(1);
    d.push_back(3);
    d.push_back(5);
    d.push_back(7);

    e.push_back(2);
    e.push_back(4);
    e.push_back(6);
    e.push_back(8);
    e.push_back(10);
    e.push_back(12);

    d.entremezclar(e);
    cout << d << '\n' << e << '\n';
    cout << "Test 2 completed\n";
}

void test3(){
    Dequeue<int> d,e;
    d.push_back(1);
    d.push_back(3);
    d.push_back(5);
    d.push_back(7);
    d.push_back(9);
    d.push_back(11);

    e.push_back(2);
    e.push_back(4);
    e.push_back(6);
    e.push_back(8);

    d.entremezclar(e);
    cout << d << '\n' << e << '\n';
    cout << "Test 3 completed\n";
}

int main()
{
    int t; cin >> t;
    int n, aux; 
    while(t--){
        Dequeue<int> a;
        cin >> n;
        while(n--) {
            cin >> aux;
            a.push_back(aux);
        }


        Dequeue<int> b;
        cin >> n;
        while(n--) {
            cin >> aux;
            b.push_back(aux);
        }

        a.entremezclar(b);
        cout << a << '\n';
    }
}