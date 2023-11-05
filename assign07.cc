#include <functional>
#include <iostream>
#include <regex>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T> *link;
};

template <typename T>
bool operator==(Node<T> &a, Node<T> &b) {
    return a.data == b.data && a.link == b.link;
}

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

    Node<T> *next() {
        if (current != nullptr) {
            auto *temp = current;
            current = current->link;
            return temp;
        }
        return nullptr;
    }

    bool is_empty() { return head == nullptr; }

    void for_each(const std::function<bool(Node<T> *)> &fn) {
        if (is_empty()) return;
        auto *og_curr = current;
        current = head;
        do {
            if (fn(current)) break;
        } while (next()->link != nullptr);
        current = og_curr;
    }

    void print() {
        for_each([](Node<T> *node) {
            cout << to_string(node->data) << endl;
            return false;
        });
    }

    int index_of(Node<T> *node) {
        int idx = -1;
        int count = 0;
        for_each([&count, &idx, &node](Node<T> *n) {
            if (*n == *node) {
                idx = count;
                return true;
            }
            count++;
            return false;
        });
        return idx;
    }

    Node<T> *node_at(int idx) {
        if (idx == 0)
            return head;
        else if (idx == _length - 1)
            return tail;

        Node<T> *res = nullptr;
        int count = 0;
        for_each([&count, &idx, &res, this](Node<T> *_) {
            if (count == idx) {
                res = current;
                return true;
            }
            count++;
            return false;
        });
        return res;
    }

    void insert_at(int idx, T element) {
        auto *new_node = new Node<T>{element, nullptr};
        auto *curr_node_at_idx = node_at(idx);

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
                auto *node_at_prev_idx = node_at(idx - 1);
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

        auto *node_at_idx = node_at(idx);
        if (idx == 0) {
            head = node_at_idx->link;
        } else {
            auto *node_at_prev_idx = node_at(idx - 1);
            node_at_prev_idx->link = node_at_idx->link;
            if (idx == _length - 1) {
                tail = node_at_prev_idx;
            }
        }

        if (_length - 1 == 0) {
            head = tail = current = nullptr;
        } else if (current == node_at_idx) {
            if (idx == _length - 1) {
                current = head;
            } else {
                current = node_at(idx);
            }
        }

        _length--;
        delete node_at_idx;
    }

    Node<T> *first_where(const std::function<bool(T)> &predicate) {
        Node<T> *res = nullptr;
        if (is_empty()) return res;
        for_each([predicate, &res](Node<T> *node) {
            if (predicate(node->data)) {
                res = node;
                return true;
            }
            return false;
        });
        return res;
    }

    LinkedList<T> where(const std::function<bool(T)> &predicate) {
        LinkedList<T> res;
        if (is_empty()) return res;
        for_each([predicate, &res](Node<T> *node) {
            if (predicate(node->data)) {
                res.insert_at(res.length, node->data);
            }
            return false;
        });
        return res;
    }

    bool contains(T element) {
        return first_where([element](const T e) { return e == element; }) != nullptr;
    }

    void sort(const std::function<bool(T, T)> &predicate) {
        int iters = length;
        for_each([predicate, &iters, this](Node<T> *_) {
            Node<T> *prev = nullptr;
            int count = 0;

            for_each([predicate, &prev, &iters, &count, this](Node<T> *node) {
                if (node->link == nullptr || count > iters) {
                    return true;
                }

                if (!predicate(node->data, node->link->data)) {
                    auto *curr = node;
                    auto *next = node->link;
                    curr->link = next->link;
                    next->link = curr;
                    if (prev == nullptr) {
                        head = next;
                    } else {
                        prev->link = next;
                    }
                    prev = next;
                }

                count++;
                prev = node;
                return false;
            });

            iters--;
            return false;
        });
    }
};

struct Appointment {
    float start_time;
    float end_time;
};

string to_string(Appointment &a) {
    string start = regex_replace(to_string(a.start_time), regex("\\."), ":");
    string end = regex_replace(to_string(a.end_time), regex("\\."), ":");
    return "- [ " + start.substr(0, start.find(":") + 3) + " - " +
           end.substr(0, end.find(":") + 3) + " ]";
}

bool operator==(const Appointment &a1, const Appointment &a2) {
    return a1.start_time == a2.start_time && a1.end_time == a2.end_time;
}

