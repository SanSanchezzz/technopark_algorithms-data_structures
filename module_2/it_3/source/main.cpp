/*В одной военной части решили построить в одну шеренгу по росту.
 * Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя,
 * а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги.
 * Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены
 * по росту – сначала самые высокие, а в конце – самые низкие. За расстановку
 * солдат отвечал прапорщик, который заметил интересную особенность – все солдаты
 * в части разного роста. Ваша задача состоит в том, чтобы помочь прапорщику правильно
 * расставлять солдат, а именно для каждого приходящего солдата указывать,
 * перед каким солдатом в строе он должен становится.
 * Требуемая скорость выполнения команды - O(log n).*/

//Формат ввода
//Первая строка содержит число N – количество команд (1 ≤ N ≤ 90 000).
//В каждой следующей строке содержится описание команды: число 1 и X если
//солдат приходит в строй (X – рост солдата, натуральное число до 100 000 включительно)
//и число 2 и Y если солдата, стоящим в строе на месте Y надо удалить из строя.
//Солдаты в строе нумеруются с нуля.

//Формат вывода
/*На каждую команду 1 (добавление в строй) вы должны выводить число K – номер позиции,
 * на которую должен встать этот солдат (все стоящие за ним двигаются назад).*/

#include <iostream>
#include <stack>

template <class T>
class DefaultComparator {
public:
    int operator() (const T& l, const T& r) {
        if (l < r) return -1;
        if (l > r) return 1;
        return 0;
    }
};

template <typename Key, class Comporator = DefaultComparator<Key>>
class AVLTree {
    struct Node {
        Node(const Key& key) : left(nullptr), right(nullptr), height(1), count_childs(1), key(key) {}
        Node* left;
        Node* right;

        size_t height;
        size_t count_childs;

        Key key;
    };

public:
    AVLTree(Comporator comp = Comporator()) : root(nullptr), comp(comp), items_count(0) {}
    ~AVLTree() {
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

    size_t insert(const Key& key) {
        size_t position = 0;
        root = insert_aux(root, key, position);

        return position;
    }

    void erase(int position) {
        size_t cur_position = 0;
        root = erase_aux(root, position, cur_position);
    }

private:
    Node* root;
    Comporator comp;
    size_t items_count;

    size_t get_count_childs(Node* node) {
        if (node) {
            return node->count_childs;
        }

        return 0;
    }

    void set_count_childs(Node* node) {
        node->count_childs = get_count_childs(node->left) + get_count_childs(node->right) + 1;
    }

    Node* rotate_right(Node* node) {
        Node* q = node->left;
        node->left = q->right;
        q->right = node;

        fix_height(node);
        fix_height(q);

        set_count_childs(node);
        set_count_childs(q);

        return q;
    }

    Node* rotate_left(Node* node) {
        Node* p = node->right;
        node->right = p->left;
        p->left = node;

        fix_height(node);
        fix_height(p);

        set_count_childs(node);
        set_count_childs(p);

        return p;
    }

    Node* balance(Node* node) {
        fix_height(node);

        int bf = balance_factor(node);
        if (bf == 2) {
            if (balance_factor(node->right) < 0) {
                node->right = rotate_right(node->right);
            }
            return rotate_left(node);
        }
        else if (bf == -2) {
            if (balance_factor(node->left) > 0) {
                node->left = rotate_left(node->left);
            }
            return rotate_right(node);
        }

        return node;
    }

    void fix_height(Node* node) {
        size_t hl = height(node->left);
        size_t hr = height(node->right);

        node->height = std::max(hl, hr) + 1;
    }

    int balance_factor(Node* node) {
        return height(node->right) - height(node->left);
    }

    int height(Node* node) {
        if (!node) {
            return 0;
        }

        return node->height;
    }

    Node* insert_aux(Node* node, const Key& key, size_t& position) {
        if (!node) {
            items_count++;
            return new Node(key);
        }
        node->count_childs++;

        if (comp(key, node->key) == -1) {
            position += get_count_childs(node->right) + 1;

            node->left = insert_aux(node->left, key, position);
        }
        else {
            node->right = insert_aux(node->right, key, position);
        }

        return balance(node);
    }

    //Node* find_min(Node* node) {
        //if (!node->left) {
            //return node;
        //}
        //return find_min(node->left);
    //}

    Node* remove_min(Node* node, Node*& tmp) {
        if (!node->left) {
            tmp = node;
            return node->right;
        }

        node->left = remove_min(node->left, tmp);
        node->count_childs--;

        return balance(node);
    }

    Node* erase_aux (Node* node, const size_t position, size_t& cur_position) {
        if (!node) {
            return nullptr;
        }

        size_t count_right_childs = get_count_childs(node->right);
        if (position > count_right_childs + cur_position) {
            cur_position += count_right_childs + 1;
            node->left = erase_aux(node->left, position, cur_position);
        }
        else if (position < count_right_childs + cur_position) {
            node->right = erase_aux(node->right, position, cur_position);
        }
        else {
            items_count--;

            Node* left = node->left;
            Node* right = node->right;
            delete node;

            if (!right) {
                return left;
            }

            Node* min_node;
            Node* tmp = remove_min(right, min_node);
            min_node->right = tmp;
            min_node->left = left;
            set_count_childs(min_node);

            return balance(min_node);
        }
        node->count_childs--;
        return balance(node);
    }
};

int main() {
    int num;
    int com, val;
    int res;
    AVLTree<int> tree;

    std::cin >> num;
    for (int i = 0; i < num; i++) {
        std::cin >> com >> val;

        switch(com) {
            case 1:
                res = tree.insert(val);
                std::cout << res << std::endl;
                break;
            case 2:
                tree.erase(val);
                break;
            default:
                return 0;
        }

    }
}
