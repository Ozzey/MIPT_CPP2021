#include <bits/stdc++.h>
#define size 3
using namespace std;


double area(const size_t n,const double* x, const double* y){
    double sum = 0;
    if (n >= 3)
        for (int i = 0; i < n; i ++)
            sum += x[i] * y[(i + 1) % n] - x[(i + 1) % n] * y[i];
    sum /= (double)2;
    return (sum > 0 ? sum : - sum);
}

double perimeter(const size_t n, const double* x, const double* y){
    double perm=0.0;
    for (int i = 0; i < n; i ++) {
        const double vec_x = x[(i + 1) % n] - x[i];
        const double vec_y = y[(i + 1) % n] - y[i];
        perm+= sqrt(dot_product(vec_x, vec_y, vec_x, vec_y));
    }
    return perm;
}


int main() {
    size_t n;
    double* x ;
    double* y;
    x = new double[n];
    y = new double[n];
    n=4;

    x[0]=0;
    x[1]=0;
    x[2]=4;
    x[3]=4;
    y[0]=0;
    y[1]=2;
    y[2]=2;
    y[3]=0;

    cout << perimeter(n, x, y)<< endl;
    cout << area(n,x,y)<<endl;
    return 0;
}
