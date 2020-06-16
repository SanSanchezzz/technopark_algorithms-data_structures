#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include <stack>

template <class T>
class DefaultComparator {
public:
    bool operator() (const T& l, const T& r) {
        return l < r;
    }
};

template <typename T, class Comporator = DefaultComparator<T>>
class Tree {
    struct Node {
        Node* parent;
        Node* left;
        Node* right;

        T data;

        Node(Node* parent, const T& data) : parent(parent), left(nullptr), right(nullptr), data(data) {}

        static Node* getParent(Node* cur) {return cur->parent;}
        static Node* getLeft(Node* cur) {return cur->left;}
        static Node* getRight(Node* cur) {return cur->right;}
        static T getData(Node* cur) {return cur->data;}
    };

public:
    Tree(Comporator comp = Comporator()) : root(nullptr), comp(comp) {}
    ~Tree() {}


    void insert(const T& val) {
        if (!root) {
            root = new Node(nullptr, val);
        }
        Node* cur = root;

        while (cur) {
           if (cur->data <= val) {
                cur = Node::getRight(cur);
            }
            else {
                cur = Node::getLeft(cur);
            }
        }

        if (cur->data <= val) {
            cur->right = new Node(cur, val);
        }
        else {
            cur->left = new Node(cur, val);
        }
    }

    Node* stepInOrder(Node* cur) {
        if (Node::getRight(cur)) {
            while (Node::getLeft(cur)) {
                cur = Node::getLeft(cur);
            }

            return cur;
        }

        while (Node::getParent(cur) && Node::getRight(Node::getParent(cur)) == cur) {
            cur = Node::getParent(cur);
        }

        return Node::getParent(cur);
    }

    void inOrder() {
        Node* cur = root;
        if (cur == nullptr) {
        
        }
    std::cout << cur->data <<"FLAG\n";
        while (Node::getLeft(cur)) {
            cur = Node::getLeft(cur);
        }

        std::cout << cur->data << cur->parent->data;

        while (stepInOrder(cur)) {
        std::cout << "step\n";
            cur = stepInOrder(cur);
            std::cout << cur->data;
        }
        std::cout << "End\n";
    }

private:
    Node* root;

    Comporator comp;
};

int main() {
    Tree<int> tree;

    int num, val;
    std::cin >> num;
    for (int i = 0; i < num; i++) {
        std::cin >> val;
        tree.insert(val);
    }
    tree.inOrder();

    return 0;
}
