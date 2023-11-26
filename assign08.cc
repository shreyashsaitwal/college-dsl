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

string convert_infix(string expr, Notation notation) {
    if (notation == INFIX) return expr;

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

    if (notation == PREFIX) return output;
    else return reverse(output);
}

string convert_prefix(string expr, Notation notation) {
    if (notation == PREFIX) {
        return expr;
    }

    string rev = reverse(expr);
    if (notation == POSTFIX) {
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

string convert_postfix(string expr, Notation notation) {
    return convert_prefix(reverse(expr), notation);
}

int main() {
    cout << "Enter an infix notation: ";
    string input;
    cin >> input;
    string pre = convert_infix(input, PREFIX);
    string post = convert_infix(input, POSTFIX);
    cout << "- Prefix:  " << pre << endl;
    cout << "- Postfix: " << post << endl;
    cout << "- Infix (from prefix): " << convert_prefix(pre, INFIX) << endl;
    cout << "- Infix (from postfix): " << convert_postfix(post, INFIX) << endl;
}
