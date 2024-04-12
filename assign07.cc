/**
 * Write a C++ program to construct the binary tree with a given preorder and
 * inorder sequence and test your tree with all traversals.
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

enum SeqOrder { pre, in, post };

class Utils {
   public:
    static vector<string> split(string str, char delimiter) {
        stringstream stream(str);
        string token;
        vector<string> res;

        while (getline(stream, token, delimiter)) {
            res.push_back(token);
        }

        return res;
    }

    static vector<int> strs_to_ints(vector<string> strs) {
        vector<int> res;
        for (string str : strs) {
            res.push_back(stoi(str));
        }
        return res;
    }
};

struct Node {
    int num;
    Node *left;
    Node *right;

    Node(int num) : num(num), left(nullptr), right(nullptr) {}
};

class BST {
   private:
    Node *root;

    BST(Node *root) : root(root) {}

    void insert(int num, Node *&parent) {
        if (!parent) {
            parent = new Node(num);
        } else {
            if (num <= parent->num) {
                insert(num, parent->left);
            } else {
                insert(num, parent->right);
            }
        }
    }

    static pair<vector<int>, vector<int>> split_seq(vector<int> seq,
                                                    int parent) {
        pair<vector<int>, vector<int>> result;
        for (int i : seq) {
            if (i <= parent)
                result.first.push_back(i);
            else
                result.second.push_back(i);
        }
        return result;
    }

    static Node *from_preorder(vector<int> seq) {
        if (seq.empty()) return nullptr;
        Node *node = new Node(seq.at(0));
        auto split = split_seq(vector(seq.begin() + 1, seq.end()), seq.at(0));
        if (!split.first.empty()) {
            node->left = from_preorder(split.first);
        }
        if (!split.second.empty()) {
            node->right = from_preorder(split.second);
        }
        return node;
    }

   public:
    static BST from_seq(SeqOrder order, string seq) {
        auto int_seq = Utils::strs_to_ints(Utils::split(seq, ' '));
        return BST(from_preorder(int_seq));
    }

    void traverse(const std::function<void(int)> &fn) {
        if (root == nullptr) return;

        stack<Node *> to_visit;
        Node *current = root;
        Node *prev_visited = nullptr;

        while (current != nullptr || !to_visit.empty()) {
            while (current != nullptr) {
                to_visit.push(current);
                current = current->left;
            }

            Node *top_node = to_visit.top();
            if (top_node->right == nullptr || top_node->right == prev_visited) {
                fn(top_node->num);
                to_visit.pop();
                prev_visited = top_node;
            } else {
                current = top_node->right;
            }
        }
    }
};

int main() {
    string seq = "10 5 3 7 15 12 18";
    BST bst = BST::from_seq(SeqOrder::pre, seq);
    bst.traverse([](int i) { cout << i << endl; });
}
