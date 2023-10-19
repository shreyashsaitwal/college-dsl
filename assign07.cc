#include <iostream>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T> *link;
};

template <typename T>
class LinkedList {
   private:
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
    Node<T> *current = nullptr;
    int _length = 0;

   public:
    const int &length;

    LinkedList() : length(_length) {}

    bool has_next() { return current->link != nullptr; }

    Node<T> *next() {
        if (has_next()) {
            Node<T> *temp = current;
            current = current->link;
            return temp;
        }
        return nullptr;
    }

    bool is_empty() { return head == nullptr; }

    void print() {
        if (is_empty()) return;
        Node<T> *og_curr = current;
        current = head;
        do {
            cout << to_string(current->data) << endl;
        } while (next() != nullptr);
        current = og_curr;
    }

    Node<T> *node_at(int idx) {
        if (idx == 0)
            return head;
        else if (idx == (_length - 1))
            return tail;

        Node<T> *res = nullptr;
        Node<T> *og_curr = current;
        current = head;

        int count = 0;
        while (count < _length) {
            if (count == idx) {
                res = current;
                break;
            }
            next();
            count++;
        }

        current = og_curr;
        return res;
    }

    void insert_at(int idx, T element) {
        Node<T> *new_node = new Node<T>{element, nullptr};
        Node<T> *curr_node_at_idx = node_at(idx);

        if (is_empty()) {
            head = tail = current = new_node;
        } else if (idx >= _length) {
            tail->link = new_node;
            tail = new_node;
        } else {
            new_node->link = curr_node_at_idx;
            if (idx == 0) {
                head = new_node;
            } else {
                Node<T> *node_at_prev_idx = node_at(idx - 1);
                node_at_prev_idx->link = new_node;
            }
        }

        if (current == curr_node_at_idx) {
            current = new_node;
        }
        _length++;
    }

    void remove_at(int idx) {
        if (is_empty() || idx >= _length) return;

        Node<T> *node_at_idx = node_at(idx);
        if (idx == 0) {
            head = node_at_idx->link;
        } else {
            Node<T> *node_at_prev_idx = node_at(idx - 1);
            node_at_prev_idx->link = node_at_idx->link;
        }

        if (current == node_at_idx) {
            if (idx == _length - 1) {
                current = head;
            } else {
                current = node_at(idx);
            }
        }

        _length--;
        delete node_at_idx;
    }
};

int main() {
    LinkedList<int> ll;
    for (int i = 0; i < 10; i++) ll.insert_at(i, i);
    ll.print();
    ll.remove_at(3);
    cout << endl;
    ll.print();
    ll.remove_at(8);
    cout << endl;
    ll.print();
    ll.remove_at(0);
    cout << endl;
    ll.print();
}
