#include <bits/stdc++.h>
#define size 3
using namespace std;
//function to calculate dot product of two vectors
double dot_product(double x1, double y1, double x2, double y2) {
    double vector_a[] = {x1,y1};
    double vector_b[] = {x2,y2};
    double product = 0;
    for (int i = 0; i < size; i++)
        product = product + vector_a[i] * vector_b[i];

    return product;
}

double cross_product(double x1, double y1, double x2, double y2) {
    double vector_a[] = {x1, y1};
    double vector_b[] = {x2, y2};

    double cross_P = vector_a[0]*vector_b[1] - vector_b[0]*vector_a[1];
    return cross_P;
}



int main() {
    double x1;
    double x2;
    double y1;
    double y2;
    const double* x = new double [1,1,2,2];
    const double* y = new double [1,2,1,2];
    size_t n;

    cin >> x1;
    cin >> x2;
    cin >> y1;
    cin >> y2;
    n=4;

    cout << dot_product(x1,y1,x2,y2) << endl;
    cout << cross_product(x1,y1,x2,y2) << endl;
    cout << perimeter(n, x, y);

    return 0;
}
