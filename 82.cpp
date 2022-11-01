#include <cassert>
#include <vector>
#include <iostream>
#include <memory>

template <class T> class BinTree {
public:
  BinTree() : root_node(nullptr) {}

  BinTree(const T &elem)
      : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

  BinTree(const BinTree &left, const T &elem, const BinTree &right)
      : root_node(std::make_shared<TreeNode>(left.root_node, elem,
                                             right.root_node)) {}

  bool empty() const { return root_node == nullptr; }

  const T &root() const {
    assert(root_node != nullptr);
    return root_node->elem;
  }

  BinTree left() const {
    assert(root_node != nullptr);
    BinTree result;
    result.root_node = root_node->left;
    return result;
  }

  BinTree right() const {
    assert(root_node != nullptr);
    BinTree result;
    result.root_node = root_node->right;
    return result;
  }

  void display(std::ostream &out) const { display_node(root_node, out); }

private:
  // Las definiciones de TreeNode y NodePointer dependen recursivamente
  // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
  // para que el compilador sepa, cuando analice la definición de NodePointer,
  // que TreeNode va a ser definida más adelante.

  struct TreeNode;
  using NodePointer = std::shared_ptr<TreeNode>;

  struct TreeNode {
    TreeNode(const NodePointer &left, const T &elem, const NodePointer &right)
        : elem(elem), left(left), right(right) {}

    T elem;
    NodePointer left, right;
  };

  NodePointer root_node;

  static void display_node(const NodePointer &root, std::ostream &out) {
    if (root == nullptr) {
      out << ".";
    } else {
      out << "(";
      display_node(root->left, out);
      out << " " << root->elem << " ";
      display_node(root->right, out);
      out << ")";
    }
  }
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const BinTree<T> &tree) {
  tree.display(out);
  return out;
}

template <typename T> BinTree<T> read_tree(std::istream &in) {
  char c;
  in >> c;
  if (c == '.') {
    return BinTree<T>();
  } else {
    assert(c == '(');
    BinTree<T> left = read_tree<T>(in);
    T elem;
    in >> elem;
    BinTree<T> right = read_tree<T>(in);
    in >> c;
    assert(c == ')');
    BinTree<T> result(left, elem, right);
    return result;
  }
}

#include <iostream>
using namespace std;

template <typename T>
int numero_nodos(const BinTree<T> &tree) {
	return (tree.empty()? 0 : numero_nodos(tree.left()) + numero_nodos(tree.right()) + 1);
}

template <typename T>
int altura(const BinTree<T> &tree) {
	return (tree.empty()? 0 : max( altura(tree.left()), altura(tree.right()) )+ 1);
}

int suma_nodos(const BinTree<int> &tree) {
	return (tree.empty()? 0 : suma_nodos(tree.left()) + suma_nodos(tree.right()) + tree.root());
}

bool contiene_pares(const BinTree<int> &tree) {
	return (tree.empty()? 0 : tree.root()%2 == 0 || contiene_pares(tree.left()) || contiene_pares(tree.right()));
}

template <typename T>
int numero_hojas(const BinTree<T> &tree){
	if(tree.empty()) return 0;
	else{
		int rv1 = numero_hojas(tree.left()),
			rv2 = numero_hojas(tree.right());
		if(rv1 == 0 && rv2 == 0) return 1;
		else return rv1 + rv2;
	}
}

template <typename T>
bool balanceado(const BinTree<T> &tree){
	return _balanceado(tree).first;
}
template <typename T>
pair<bool, int> _balanceado(const BinTree<T> &tree){
	if(tree.empty()) return {true,0};
	else{
		auto rv1 = _balanceado(tree.left()),
			rv2 = _balanceado(tree.right());
		return {rv1.first && rv2.first && abs(rv1.second - rv2.second) <= 1, max(rv1.second,rv2.second)};
	}
}

template <typename T>
bool completo(const BinTree<T> &tree){
	return _completo(tree).first;
}
template <typename T>
pair<bool, int> _completo(const BinTree<T> &tree){
	if(tree.empty()) return {true,0};
	else{
		auto rv1 = _completo(tree.left()),
			rv2 = _completo(tree.right());
		return {rv1.first && rv2.first && rv1.second == rv2.second, 1+max(rv1.second,rv2.second)};
	}
}

template <typename T>
// 4, 2, 1, 3, 5, 7
// 0 4
// 1 4		  →{{1} 2 {3}}
// 2 2  → {1}
// 3 2  → {3}
// 4 4 → {5}
BinTree<T> f(vector<T> const& preorden, int &idx, T last){
	T const& curr = preorden[idx];
	if(idx + 1 >= (int)preorden.size()) 
		return {curr};
	else if (preorden[idx+1] > curr) {
		if(preorden[idx + 1] < last) return {{}, curr, {preorden[++idx]}};
		if(curr > last) { // Descenso
			return {{},curr, f(preorden, ++idx, curr)};
		}
		return {curr};
	}
	else{
		BinTree<T> left = f(preorden, ++idx, curr);
		BinTree<T> right= f(preorden, ++idx, last);
		return {left, curr, right};
	}
}

template <typename T>
BinTree<T> constr_ABB_con_preorden(vector<T> const& preorden){
	if(preorden.size() == 0) return {};
	else{
		int idx = 0;
		return f<T>(preorden, idx, preorden.front());
	}
}


bool resuelveCaso(){
	int n; cin >> n;
	if(!cin) return false;

	vector<int> preorden(n);
	for(auto & e : preorden) cin >> e;

	BinTree<int> t = constr_ABB_con_preorden<int>(preorden);
	cout << t << '\n';

	return true;
}

int main() {
	while(resuelveCaso());
	return 0;
}
