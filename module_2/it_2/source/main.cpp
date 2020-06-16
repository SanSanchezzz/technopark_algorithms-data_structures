//Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
//Требуется построить бинарное дерево, заданное наивным порядком вставки.
//Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
//Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.

#include <iostream>
#include <stack>
#include <functional>

template <class T>
class DefaultComparator {
public:
    bool operator() (const T& l, const T& r) {
        return l <= r;
    }
};

template <typename Key, class Comporator = DefaultComparator<Key>>
class Tree {
    class Node {
    public:
        Node(Key key)
            : left(nullptr), right(nullptr), key(key) {}

        Node* left;
        Node* right;

        Key key;
    };
public:
    Tree(Comporator comp = Comporator()) : root(nullptr), items_count(0), comp(comp) {}
    ~Tree() {
        if (!root) {
            return;
        }

        std::stack<Node*> stack;
        Node* cur = root;
        while (cur) {
            if (cur->right) {
                stack.push(cur->right);
            }
            if (cur->left) {
                stack.push(cur->left);
            }
            delete cur;
            cur = nullptr;
            if (!stack.empty()) {
                cur = stack.top();
                stack.pop();
            }
        }
    }

    void insert(const Key& key) {
        if (!root) {
            root = new Node(key);
            items_count++;
            return;
        }

        Node* cur = root;
        while (1) {
            if (comp(cur->key, key)) {
                if (cur->right) {
                    cur = cur->right;
                }
                else {
                    cur->right = new Node(key);
                    items_count++;
                    return;
                }
            }
            else {
                if (cur->left) {
                    cur = cur->left;
                }
                else {
                    cur->left = new Node(key);
                    items_count++;
                    return;
                }
            }
        }
    }

    static void printNode(Node* node) {
        std::cout << node->key << " ";
    }

    //void printInOrderTraversal() {
        //inOrderTraversal(&printNode);
    //}

    void inOrderTraversal(void (*func)(Node*)) {
        if (!root) {
            return;
        }

        std::stack<Node*> stack;
        Node* cur = root;
        while (cur != nullptr || !stack.empty()) {
            if (cur != nullptr) {
                stack.push(cur);
                cur = cur->left;
            }
            else {
                cur = stack.top();
                stack.pop();
                func(cur);
                //std::cout << cur->key << " ";
                cur = cur->right;
            }
        }
    }

private:
    Node* root;
    size_t items_count;
    Comporator comp;
};

int main () {
    int num, val;
    Tree<int> tree;

    std::cin >> num;
    for (int i = 0; i < num; i++) {
        std::cin >> val;
        tree.insert(val);
    }
    tree.inOrderTraversal(&Tree<int>::printNode);
    std::cout << std::endl;

    return 0;
}
