#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

#define OK "OK"
#define FAIL "FAIL"

size_t str_hash_1(const std::string &data, size_t size) {
    size_t hash = 0;
    size_t arg = 13;

    for (size_t i = 0; data[i] != 0; i++) {
        hash += (hash * arg + data[i]) % size;
    }

    return (hash % size);
}

size_t str_hash_2(const std::string &data, size_t size) {
    size_t hash = 0;
    size_t arg = 113;

    for (size_t i = 0; data[i] != 0; i++) {
        hash += (hash * arg + data[i]) % size;
    }

    return (hash * 2 + 1) % size;
}

template <typename T>
class HashFunc {
public:
    static size_t hash_1(const T &data, size_t size) {
        return data;
    }
    static size_t hash_2(const T &data, size_t size) {
        return data;
    }
};

template<>
class HashFunc<std::string> {
public:
    static size_t hash_1(const std::string &data, size_t size) {
        return str_hash_1(data, size);
    }
    static size_t hash_2(const std::string &data, size_t size) {
        return str_hash_2(data, size);
    }
};

template <class T>
struct EqualsFunc {
    bool operator() (const T& l, const T& r) const { return l == r; }
};

template <typename Key>
class Node {
public:
    Node() : is_null(1) {};

    bool isNull() {
        return is_null;
    }
    Key& getKey() {
        return key;
    }
    bool isDeleted() {
        return is_del;
    }

    void setData(const Key& data) {
        key = data;
        is_del = 0;
        is_null = 0;
    }
    void erase() {
        is_del = 1;
    }

private:
    Key key;
    bool is_del;
    bool is_null;
};

template <typename Key, class Hash = HashFunc<Key>, class Equals = EqualsFunc<Key>>
class HashTable {
public:
    HashTable(Hash hash = Hash(), Equals equals = Equals());
    ~HashTable();

    Key* find(const Key& key);
    bool insert(const Key& key);
    bool erase(const Key& key);
    void debug();
private:
    size_t init_size = 8;
    double fill_factor = 0.75;
    Node<Key>* buckets;
    size_t buckets_count;
    size_t items_count;

    Hash hash;
    Equals equals;

    void grow();
};

int main() {
    char operation = '\0';
    std::string key = "";

    HashTable<std::string, HashFunc<std::string>> hash;
    //hash.debug();
    while (std::cin >> operation >> key) {
        bool res = false;
        switch (operation) {
            case '+':
                res = hash.insert(key);
                break;
            case '-':
                res = hash.erase(key);
                break;
            case '?':
                res = (hash.find(key) != nullptr);
                break;
            default:
                return 0;
        }

        if (res) {
            std::cout << OK << std::endl;
        }
        else {
            std::cout << FAIL << std::endl;
        }
    }

    return 0;
}

template <typename Key, class Hash, class Equals>
HashTable<Key, Hash, Equals>::HashTable(Hash hash, Equals equals)
    : buckets_count(init_size), items_count(0), hash(hash), equals(equals) {
    buckets = new Node<Key>[init_size];
}

template <typename Key, class Hash, class Equals>
HashTable<Key, Hash, Equals>::~HashTable() {
    delete[] buckets;
}

template <typename Key, class Hash, class Equals>
void HashTable<Key, Hash, Equals>::debug() {
    for (size_t i = 0; i < buckets_count; i++) {
        std::cout << i << buckets[i].getKey() << std::endl;
    }
}

/*template <typename Key, class Hash, class Equals>*/
//Key* HashTable<Key, Hash, Equals>::find(const Key& key) {
    //size_t hash_1 = Hash::hash_1(key, buckets_count);
    //size_t hash_2 = Hash::hash_2(key, buckets_count);

    //Node<Key>* cur;
    //for (size_t i = 0; i < buckets_count; i++) {
        //cur = &buckets[hash_1];

        //if (!cur->isNull()) {
            //if (!cur->isDeleted() && equals(cur->getKey(), key)) {
                //return &cur->getKey();
            //}
        //}
        //else {
            //return nullptr;
        //}

        //hash_1 = (hash_1 + i * hash_2) % buckets_count;
    //}

    //return nullptr;
//}

template <typename Key, class Hash, class Equals>
Key* HashTable<Key, Hash, Equals>::find(const Key& key) {
    size_t hash_1 = Hash::hash_1(key, buckets_count);
    size_t hash_2 = Hash::hash_2(key, buckets_count);

    for (size_t i = 0; i < buckets_count; i++) {

        if (buckets[hash_1].isNull()) {
            return nullptr;
        }

        if (!buckets[hash_1].isDeleted() && equals(buckets[hash_1].getKey(), key)) {
            return &buckets[hash_1].getKey();
        }

        hash_1 = (hash_1 + i * hash_2) % buckets_count;
    }

    return nullptr;
}


template <typename Key, class Hash, class Equals>
bool HashTable<Key, Hash, Equals>::insert(const Key& key) {
    if (((double) items_count) >= fill_factor * (double) buckets_count) {
        grow();
    }

    size_t hash_1 = Hash::hash_1(key, buckets_count);
    size_t hash_2 = Hash::hash_2(key, buckets_count);

    int del_idx = -1;
    for (size_t i = 0; i < buckets_count; i++) {
        if (buckets[hash_1].isNull()) {
            break;
        }

        if (!buckets[hash_1].isDeleted() && equals(buckets[hash_1].getKey(), key)) {
            return false;
        }
        if (buckets[hash_1].isDeleted() && (del_idx < 0)) {
            del_idx = hash_1;
        }


        hash_1 = (hash_1 + i * hash_2) % buckets_count;
    }

    if (del_idx != -1) {
        buckets[del_idx].setData(key);
        items_count++;

        return true;
    }
    else {
        buckets[hash_1].setData(key);
        items_count++;

        return true;
    }

    return false;
}


template <typename Key, class Hash, class Equals>
bool HashTable<Key, Hash, Equals>::erase(const Key& key) {
/*    if (!find(key)) {*/
        //return false;
    //}

    size_t hash_1 = Hash::hash_1(key, buckets_count);
    size_t hash_2 = Hash::hash_2(key, buckets_count);


    for (size_t i = 0; i < buckets_count; i++) {
        if (buckets[hash_1].isNull()) {
            return false;
        }

        if (!buckets[hash_1].isDeleted() && equals(buckets[hash_1].getKey(), key)) {
            buckets[hash_1].erase();
            items_count--;
            return true;
        }

        hash_1 = (hash_1 + i * hash_2) % buckets_count;
    }

/*    Node<Key>* cur;*/
    //for (size_t i = 0; i < buckets_count; i++) {
        //cur = &buckets[hash_1];

        //if (equals(cur->getKey(), key)) {
            //cur->erase();
            //items_count--;

            //return true;
        //}

        //hash_1 = (hash_1 + i * hash_2) % buckets_count;
    //}

    return false;
}

template <typename Key, class Hash, class Equals>
void HashTable<Key, Hash, Equals>::grow() {
    Node<Key>* old_buckets = buckets;
    size_t old_buckets_count = buckets_count;
    items_count = 0;

    buckets_count *= 2;
    buckets = new Node<Key>[buckets_count];

    for (size_t i = 0; i < old_buckets_count; i++) {
        Node<Key>* cur = &old_buckets[i];

        if (!cur->isNull() && !cur->isDeleted()) {
            insert(cur->getKey());
        }
    }

    delete[] old_buckets;
}
