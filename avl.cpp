#include <iostream>
#include <string>

using namespace std;

class AVL {
public:
	
	AVL()
		:root_(nullptr)
	{}
	
	~AVL() = default;
	
	void print() {
		inorder(root_);
	}
	
	bool find(int val) {
		return find(val, root_);
	}
	
	void insert(int val) {
		root_ = this->insert(val, root_);
	}
	
	void remove(int val) {
		root_ = this->remove(val, root_);
	}
	
	void removeMin() {
		root_ = this->removeMin(root_);
	}
	
	void removeMax() {
		root_ = this->removeMax(root_);
	}

private:
	class Node {
	public:
		Node(int val, Node *left=nullptr, Node *right=nullptr)
			: val(val)
			, left(left)
			, right(right)
			, height(1)
		{}
		
		int val;
		Node *left;
		Node *right;
		int height;
	};
	
	Node *root_;
	
	void inorder(Node *x) {
		if (x == nullptr) {
			return;
		}
		std::cout << ((x->left == nullptr) ? "x" : to_string(x->left->val)) << " " 
					<< x->val << " "
					<< ((x->right == nullptr) ? "x" : to_string(x->right->val)) << endl;
		inorder(x->left);
		inorder(x->right);
	}
	
	bool find(int val, Node *x) {
		if (x == nullptr) {
			return false;
		}
		if (val < x->val) {
			return find(val, x->left);
		}
		if (val > x->val) {
			return find(val, x->right);
		}
		return true;
	}
	
	Node *getMin(Node *x) {
		return (x->left == nullptr) ? x : getMin(x->left);
	}
	
	Node *getMax(Node *x) {
		return (x->right == nullptr) ? x : getMax(x->right);
	}
	
	Node *insert(int val, Node *x) {
		if (x == nullptr) return new Node(val);
		if (val < x->val) {
			x->left = insert(val, x->left);
		}
		if (val > x->val) {
			x->right = insert(val, x->right);
		}
		return balance(x);
	}
	
	Node *removeMin(Node *x) {
		if (x->left == nullptr) {
			return x->right;
		}
		x->left = removeMin(x->left);
		return balance(x);
	}
	
	Node *removeMax(Node *x) {
		if (x->right == nullptr) {
			return x->left;
		}
		x->right = removeMax(x->right);
		return balance(x);
	}
	
	Node *remove(int val, Node *x) {
		if (x == nullptr) {
			return x;
		}
		if (val < x->val) {
			x->left = remove(val, x->left);
		} else if (val > x->val) {
			x->right = remove(val, x->right);
		} else {
			Node *l = x->left;
			Node *r = x->right;
			delete x;
			if (r == nullptr) return l;
			Node *next = getMin(r);
			next->right = removeMin(r);
			next->left = l;
			return balance(next);
		}
		return balance(x);
	}
	
	Node *balance(Node *x) {
		fixHeight(x);
		if (bf(x) == -2) {
			if (bf(x->right) > 0) {
				x->right = rR(x->right);
			}
			return rL(x);
		}
		if (bf(x) == 2) {
			if (bf(x->left) < 0) {
				x->left = rL(x->left);
			}
			return rR(x);
		}
		return x;
	}
	
	int height(Node *node) {
		return (node == nullptr) ? 0 : node->height;
	}
	
	void fixHeight(Node *x) {
		int hl = height(x->left);
		int hr = height(x->right);
		x->height = 1 + max(hl, hr);
	}
	
	int bf(Node *node) {
		return (node == nullptr) ? 0 : height(node->left) - height(node->right);
	}
	
	Node *rL(Node *a) {
		Node *b = a->right;
		a->right = b->left;
		b->left = a;
		fixHeight(a);
		fixHeight(b);
		return b;
	}
	
	Node *rR(Node *b) {
		Node *a = b->left;
		b->left = a->right;
		a->right = b;
		fixHeight(b);
		fixHeight(a);
		return a;
	}
};

int main() {
	AVL avl;
	avl.insert(10);
	cout << avl.find(10) << endl;
}
