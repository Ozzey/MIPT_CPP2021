#include <bits/stdc++.h>
#define size 3
using namespace std;
//function to calculate dot product of two vectors
double dot_product(double x1, double y1, double x2, double y2) {
    double prod = x1*x2+y1*y2;
    return prod;
}

double cross_product(double x1, double y1, double x2, double y2) {
       double cross_P = x1 * y2 - y1 * x2;
    return cross_P;
}



int main() {
    double x1;
    double x2;
    double y1;
    double y2;

    cin >> x1;
    cin >> x2;
    cin >> y1;
    cin >> y2;

    cout << dot_product(x1,y1,x2,y2) << endl;
    cout << cross_product(x1,y1,x2,y2) << endl;

    return 0;
}
