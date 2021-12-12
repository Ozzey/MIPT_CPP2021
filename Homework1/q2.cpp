#include <bits/stdc++.h>
using namespace std;

int main() {
    int o = 0;
    int c = 0;
    int n;
    cin >> n;
    vector <vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                matrix[i][j] = n;
                o = 1;
                c = 1;
            }
            else {
                if (!o) {
                    matrix[i][j] = n - i + c;
                    c++;
                }
                else {
                    matrix[i][j] = n - c;
                    c++;
                }
            }
        }
        c = 0;
        o = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
