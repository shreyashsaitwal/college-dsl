#include <ctime>
#include <functional>
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
        LinkedList<T> res = where(predicate);
        return res.length > 0 ? res.head : nullptr;
    }

    LinkedList<T> where(const std::function<bool(T)> &predicate) {
        LinkedList<T> res;
        Node<T> *og_curr = current;
        current = head;
        do {
            if (predicate(current->data)) {
                res.insert_at(res.length, current->data);
            }
        } while (next());
        return res;
    }
};

struct DOB {
    int day;
    int month;
    int year;
};

struct Student {
    string name;
    DOB dob;
};

class StudentOps {
   public:
    static Student *from_stdout() {
        Student *stud = new Student;
        cout << "- Name of student: ";
        cin >> stud->name;
        cout << "- DOB of student (dd mm yyyy): ";
        cin >> stud->dob.day >> stud->dob.month >> stud->dob.year;
        return stud;
    }
};

string to_string(Student stud) {
    return "- " + stud.name + " (" + std::to_string(stud.dob.day) + "/" +
           std::to_string(stud.dob.month) + "/" + std::to_string(stud.dob.year) + ")";
}

bool operator==(DOB &d1, DOB &d2) {
    return d1.day == d2.day && d1.month == d2.month && d1.year == d2.year;
}

bool operator==(Student &s1, Student &s2) { return (s1.name == s2.name) && (s1.dob == s2.dob); }

string todays_date() {
    time_t t = time(0);
    tm *now = localtime(&t);
    string res = to_string(now->tm_mday) + "/" + to_string(now->tm_mon + 1);
    return res;
}

int main() {
    string date = todays_date();
    LinkedList<Student> studs;
    while (true) {
        cout << "Select operation: " << endl;
        cout << "1. Enter new student" << endl;
        cout << "2. Delete a student" << endl;
        cout << "3. See whose birthday is it today" << endl;
        cout << "4. Display all students" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cout << endl;

        if (choice == 0) {
            break;
        }

        Student temp;
        switch (choice) {
            case 1: {
                cout << "Add new student: " << endl;
                studs.insert_at(studs.length, *StudentOps::from_stdout());
                break;
            }

            case 2: {
                cout << "Delete a student: " << endl;
                cout << "- Name of student: ";
                cin >> temp.name;
                Node<Student> *student =
                    studs.first_where([temp](Student s) { return s.name == temp.name; });
                if (student == nullptr) {
                    cout << "- No student exists with given name." << endl;
                } else {
                    studs.remove_at(studs.index_of(student));
                }
                break;
            }

            case 3: {
                cout << "Today's birthdays: " << endl;
                LinkedList<Student> birthday_studs = studs.where([date](Student s) {
                    return to_string(s.dob.day) + "/" + to_string(s.dob.month) == date;
                });
                if (birthday_studs.length > 0) {
                    birthday_studs.print();
                } else {
                    cout << "There's no one's birthday today" << endl;
                }
                break;
            }

            case 4: {
                cout << "All students: " << endl;
                studs.print();
                break;
            }

            default:
                cout << "Please select a valid operation..." << endl;
                break;
        }

        cout << "------------------------------------------------------------------" << endl;
    }
}
