/**
 * Write a menu driven C++ program to contruct an expression tree from the given
 * prefix expression., for eg, +--a*bc/def, and perform following operations:
 * 1. Traverse it using post order traversal
 * 2. Delete the entire tree
 * 3. Change a tree so that the role of left and right pointers are swapped at
 * every node
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

enum Operator { add, sub, mul, dvi, exp };

struct Operand;

struct Node {
    Operator op;
    Operand *left;
    Operand *right;
};

enum OperandTag { operation, value };

struct Operand {
    OperandTag tag;
    union {
        Node *node;
        char value;
    } operand;

    Operand(OperandTag tag, Node *node) {
        this->tag = tag;
        this->operand.node = node;
    }

    Operand(OperandTag tag, char value) {
        this->tag = tag;
        this->operand.value = value;
    }
};

class ExpressionTree {
   private:
    Node *root;
    vector<Operand *> operands;

    bool is_operator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
    }

    Operator char_to_operator(char ch) {
        if (ch == '+') return Operator::add;
        if (ch == '-') return Operator::sub;
        if (ch == '*') return Operator::mul;
        if (ch == '/') return Operator::dvi;
        if (ch == '^') return Operator::exp;
        throw runtime_error("Unknown operator: " + string(1, ch));
    }

    int precedence(char c) {
        if (c == '+' || c == '-') return 1;
        if (c == '*' || c == '/') return 2;
        if (c == '^') return 3;
        return 0;
    }

    string reverse(string str) {
        string res = "";
        for (char ch : str) res = ch + res;
        return res;
    }

   public:
    ExpressionTree(string expr) {
        string postfix = reverse(expr);
        stack<Operand *> opstack;

        for (char ch : postfix) {
            if (ch == ' ') continue;

            if (is_operator(ch)) {
                auto right = opstack.top();
                opstack.pop();
                auto left = opstack.top();
                opstack.pop();

                auto node = new Node{char_to_operator(ch), left, right};
                auto opnd = new Operand(OperandTag::operation, node);
                opstack.push(opnd);
            } else {
                auto opnd = new Operand(OperandTag::value, ch);
                opstack.push(opnd);
            }
        }

        if (opstack.size() != 1) {
            throw "Something went wrong (size > 1) trying to parse the expression: (" + expr + ").";
        } else if (opstack.top()->operand.node == nullptr) {
            throw "Something went wrong (null operation) trying to parse the expression: (" + expr + ").";
        }

        root = opstack.top()->operand.node;
    }

    static char operator_to_char(Operator op) {
        if (op == Operator::add) return '+';
        if (op == Operator::sub) return '-';
        if (op == Operator::mul) return '*';
        if (op == Operator::dvi) return '/';
        if (op == Operator::exp) return '^';
        throw runtime_error("Unknown operator");
    }

    void traverse(const std::function<void(Operand *)> &fn) {
        stack<Operand *> to_visit;
        vector<Operand *> visited;

        auto root_oprnd = new Operand(OperandTag::operation, root);
        to_visit.push(root_oprnd);

        while (!to_visit.empty()) {
            Node *top = to_visit.top()->operand.node;
            bool l_visit = find(visited.begin(), visited.end(), top->left) !=
                           visited.end();
            bool r_visit = find(visited.begin(), visited.end(), top->right) !=
                           visited.end();

            if (!l_visit) {
                if (top->left->tag == OperandTag::value) {
                    visited.push_back(top->left);
                    fn(top->left);
                } else {
                    to_visit.push(top->left);
                }
            } else if (!r_visit) {
                if (top->right->tag == OperandTag::value) {
                    visited.push_back(top->right);
                    fn(top->right);
                } else {
                    to_visit.push(top->right);
                }
            } else {
                visited.push_back(to_visit.top());
                fn(to_visit.top());
                to_visit.pop();
            }
        }
    }

    void invert_tree() {
        traverse([](Operand *op) {
            if (op->tag == OperandTag::operation) {
                auto temp = op->operand.node->left;
                op->operand.node->left = op->operand.node->right;
                op->operand.node->right = temp;
            }
        });
    }
};

int main() {
    auto exptree = ExpressionTree("+--a*bc/def");
    cout << "Prefix: "
         << "+--a*bc/def" << endl;
    exptree.traverse([](Operand *op) {
        if (op->tag == OperandTag::value) {
            cout << op->operand.value << " ";
        } else {
            cout << ExpressionTree::operator_to_char(op->operand.node->op)
                 << " ";
        }
    });
    cout << endl;
    exptree.invert_tree();
    exptree.traverse([](Operand *op) {
        if (op->tag == OperandTag::value) {
            cout << op->operand.value << " ";
        } else {
            cout << ExpressionTree::operator_to_char(op->operand.node->op)
                 << " ";
        }
    });
    cout << endl;
}
