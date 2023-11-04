#include <iostream>

using namespace std;

class Polynomial {
    int *coeffs;
    int highest_deg;

   public:
    static Polynomial read() {
        Polynomial poly;
        cout << "Highest degree of your polynomial: ";
        cin >> poly.highest_deg;

        poly.coeffs = new int[poly.highest_deg];

        for (int i = 0; i <= poly.highest_deg; i++) {
            cout << "Enter coefficient of degree " << i << ": ";
            cin >> poly.coeffs[i];
        }
        return poly;
    }

    static Polynomial add(Polynomial a, Polynomial b) {
        Polynomial res = a;
        for (int i = 0; i <= b.highest_deg; i++) {
            res.coeffs[i] = res.coeffs[i] + b.coeffs[i];
        }
        return res;
    }

    string to_string() {
        string expr = "";
        for (int i = highest_deg; i >= 0; i--) {
            if (coeffs[i] == 0) continue;
            if (expr != "") expr = expr + " + ";
            if (coeffs[i] != 1) expr = expr + to_string(coeffs[i]);
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
    auto poly = Polynomial::read();
    cout << "\nGiven polynomial: " << poly.to_string() << endl;
    auto addition = Polynomial::add(poly, poly);
    cout << "Addition of given polynomial with itself: " << addition.to_string() << endl;
}
