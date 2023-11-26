/**
 * A palindrome is a string of chars thats identical when read in forward and 
 * backward direction. Typically, puntuations, capitalizations and spaces are
 * ignored. For eg: "poor dan is in a droop" is a palindrome as can be seen by 
 * examining the chars "poordanisinadroop" and observing that they are identical
 * when in read in backward and forward direction. One way to check for palindrome
 * is to reverse the chars in the string and compare them with the original. In 
 * a palindrome the sequence will be identical.
 * 
 * Write a C++ program using functions from STL stack:
 * 1. To print the original string followed by reversed string using stack
 * 2. To check whether the given string is a palindrome or not
*/

#include <stack>
#include <iostream>

using namespace std;

string sanitize(string str) {
    string res = "";
    for (char ch : str) {
        if (isalnum(ch)) {
            res = res + (char) tolower(ch);
        }
    }
    return res;
}

string reverse(string str) {
    stack<char> stack;
    for (char ch : str) {
        stack.push(ch);
    }
    string res = "";
    while (!stack.empty()) {
        res = res + stack.top();
        stack.pop();
    }
    return res;
}

bool is_palindrome(string str) {
    string sanitized = sanitize(str);
    string reversed = reverse(sanitized);
    return sanitized == reversed;
}

int main() {
    string str;
    cout << "Enter a string: ";
    getline(cin, str);
    cout << "- Reversed: " << reverse(sanitize(str)) << endl;
    cout << "- Is palindrome? " << (is_palindrome(str) == 1 ? "Yes" : "No") << endl;
}
