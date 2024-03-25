/**
 * Sandy is a well organized person. Every day he makes a list of things which
 * need to be done and enumerates them from 1 to n. However, some things need to
 * be done before others.
 * Write a C++ code to find out whether Sandy can solve all his duties and if
 * so, print the correct order.
 */

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

template <typename T>
struct Node {
    T thing;
    vector<Node<T> *> incoming;
    vector<Node<T> *> outgoing;
};

template <typename T>
class DiGraph {
   private:
    vector<Node<T> *> nodes;

   public:
    Node<T> *add_node(T thing) {
        auto node = new Node<T>{thing};
        nodes.push_back(node);
        return node;
    }

    void add_edge(Node<T> *from, Node<T> *to) {
        from->outgoing.push_back(to);
        to->incoming.push_back(from);
    }

    vector<Node<T> *> topological_sort() {
        map<Node<T> *, int> map;
        queue<Node<T> *> queue;
        vector<Node<T> *> sorted;

        for (auto node : nodes) {
            if (node->incoming.size() == 0) {
                queue.push(node);
            } else {
                map[node] = node->incoming.size();
            }
        }

        while (!queue.empty()) {
            auto front = queue.front();
            sorted.push_back(front);
            queue.pop();

            for (auto node : front->outgoing) {
                if (map[node] > 0) {
                    map[node] = map[node] - 1;
                    if (map[node] == 0) {
                        queue.push(node);
                    }
                }
            }
        }

        if (sorted.size() != nodes.size()) {
            throw runtime_error(
                "Graph has a cycle, topological sorting not possible");
        }

        return sorted;
    }
};

int main() {
    DiGraph<string> taskGraph;

    auto wakeUp = taskGraph.add_node("Wake Up");
    auto getDressed = taskGraph.add_node("Get Dressed");
    auto commute = taskGraph.add_node("Commute");
    auto eatBreakfast = taskGraph.add_node("Eat Breakfast");
    auto makeCoffee = taskGraph.add_node("Make Coffee");
    auto shower = taskGraph.add_node("Shower");

    taskGraph.add_edge(wakeUp, makeCoffee);
    taskGraph.add_edge(wakeUp, shower);
    taskGraph.add_edge(shower, getDressed);
    taskGraph.add_edge(makeCoffee, eatBreakfast);
    taskGraph.add_edge(getDressed, commute);

    try {
        vector<Node<string> *> sortedOrder = taskGraph.topological_sort();
        cout << "Sandy will perfrom his duties in the following order:\n";
        for (auto node : sortedOrder) {
            cout << node->thing << " > ";
        }
        cout << endl;
    } catch (const runtime_error &e) {
        cerr << "Sandy won't be able to perform his duties... :(" << endl;
    }

    return 0;
}
