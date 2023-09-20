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
vector<T> difference(vector<T> vec1, vector<T> vec2) {
    vector<T> result;

    for (int i = 0; i < vec1.size(); i++) {
        int count = std::count(vec2.begin(), vec2.end(), vec1[i]);
        if (count == 0) {
            result.push_back(vec1[i]);
        }
    }

    return result;
}

template<typename T>
vector<T> find_union(vector<T> vec1, vector<T> vec2) {
    vector<T> result;

    for (int i = 0; i < vec1.size(); i++) {
        result.push_back(vec1[i]);
    }

    auto vec2_unique = difference(vec2, result);
    for (int i = 0; i < vec2_unique.size(); i++) {
        result.push_back(vec2_unique[i]);
    }

    return result;
}

template<typename T>
vector<T> find_union(vector<T> vec1, vector<T> vec2, vector<T> vec3) {
    vector<T> result = find_union(vec1, vec2);

    auto vec3_unique = difference(vec3, result);
    for (int i = 0; i < vec3_unique.size(); i++) {
        result.push_back(vec3_unique[i]);
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

template<typename T>
vector<T> find_intersection(vector<T> vec1, vector<T> vec2, vector<T> vec3) {
    vector<T> result;
    vector<T> vec1n2 = find_intersection(vec1, vec2);

    for (int i = 0; i < vec3.size(); i++) {
        int count = std::count(vec1n2.begin(), vec1n2.end(), vec3[i]);
        if (count > 0) {
            int count = std::count(result.begin(), result.end(), vec3[i]);
            result.push_back(vec3[i]);
        }
    }

    return result;
}

int main() {
    vector<string> coding = {"Dev", "Shreyash", "Tanmay", "Pranav"};
    vector<string> project = {"Dhananjay", "Shreyash", "Tanmay", "Atharva", "Pranav"};
    vector<string> mastermind = {"Dhananjay", "Shreyash", "Tanmay"};

    while (true) {
        cout << "Select which operation you want to perform." << endl;
        cout << "Find out participants who have participated in: " << endl;
        cout << "1. both coding and project comp." << endl;
        cout << "2. coding or project comp or mastermind." << endl;
        cout << "3. coding but not in mastermind." << endl;
        cout << "4. all the events." << endl;
        cout << "0. Exit" << endl;
        cout << "\nYour choice: ";
        
        int op;
        cin >> op;

        if (op == 0) {
            break;
        }

        vector<string> result;
        switch (op) {
            case 1:
                cout << "Students who have taken part in both coding and project competition:" << endl;
                result = find_intersection(coding, project);
                print(result);
                break;
            
            case 2:
                cout << "Students who have taken part in coding or project comp or mastermind:" << endl;
                result = find_union(coding, project, mastermind);
                print(result);
                break;
            
            case 3:
                cout << "Students who have taken part in coding but not in mastermind:" << endl;
                result = difference(coding, mastermind);
                print(result);
                break;
            
            case 4:
                cout << "Students who have taken part in all the events" << endl;
                result = find_intersection(coding, project, mastermind);
                print(result);
                break;
            
            default:
                cout << "\n Please enter a valid choice..." << endl;
                break;
        }
        cout << "---------------------------------------------------\n" << endl;
    }

}