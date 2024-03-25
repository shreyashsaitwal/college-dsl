/**
 * Write a menu driven C++ program to construct a binary search tree by
 * inserting the values in the order given, considering at the beginning with an
 * empty binary search tree. After constructing a binary tree:
 *  1. Insert new node
 *  2. Find number of nodes in longest path from root
 *  3. Minimum data value found in the tree
 *  4. Search a value
 *  5. Print values in ascending and descending order
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
struct Node {
    T thing;
    Node<T> *left;
    Node<T> *right;

    Node(T thing) : thing(thing), left(nullptr), right(nullptr) {}
};

template <typename T>
class BST {
   private:
    Node<T> *root;

    void insert(T thing, Node<T> *&parent) {
        if (!parent) {
            parent = new Node<T>(thing);
        } else {
            if (thing <= parent->thing) {
                insert(thing, parent->left);
            } else {
                insert(thing, parent->right);
            }
        }
    }

    Node<T> *search(T thing, Node<T> *parent) {
        if (!parent) return nullptr;
        if (parent->thing == thing) return parent;

        if (thing < parent->thing) {
            return search(thing, parent->left);
        } else {
            return search(thing, parent->right);
        }
    }

   public:
    BST() : root(nullptr) {}

    void insert(T thing) { insert(thing, this->root); }

    Node<T> *search(T thing) { return search(thing, this->root); }

    vector<Node<T> *> longest_path() {
        if (!root) throw runtime_error("BST is empty");

        vector<Node<T> *> longest_path;
        stack<pair<Node<T> *, vector<Node<T> *>>> stack;
        stack.push({root, longest_path});

        while (!stack.empty()) {
            auto top = stack.top();
            stack.pop();

            Node<T> *node = top.first;
            vector<Node<T> *> curr_path = top.second;
            curr_path.push_back(node);

            if (curr_path.size() > longest_path.size())
                longest_path = curr_path;

            if (node->right) stack.push({node->right, curr_path});
            if (node->left) stack.push({node->left, curr_path});
        }

        return longest_path;
    }

    T minimum() {
        if (!root) throw runtime_error("BST is empty");

        T min;
        stack<Node<T> *> stack;
        stack.push(root);

        while (!stack.empty()) {
            auto node = stack.top();
            stack.pop();
            min = std::min(node->thing, min);

            if (node->right) stack.push(node->right);
            if (node->left) stack.push(node->left);
        }

        return min;
    }
};

int main() {
    BST<int> bst;
    bst.insert(14);
    bst.insert(15);
    bst.insert(19);
    bst.insert(13);
    bst.insert(25);
    bst.insert(5);
    bst.insert(2);
    bst.insert(1);
    bst.insert(0);

    cout << bst.search(19)->thing << endl;
    cout << bst.minimum() << endl;
    cout << bst.longest_path().size() << endl;
    for (auto node : bst.longest_path()) {
        cout << node->thing << " ";
    }
    cout << endl;
}
