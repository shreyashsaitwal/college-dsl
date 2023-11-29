/**
 * Simulation of pizza parlour: Pizza polour accepting max M orders. Orders are
 * served on a first come first basis. Order once placed cannot be cancelled.
 *
 * Write a C++ program to simulate the system by using a queue.
 */
#include <iostream>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T> *next;
};

template <typename T>
class Queue {
   private:
    Node<T> *front;
    Node<T> *rear;
    int size;
    int capacity;

   public:
    Queue(int capacity) {
        this->capacity = capacity;
        this->size = 0;
        this->front = NULL;
        this->rear = NULL;
    }

    bool is_empty() { return this->size == 0; }

    bool is_full() { return this->size == this->capacity; }

    void enqueue(T data) {
        if (this->is_full()) {
            throw "Queue is full";
        }
        Node<T> *node = new Node<T>;
        node->data = data;
        node->next = nullptr;
        if (this->is_empty()) {
            this->front = node;
            this->rear = node;
        } else {
            this->rear->next = node;
            this->rear = node;
        }
        this->size++;
    }

    T dequeue() {
        if (this->is_empty()) {
            throw "Queue is empty";
        }
        Node<T> *node = this->front;
        T data = node->data;
        this->front = this->front->next;
        delete node;
        this->size--;
        return data;
    }

    T peek() {
        if (this->is_empty()) {
            throw "Queue is empty";
        }
        return this->front->data;
    }

    void display() {
        if (this->is_empty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        Node<T> *node = this->front;
        while (node != NULL) {
            cout << "- " << node->data << endl;
            node = node->next;
        }
        cout << endl;
    }
};

int main() {
    int capacity;
    cout << "Enter capacity: ";
    cin >> capacity;
    Queue<string> queue(capacity);
    while (true) {
        cout << "1. Place order" << endl;
        cout << "2. Serve order" << endl;
        cout << "3. Display orders" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: {
                string order;
                cout << "- What do you want to order? ";
                cin >> order;
                try {
                    queue.enqueue(order);
                } catch (const char *msg) {
                    cout << msg << endl;
                }
                break;
            }
            case 2: {
                try {
                    string order = queue.dequeue();
                    cout << "- Serving order: " << order << endl;
                } catch (const char *msg) {
                    cout << msg << endl;
                }
                break;
            }
            case 3: {
                queue.display();
                break;
            }
            case 4: {
                return 0;
            }
            default: {
                cout << "Invalid choice" << endl;
            }
        }
        cout << "----------------------------------------" << endl;
    }
}
