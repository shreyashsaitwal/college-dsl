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
    int height;

    Node(Entry<T> entry) : entry(entry), height(0) {}
};

template <typename T>
class Dictionary {
   private:
    Node<T> *root;

    int height(Node<T> *node) {
        if (!node) return -1;
        return node->height;
    }

    Node<T> *right_rot(Node<T> *n) {
        Node<T> *parent = n;
        Node<T> *node = n->left;

        parent->left = node->right;
        node->right = parent;

        parent->height = max(height(parent->left), height(parent->right)) + 1;
        node->height = max(height(node->left), height(node->right)) + 1;

        return node;
    }

    Node<T> *left_rot(Node<T> *n) {
        Node<T> *parent = n;
        Node<T> *node = n->right;

        parent->right = node->left;
        node->left = parent;

        parent->height = max(height(parent->left), height(parent->right)) + 1;
        node->height = max(height(node->left), height(node->right)) + 1;

        return node;
    }

    Node<T> *rotate(Node<T> *node) {
        // Tree is left heavy
        if (height(node->left) - height(node->right) > 1) {
            // Right rotate
            if (height(node->left->left) - height(node->left->right) > 0) {
                return right_rot(node);
            }

            // Left right rotate
            if (height(node->left->left) - height(node->left->right) < 0) {
                node->left = left_rot(node->left);
                return right_rot(node);
            }
        }

        // Tree is right heavy
        if (height(node->left) - height(node->right) < -1) {
            // Left rotation
            if (height(node->right->left) - height(node->right->right) < 0) {
                return left_rot(node);
            }

            // Right left rotation
            if (height(node->right->left) - height(node->right->right) > 0) {
                node->right = right_rot(node->right);
                return left_rot(node);
            }
        }
    
        return node;
    }

    Node<T> *insert(Entry<T> &entry, Node<T> *&parent) {
        if (!parent) {
            parent = new Node<T>(entry);
            return parent;
        }

        if (entry.key > parent->entry.key) {
            parent->right = insert(entry, parent->right);
        } else if (entry.key < parent->entry.key) {
            parent->left = insert(entry, parent->left);
        } else {
            throw runtime_error("ERR: Duplicate key: " + to_string(entry.key));
        }

        parent->height = max(height(parent->left), height(parent->right)) + 1;

        return rotate(parent);
    }

   public:
    Dictionary() : root(nullptr) {}

    void insert(int key, T value) {
        auto entry = Entry<T>{key, value};
        root = insert(entry, root);
    }

    int height() {
        return height(root);
    }
};

int main() {
    Dictionary<string> dict;

    for (int i = 0; i < 1000; i++) {
        dict.insert(i, to_string(i));
    }

    cout << dict.height() << endl;
}
