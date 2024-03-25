/**
 * Graph traversal: The area around the college and the prominent landmarks of
 * it are represented using graphs.
 * Write a menu driven C++ program to represent this as a graph using adjacency
 * matrix/list and perform DFS and BFS.
 */

#include <algorithm>
#include <iostream>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

template <typename T>
struct Node {
    T thing;
    set<tuple<Node<T> *, int>> neighbors;
};

template <typename T>
class UDGraph {
   private:
    set<Node<T> *> nodes;

   public:
    Node<T> *add_node(T thing) {
        auto node = new Node<T>{thing};
        nodes.insert(node);
        return node;
    }

    void add_edge(Node<T> *n1, Node<T> *n2, int cost) {
        auto edge = make_tuple(n2, cost);
        n1->neighbors.insert(edge);
    }

    void display() {
        for (Node<T> *node : nodes) {
            cout << "(" << node->thing << ")";
            if (!node->neighbors.empty()) {
                cout << " -> ";
            }
            for (const auto &edge : node->neighbors) {
                cout << "(" << get<0>(edge)->thing << ", " << get<1>(edge)
                     << ") ";
            }
            cout << endl;
        }
    }

    vector<Node<T> *> dfs(Node<T> *start) {
        vector<Node<T> *> explored;
        vector<Node<T> *> frontier;
        frontier.push_back(start);

        while (!frontier.empty()) {
            auto node = frontier.at(frontier.size() - 1);
            frontier.pop_back();
            explored.push_back(node);

            for (const auto &edge : node->neighbors) {
                Node<T> *neighbor = get<0>(edge);
                bool is_explored = find(explored.begin(), explored.end(),
                                        neighbor) != explored.end();
                bool is_in_frontier = find(frontier.begin(), frontier.end(),
                                           neighbor) != frontier.end();

                if (!is_explored && !is_in_frontier) {
                    frontier.push_back(neighbor);
                }
            }
        }
        return explored;
    }

    vector<Node<T> *> bfs(Node<T> *start) {
        vector<Node<T> *> explored;
        vector<Node<T> *> frontier;
        frontier.push_back(start);

        while (!frontier.empty()) {
            Node<T> *node = frontier.at(0);
            frontier.erase(frontier.begin());
            explored.push_back(node);

            for (const auto &edge : node->neighbors) {
                Node<T> *neighbor = get<0>(edge);
                bool is_explored = find(explored.begin(), explored.end(),
                                        neighbor) != explored.end();
                bool is_in_frontier = find(frontier.begin(), frontier.end(),
                                           neighbor) != frontier.end();

                if (!is_explored && !is_in_frontier) {
                    frontier.push_back(neighbor);
                }
            }
        }
        return explored;
    }
};

int main() {
    UDGraph<int> binary_tree;
    auto n1 = binary_tree.add_node(1);
    auto n2 = binary_tree.add_node(2);
    auto n3 = binary_tree.add_node(3);
    auto n4 = binary_tree.add_node(4);
    auto n5 = binary_tree.add_node(5);
    auto n6 = binary_tree.add_node(6);
    auto n7 = binary_tree.add_node(7);

    binary_tree.add_edge(n1, n2, 1);
    binary_tree.add_edge(n1, n3, 1);
    binary_tree.add_edge(n2, n4, 1);
    binary_tree.add_edge(n2, n5, 1);
    binary_tree.add_edge(n3, n6, 1);
    binary_tree.add_edge(n3, n7, 1);

    auto p1 = binary_tree.dfs(n1);
    for (auto i : p1) {
        cout << "(" << i->thing << ")";
        if (i != p1.at(p1.size() - 1)) {
            cout << " -> ";
        }
    }

    cout << endl;
    auto p2 = binary_tree.bfs(n1);
    for (auto i : p2) {
        cout << "(" << i->thing << ")";
        if (i != p2.at(p2.size() - 1)) {
            cout << " -> ";
        }
    }
    cout << endl;
}
