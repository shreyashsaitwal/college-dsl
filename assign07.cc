#include <iostream>
#include <functional>
#include <regex>

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

    Node<T> *peek() {
        if (has_next()) {
            return current->link;
        }
        return nullptr;
    }

    bool is_empty() { return head == nullptr; }

    void print() {
        if (is_empty()) return;
        Node<T> *og_curr = current;
        current = head;
        do {
            cout << "- " << to_string(current->data) << endl;
        } while (next() != nullptr);
        current = og_curr;
    }

    int index_of(Node<T> *node) {
        int idx = -1;
        Node<T> *og_curr = current;
        current = head;

        int count = 0;
        while (count < _length) {
            if (current->data == node->data) {
                idx = count;
                break;
            }
            next();
            count++;
        }

        current = og_curr;
        return idx;
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

    Node<T> *first_where(const std::function<bool(T)>& predicate) {
        LinkedList<T> res = where(predicate);
        return res.length > 0 ? res.head : nullptr;
    }

    LinkedList<T> where(const std::function<bool(T)>& predicate) {
        LinkedList<T> res;
        if (is_empty()) return res;

        Node<T> *og_curr = current;
        current = head;
        do {
            if (predicate(current->data)) {
                res.insert_at(res.length, current->data);
            }
        } while (next());
        return res;
    }

    bool contains(T element) {
        return where([element](const T e) { return e == element; }).length > 0;
    }

    void sort(const std::function<bool(T, T)>& predicate) {
        auto og_curr = current;
        current = head;
        do {
            auto og_curr2 = current;
            current = head;
            Node<T> *prev = nullptr;
            do {
                if (!predicate(peek()->data, peek()->link->data)) {
                    Node<T> *next = peek()->link;
                    Node<T> *curr = peek();
                    curr->link = next->link;
                    next->link = curr;
                    current->link = next;
                }
                prev = next();
            } while (peek()->link != nullptr);
            current = og_curr2;
        } while (next() != nullptr);
        current = og_curr;
    }
};

struct Appointment {
    float start_time;
    float end_time;
};

string to_string(Appointment& a) {
    string start = regex_replace(to_string(a.start_time), regex("\\."), ":");
    string end =  regex_replace(to_string(a.end_time), regex("\\."), ":");
    return "[ " + start.substr(0, start.find(":") + 3) + " - " + end.substr(0, end.find(":") + 3) + " ]";
}

bool operator==(const Appointment& a1, const Appointment& a2) {
    return a1.start_time == a2.start_time && a1.end_time == a2.end_time;
}


int main() {
    LinkedList<Appointment> slots;
    slots.insert_at(slots.length, {9.0, 10.0});
    slots.insert_at(slots.length, {10.30, 11.30});
    slots.insert_at(slots.length, {12.0, 1.0});
    slots.insert_at(slots.length, {3.0, 4.0});
    slots.insert_at(slots.length, {4.30, 5.30});

    LinkedList<Appointment> appointments;
    while (true) {
        cout << "Select operation: " << endl;
        cout << "1. Display available slots" << endl;
        cout << "2. Book appointment" << endl;
        cout << "3. Cancel appointment" << endl;
        cout << "4. Sort appointments" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 0) {
            break;
        }

        Appointment temp;
        switch (choice) {
            case 1: {
                auto available = slots.where([&appointments](const Appointment ap) { return !appointments.contains(ap); });
                available.print();
                break;
            }
            case 2: {
                cout << "- Enter start time: ";
                cin >> temp.start_time;
                auto available = slots.where([&appointments](const Appointment ap) { return !appointments.contains(ap); });
                auto slot = available.first_where([&temp](Appointment ap) { return ap.start_time == temp.start_time; });
                if (slot == nullptr) {
                    cout << "- Slot with given start time does not exist" << endl;
                } else {
                    appointments.insert_at(appointments.length, slot->data);
                    cout << "- Slot " + to_string(slot->data) + " successfully booked!" << endl;
                }
                break;
            }
            case 3: {
                cout << "- Enter start time: ";
                cin >> temp.start_time;
                auto available = slots.where([&appointments](const Appointment ap) { return !appointments.contains(ap); });
                auto slot = available.first_where([&temp](Appointment ap) { return ap.start_time == temp.start_time; });
                if (slot == nullptr) {
                    cout << "- Slot with given start time does not exist" << endl;
                } else {
                    appointments.remove_at(appointments.index_of(slot));
                    cout << "- Slot " + to_string(slot->data) + " successfully cancelled!" << endl;
                }
                break;
            }
            case 4: {
                slots.sort([](Appointment a1, Appointment a2) { return a1.start_time < a2.start_time; });
                slots.print();
                break;
            }
            default:
                break;
        }
    }
}