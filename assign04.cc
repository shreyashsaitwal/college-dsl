#include <iostream>
#include <vector>
using namespace std;

template<typename T>
using Mat = vector<vector<T>>;

class SparseMat {
    public:
        static bool isSparse(Mat<int> mat) {
            int zeroCount = 0;
            int nonZeroCount = 0;
            for (auto row : mat) {
                for (auto el : row) {
                    if (el == 0) 
                        zeroCount++;
                    else
                        nonZeroCount++;
                }
            }
            return zeroCount > nonZeroCount;
        }

        static void print(Mat<int> mat) {
            for (auto row : mat) {
                for (int el : row) {
                    cout << el << "\t";
                }
                cout << endl;
            }
        }

        static Mat<int> read(int m, int n) {
            Mat<int> mat;
            for (int i = 0; i < m; i++) {
                cout << "Enter elements of row #" << i + 1 << ": ";
                vector<int> row;
                for (int j = 0; j < n; j++) {
                    int val;
                    cin >> val;
                    row.push_back(val);
                }
                mat.push_back(row);
            }
            return mat;
        }

        static Mat<int> add(Mat<int> m1, Mat<int> m2) {
            if (m1.size() != m2.size() || m1[0].size() != m2[0].size()) {
                cout << "ERR: Can't perform addition of matrices with different dimensions." << endl;
                exit(1);
            }

            Mat<int> mat;
            for (int i = 0; i < m1.size(); i++) {
                vector<int> row;
                for (int j = 0; j < m1[0].size(); j++) {
                    row.push_back(m1[i][j] + m2[i][j]);
                }
                mat.push_back(row);
            }
            return mat;
        }

        static Mat<int> simpleTrans(Mat<int> mat) {
            vector<int> defRow(mat[0].size(), 0);
            Mat<int> trans(mat.size(), defRow);

            for (int i = 0; i < mat.size(); i++) {
                for (int j = 0; j < mat[0].size(); j++) {
                    trans[j][i] = mat[i][j];
                }
            }
            return trans;
        }

        static Mat<int> fastTrans(Mat<int> mat) {
            if (!isSparse(mat)) {
                cout << "ERR: Fast transpose algorithm only works on sparse matrices" << endl;
                exit(1);
            }

            vector<int> defRow(mat[0].size(), 0);
            Mat<int> trans(mat.size(), defRow);

            for (int i = 0; i < mat.size(); i++) {
                for (int j = 0; j < mat[0].size(); j++) {
                    if (mat[i][j] != 0) {
                        trans[j][i] = mat[i][j];
                    }
                }
            }
            return trans;
        }
};

int main() {
    auto mat = SparseMat::read(3, 3);
    cout << "Is sparse: " << (SparseMat::isSparse(mat) ? "true" : "false") << endl;
    SparseMat::print(SparseMat::fastTrans(mat));
}
