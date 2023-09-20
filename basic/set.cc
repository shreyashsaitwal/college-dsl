#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
void print(vector<T> vec) {
    cout << "[ ";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i != vec.size() - 1) {
            cout << ", ";
        }
    }
    cout << " ]" << endl;
}

template<typename T>
vector<T> find_union(vector<T> vec1, vector<T> vec2) {
    vector<T> result;

    // Add elements from first vec
    for (int i = 0; i < vec1.size(); i++) {
        result.push_back(vec1[i]);
    }

    // Add elements from second vec that don't exist in result
    for (int i = 0; i < vec2.size(); i++) {
        int count = std::count(result.begin(), result.end(), vec2[i]);
        if (count == 0) {
            result.push_back(vec2[i]);
        }
    }

    return result;
}

template<typename T>
vector<T> find_intersection(vector<T> vec1, vector<T> vec2) {
    vector<T> result;

    for (int i = 0; i < vec1.size(); i++) {
        int count = std::count(vec2.begin(), vec2.end(), vec1[i]);
        if (count > 0) {
            int count = std::count(result.begin(), result.end(), vec1[i]);
            result.push_back(vec1[i]);
        }
    }

    return result;
}

int main() {
    vector<int> vec1 = {1, 2, 3, 5};
    vector<int> vec2 = {3, 5, 6, 8};

    auto uni = find_union(vec1, vec2);
    print(uni);

    auto inter = find_intersection(vec1, vec2);
    print(inter);
}