void app() {
    LinkedList<Appointment> slots;
    slots.insert_at(slots.length, {9.0, 10.0});
    slots.insert_at(slots.length, {10.30, 11.30});
    slots.insert_at(slots.length, {12.0, 13.0});
    slots.insert_at(slots.length, {15.0, 16.0});
    slots.insert_at(slots.length, {16.30, 17.30});

    LinkedList<Appointment> appointments;
    LinkedList<Appointment> cancelled;
    while (true) {
        cout << "Select operation: " << endl;
        cout << "1. Display available slots" << endl;
        cout << "2. Display booked slots" << endl;
        cout << "3. Book appointment" << endl;
        cout << "4. Cancel appointment" << endl;
        cout << "5. Sort appointments" << endl;
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
                auto available = slots.where(
                    [&appointments](const Appointment ap) { return !appointments.contains(ap); });
                available.print();
                break;
            }
            case 2: {
                appointments.print();
                break;
            }
            case 3: {
                cout << "- Enter start time: ";
                cin >> temp.start_time;
                auto available = slots.where(
                    [&appointments](const Appointment ap) { return !appointments.contains(ap); });
                auto slot = available.first_where(
                    [&temp](Appointment ap) { return ap.start_time == temp.start_time; });
                if (slot == nullptr) {
                    cout << "- Slot with given start time does not exist" << endl;
                } else {
                    appointments.insert_at(appointments.length, slot->data);
                    cout << "- Slot " + to_string(slot->data) + " successfully booked!" << endl;
                }
                break;
            }
            case 4: {
                cout << "- Enter start time: ";
                cin >> temp.start_time;
                auto slot = appointments.first_where(
                    [&temp](Appointment ap) { return ap.start_time == temp.start_time; });
                if (slot == nullptr) {
                    cout << "- Slot with given start time does not exist" << endl;
                } else {
                    cancelled.insert_at(cancelled.length, slot->data);
                    appointments.remove_at(appointments.index_of(slot));
                    cout << "- Slot " + to_string(slot->data) + " successfully cancelled!" << endl;
                }
                break;
            }
            case 5: {
                appointments.sort(
                    [](Appointment a1, Appointment a2) { return a1.start_time < a2.start_time; });
                appointments.print();
                break;
            }
            case 6: {
                if (cancelled.length > 0) {
                    cout << "Cancelled appointments: " << endl;
                    cancelled.print();
                } else {
                    cout << "There is no cancelled appointment" << endl;
                }
                break;
            }
            default:
                cout << "Please select a valid option" << endl;
                break;
        }
        cout << "---------------------------" << endl;
    }
}

void app_v2() {
    float start = 9.0;
    float end = 17.0;
    float max_time = 1.5;

    LinkedList<Appointment> appointments;
    while (true) {
        cout << "Select operation: " << endl;
        cout << "1. Display booked slots" << endl;
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

        switch (choice) {
            case 1: {
                if (!appointments.is_empty()) {
                    appointments.print();
                } else {
                    cout << "No appointment booked for today" << endl;
                }
                break;
            }
            case 2: {
                auto *temp = new Appointment;
                cout << "- Enter start time: ";
                cin >> temp->start_time;
                cout << "- Enter end time: ";
                cin >> temp->end_time;
                if (temp->start_time < start || temp->end_time > end) {
                    cout << "We don't take any appointements before 8:00 and after 17:00" << endl;
                    break;
                }

                auto conflicting = appointments.first_where([temp](Appointment ap) {
                    return (temp->start_time >= ap.start_time && temp->start_time <= ap.end_time) ||
                           (temp->end_time <= ap.end_time && temp->end_time >= ap.start_time);
                });
                if (conflicting != nullptr) {
                    cout << "Sorry, we already have an appointment between that time frame" << endl;
                    break;
                }

                appointments.insert_at(appointments.length, *temp);
                cout << "Slot " << to_string(*temp) << " successfully booked!" << endl;
                break;
            }
            case 3: {
                auto *temp = new Appointment;
                cout << "- Enter start time: ";
                cin >> temp->start_time;
                auto slot = appointments.first_where(
                    [&temp](Appointment ap) { return ap.start_time == temp->start_time; });
                if (slot == nullptr) {
                    cout << "- Slot with given start time does not exist" << endl;
                } else {
                    cout << "- Slot " + to_string(slot->data) + " successfully cancelled!" << endl;
                    appointments.remove_at(appointments.index_of(slot));
                }
                break;
            }
            case 4: {
                appointments.sort(
                    [](Appointment a1, Appointment a2) { return a1.start_time < a2.start_time; });
                appointments.print();
                break;
            }
            default:
                cout << "Please select a valid option" << endl;
                break;
        }
        cout << "---------------------------" << endl;
    }
}

int main() { app_v2(); }
