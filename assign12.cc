#include <iostream>

using namespace std;

template <typename T>
struct Node {
    T stuff;
    Node<T> *left;
    Node<T> *right;

    Node(T stuff) : stuff(stuff), left(nullptr), right(nullptr) {}
};

template <typename T>
class Heap {
   private:
    Node<T> *root;

    Node<T> *insert(T stuff, Node<T> *&node) {
        
    }
};
