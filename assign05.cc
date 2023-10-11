#include <iostream>
using namespace std;

class Polynomial {
    int *coeffs;
    int highestDeg;

    public:
        static Polynomial read() {
            Polynomial poly;
            cout << "Highest degree of your polynomial: ";
            cin >> poly.highestDeg;

            poly.coeffs = new int[poly.highestDeg];

            for (int i = 0; i <= poly.highestDeg; i++) {
                cout << "Enter coefficient of degree " << i << ": ";
                cin >> poly.coeffs[i];
            }
            return poly;
        }

        static Polynomial add(Polynomial a, Polynomial b) {
            Polynomial res = a;
            for (int i = 0; i <= b.highestDeg; i++) {
                res.coeffs[i] = res.coeffs[i] + b.coeffs[i];
            }
            return res;
        }

        string toString() {
            string expr = "";
            for (int i = highestDeg; i >= 0; i--) {
                if (coeffs[i] == 0) continue;
                if (expr != "")
                    expr = expr + " + ";
                if (coeffs[i] != 1)
                    expr = expr + to_string(coeffs[i]);
                if (i != 0) {
                    expr = expr + "x";
                    if (i != 1) {
                        expr = expr + "^" + to_string(i);
                    }
                }
            }
            return expr;
        }
};

int main() {
    auto poly = Polynomial::read();
    cout << "\nGiven polynomial: " << poly.toString() << endl;
    auto addition = Polynomial::add(poly, poly);
    cout << "Addition of given polynomial with itself: " << addition.toString() << endl;
}