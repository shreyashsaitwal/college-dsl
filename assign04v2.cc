#include <iostream>
#include <vector>

using namespace std;

template <typename T>
using SparseMat = vector<vector<T>>;

class MatOps {
   public:
    // static bool is_sparse(Mat<int> mat) {
    //     todo
    // }

    static void print(SparseMat<int> mat) {
        int iter = 1;
        for (int i = 0; i < mat[0][0]; i++) {
            for (int j = 0; j < mat[0][1]; j++) {
                if (mat[iter][0] == i && mat[iter][1] == j) {
                    cout << mat[iter][2] << "\t";
                    iter++;
                } else {
                    cout << "0\t";
                }
            }
            cout << endl;
        }
    }

    static SparseMat<int> read(int m, int n) {
        SparseMat<int> mat;
        mat.push_back({m, n, 0});

        for (int i = 0; i < m; i++) {
            cout << "Enter elements of row #" << i + 1 << ": ";
            for (int j = 0; j < n; j++) {
                int val;
                cin >> val;
                if (val != 0) {
                    vector<int> el = {i, j, val};
                    mat.push_back(el);
                    mat[0][2] = mat[0][2] + 1;
                }
            }
        }

        return mat;
    }

    // static SparseMat<int> add(SparseMat<int> m1, SparseMat<int> m2) {
    //     todo
    // }

    static SparseMat<int> trans(SparseMat<int> mat) {
        vector<int> defRow(mat[0].size(), 0);
        SparseMat<int> trans = mat;

        for (int i = 0; i < mat.size(); i++) {
            trans[i][0] = mat[i][1];
            trans[i][1] = mat[i][0];
        }
        return trans;
    }
};

int main() {
    auto mat = MatOps::read(3, 3);
    // cout << "Is sparse: " << (Mat::is_sparse(mat) ? "true" : "false") << endl;
    // SparseMat::print(SparseMat::fast_trans(mat));
    MatOps::print(MatOps::trans(mat));
}
