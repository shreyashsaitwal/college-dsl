#include <iostream>

using namespace std;

class StrOps {
   public:
    static string occurance(char ch, string str) {
        string res = "[ ";
        int count = 0;
        for (char c : str) {
            count++;
            if (ch != c) {
                continue;
            }
            res = res + to_string(count - 1) + " ";
        }
        res = res + "]";
        return res;
    }

    static string rm_char(char ch, string str) {
        string res = "";
        for (char c : str) {
            if (c != ch) {
                res = res + c;
            }
        }
        return res;
    }

    static bool is_palindrome(string str) {
        string rev = "";
        for (char ch : str) {
            rev = ch + rev;
        }
        return rev == str;
    }

    static string replace_substr(string str, string target, string rep) {
        int pos[2] = {-1, -1};
        int idx = 0;
        for (int i = 0; i < str.length(); i++) {
            if (idx < target.length() && str.at(i) == target.at(idx)) {
                if (pos[0] == -1) {
                    pos[0] = i;
                }
                idx++;
            } else {
                if (pos[0] != -1 && idx == target.length()) {
                    pos[1] = i;
                    break;
                }
                pos[0] = -1;
                pos[1] = -1;
                idx = 0;
            }
        }

        if (pos[0] != -1 && pos[1] == -1) {
            pos[1] = str.length() - 1;
        }

        idx = 0;
        string newStr = "";
        for (int i = 0; i < str.length(); i++) {
            if (i >= pos[0] && i < pos[1]) {
                if (idx < rep.length()) {
                    newStr = newStr + rep.at(idx);
                    idx++;
                }
            } else {
                newStr = newStr + str.at(i);
            }
        }

        return newStr;
    }
};

int main() {
    while (true) {
        cout << "Select string operation:\n";
        cout << "1. Find all the occurances of a character\n";
        cout << "2. Extract a substring\n";
        cout << "3. Remove a character\n";
        cout << "4. Replace a substring\n";
        cout << "5. Check if a string is palindrome\n";
        cout << "0. Exit...\n";
        cout << "Enter your choice: ";

        int opr;
        cin >> opr;

        if (opr == 0) {
            break;
        }

        switch (opr) {
            case 1: {
                string str;
                cout << "-- Enter string: ";
                cin >> str;
                char ch;
                cout << "-- Enter char: ";
                cin >> ch;
                cout << ">> Given char occures at these indices: " << StrOps::occurance(ch, str)
                     << endl;
            } break;

            case 2: {
                string str;
                cout << "-- Enter string: ";
                cin >> str;
                int pos, ch;
                cout << "-- Enter starting position: ";
                cin >> pos;
                cout << "-- Enter number of chars: ";
                cin >> ch;
                cout << ">> Substring: " << str.substr(pos, ch) << endl;
            } break;

            case 3: {
                string str;
                cout << "-- Enter string: ";
                cin >> str;
                char ch;
                cout << "-- Enter char: ";
                cin >> ch;
                cout << ">> New string: " << StrOps::rm_char(ch, str) << endl;
            } break;

            case 4: {
                string str, target, rep;
                cout << "-- Enter string: ";
                cin >> str;
                cout << "-- Enter string that is to be replaced: ";
                cin >> target;
                cout << "-- Enter replacement string: ";
                cin >> rep;
                cout << ">> New string: " << StrOps::replace_substr(str, target, rep) << endl;
            } break;

            case 5: {
                string str;
                cout << "-- Enter string: ";
                cin >> str;
                cout << ">> Is palindrome: " << StrOps::is_palindrome(str) << endl;
            } break;

            default:
                cout << "Enter a valid choice..." << endl;
                break;
        }

        cout << "-----------------------------------------------" << endl;
    }
}
