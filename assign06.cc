#include <iostream>

using namespace std;

template <typename T>
struct Entry {
    int key;
    T value;
};

template <typename T>
struct Node {
    Entry<T> entry;
    Node<T> *left;
    Node<T> *right;

    Node(Entry<T> entry) : entry(entry), left(nullptr), right(nullptr) {}
};

template <typename T>
class Dictionary {
   private:
    Node<T> *root = nullptr;

    void insert(Entry<T> entry, Node<T> *&parent) {
        if (!parent) {
            auto node = new Node<T>(entry);
            parent = node;
            return;
        }

        if (entry.key > parent->entry.key) {
            return insert(entry, parent->right);
        } else if (entry.key < parent->entry.key) {
            return insert(entry, parent->left);
        } else {
            throw runtime_error("Keys must be unique; key " +
                                to_string(entry.key) + " already exist.");
        }
    }

    T find(int key, Node<T> *&node) {
        if (!node) {
            throw runtime_error("Key not found; key: " + to_string(key));
        }

        if (node->entry.key == key) {
            return node->entry.value;
        }

        if (key > node->entry.key) {
            return find(key, node->right);
        } else {
            return find(key, node->left);
        }
    }

    Node<T> *remove(int key, Node<T> *&node) {
        if (!node) return nullptr;

        if (key > node->entry.key) {
            node->right = remove(key, node->right);
        } else if (key < node->entry.key) {
            node->left = remove(key, node->left);
        }

        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        }
        if (!node->left) {
            auto right = node->right;
            delete node;
            return right;
        }
        if (!node->right) {
            auto left = node->left;
            delete node;
            return left;
        }

        auto inorder_succ = min_node(node->right);
        node->entry = inorder_succ->entry;
        node->right = remove(inorder_succ->entry.key, node->right);
        return node;
    }

    Node<T> *min_node(Node<T> *node) {
        auto current = node;
        while (current->left) {
            current = current->left;
        }
        return current;
    }

    void print_asc(Node<T> *&node) {
        if (!node) return;
        print_asc(node->left);
        cout << "(" << node->entry.key << ": " << node->entry.value << ") ";
        print_asc(node->right);
    }

    void print_desc(Node<T> *&node) {
        if (!node) return;
        print_desc(node->right);
        cout << "(" << node->entry.key << ": " << node->entry.value << ") ";
        print_desc(node->left);
    }

   public:
    void insert(int key, T value) {
        auto entry = Entry<T>{key, value};
        return insert(entry, root);
    }

    T find(int key) { return find(key, root); }

    void remove(int key) { remove(key, root); }

    void print(bool ascending = true) {
        if (ascending)
            print_asc(root);
        else
            print_desc(root);
        cout << endl;
    }
};

int main() {
    Dictionary<string> dict;
    dict.insert(3, "hello3");
    dict.insert(2, "hello2");
    dict.insert(1, "hello");
    dict.insert(4, "hello4");
    dict.insert(5, "hello5");

    cout << dict.find(2) << endl;

    dict.remove(3);
    cout << dict.find(1) << endl;

    dict.print(false);

    return 1;
}
