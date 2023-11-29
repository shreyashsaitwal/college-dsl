// Write a menu driven CPP program for expression conversion and eval
// 1. infix to prefix
// 2. prefix to postfix
// 3. prefix to infix
// 4. postfix to infix
// 5. postfix to prefix

#include <functional>
#include <iostream>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node *link;
};

template <typename T>
class Stack {
   private:
    Node<T> *top = nullptr;
    Node<T> *rear = nullptr;
    unsigned int _len = 0;

   public:
    const int &length;

    Stack() : length(_len){};

    void push(T element) {
        Node<T> *node = new Node<T>{element, nullptr};
        if (top == nullptr) {
            top = rear = node;
        } else {
            node->link = top;
            top = node;
        }
        _len++;
    }

    T pop() {
        if (top == nullptr) return NULL;
        Node<T> *node = top;
        top = top->link;
        T data = node->data;
        delete node;
        _len--;
        return data;
    }

    T peek() {
        if (top == nullptr) return NULL;
        return top->data;
    }

    void for_each(const function<bool(T)> &fn) {
        Node<T> *curr = top;
        while (curr != nullptr) {
            if (fn(curr->data)) {
                break;
            }
            curr = curr->link;
        }
    }

    void print() {
        for_each([](T el) {
            cout << to_string(el) << endl;
            return false;
        });
    }
};

bool is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
}

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^') return 3;
    return 0;
}

string reverse(string str) {
    string res = "";
    for (char ch : str) {
        res = ch + res;
    }
    return res;
}

enum Notation { INFIX, PREFIX, POSTFIX };

string convert_infix(string expr, Notation into) {
    if (into == INFIX) return expr;

    Stack<char> operators;
    string output = "";

    for (char ch : reverse(expr)) {
        if (ch == ' ') continue;
        if (!is_operator(ch)) {
            output = ch + output;
        } else if (ch == ')') {
            operators.push(ch);
        } else if (ch == '(') {
            while (operators.length > 0 && operators.peek() != ')') {
                output = operators.pop() + output;
            }
            operators.pop();
        } else {
            while (operators.length > 0 && precedence(operators.peek()) >= precedence((ch))) {
                output = operators.pop() + output;
            }
            operators.push(ch);
        }
    }

    operators.for_each([&output](char ch) {
        output = ch + output;
        return false;
    });

    if (into == PREFIX)
        return output;
    else
        return reverse(output);
}

string convert_prefix(string expr, Notation into) {
    if (into == PREFIX) {
        return expr;
    }

    string rev = reverse(expr);
    if (into == POSTFIX) {
        return rev;
    }

    Stack<string> stack;
    for (char ch : rev) {
        if (is_operator(ch)) {
            stack.push("(" + stack.pop() + ch + stack.pop() + ")");
        } else {
            string op(1, ch);
            stack.push(op);
        }
    }

    return stack.pop();
}

string convert_postfix(string expr, Notation into) { return convert_prefix(reverse(expr), into); }

int main() {
    while (true) {
        cout << "Select one of the following conversion operations:" << endl;
        cout << "1. Infix to prefix" << endl;
        cout << "2. Prefix to postfix" << endl;
        cout << "3. Prefix to infix" << endl;
        cout << "4. Postfix to infix" << endl;
        cout << "5. Postfix to prefix" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        string input;
        cout << "Enter an expression: ";
        cin >> input;

        string output;
        switch (choice) {
            case 1:
                output = convert_infix(input, PREFIX);
                break;
            case 2:
                output = convert_infix(input, POSTFIX);
                break;
            case 3:
                output = convert_prefix(input, INFIX);
                break;
            case 4:
                output = convert_postfix(input, INFIX);
                break;
            case 5:
                output = convert_postfix(input, PREFIX);
                break;
            default:
                cout << "Invalid choice" << endl;
                break;
        }

        cout << "- Result: " << output << endl;
        cout << "--------------------------------------------" << endl << endl;
    }
}
