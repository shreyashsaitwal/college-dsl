// Write a menu driven CPP program for expression conversion and eval
// 1. infix to prefix
// 2. prefix to postfix
// 3. prefix to infix
// 4. postfix to infix
// 5. postfix to prefix

#include <iostream>

using namespace std;

enum class Operator { Plus, Minus, Multiply, Divide };

Operator oper_from_string(string o) {
    if (o == "+")
        return Operator::Plus;
    else if (o == "-")
        return Operator::Minus;
    else if (o == "*")
        return Operator::Multiply;
    else
        return Operator::Divide;
}

enum class Operand { Literal, Expr };

struct Literal {
    string data;
};

struct Expr {
    Operator oper;
    Operand left;
    Operand right;
};

// (A + B) * C / D

// Expr expr_from_string(string e) {

// }

int main() {}
