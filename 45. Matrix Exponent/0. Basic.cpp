#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

struct Matrix {
    vector<vector<ll>> A;
    int rows, cols;

    Matrix(int n = 0, int m = 0) : rows(n), cols(m) {
        A.resize(n);
        for (int i = 0; i < n; ++i) {
            A[i].resize(m);
            for (int j = 0; j < m; ++j)
                A[i][j] = 0;
        }
    }
};
Matrix operator*(const Matrix& A, const Matrix& B) {
    Matrix C(A.rows, B.cols);
    for (int i = 0; i < A.rows; ++i) {
        for (int j = 0; j < B.cols; ++j) {
            for (int k = 0; k < A.cols; ++k) {
                C.A[i][j] += A.A[i][k] * B.A[k][j];
            }
        }
    }
    return C;
}

ostream& operator<<(ostream& os, const Matrix& matrix) {
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j)
            os << matrix.A[i][j] << " ";
        cout << '\n';
    }
}

int main() {
    //    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    return 0;
}