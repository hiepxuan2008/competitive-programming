#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
int MOD = 1e9 + 7;

#define fin freopen("in.txt", "r", stdin)
#define fout freopen("out.txt", "w", stdout)

struct Matrix {
    vector<vector<ll>> A;
    int rows, cols;

    Matrix(int rows = 0, int cols = 0) : rows(rows), cols(cols) {
        A.resize(rows);
        for (int i = 0; i < rows; ++i) {
            A[i].resize(cols);
            for (int j = 0; j < cols; ++j)
                A[i][j] = 0;
        }
    }
};
Matrix operator*(const Matrix& A, const Matrix& B) {
    Matrix C(A.rows, B.cols);
    for (int i = 0; i < A.rows; ++i) {
        for (int j = 0; j < B.cols; ++j) {
            for (int k = 0; k < A.cols; ++k) {
                C.A[i][j] += A.A[i][k] * B.A[k][j] % MOD;
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

Matrix Identity(int n) {
    Matrix mat(n, n);
    for (int i = 0; i < n; ++i)
        mat.A[i][i] = 1;
    return mat;
}

Matrix fastPow(const Matrix& base, int pow) {
    if (pow == 0) return Identity(base.cols);
    if (pow == 1) return base;
    Matrix tmp = fastPow(base, pow / 2);
    tmp = tmp * tmp;
    if (pow & 1)
        tmp = tmp * base;
    return tmp;
}

int main() {
//    fin;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Matrix mat(2, 2), base(2, 1), tmp;
    mat.A[0][1] = mat.A[1][0] = mat.A[1][1] = 1;
    base.A[1][0] = 1;

    int n, m;
    while (cin >> n >> m) {
        MOD = 1 << m;
        tmp = fastPow(mat, n);
        tmp = tmp * base;
        cout << tmp.A[0][0] << '\n';
    }

    return 0;
}