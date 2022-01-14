#include <bits/stdc++.h>
#define size 3
using namespace std;


double perimeter(size_t n,const double* x, const double* y){

    double peri= 0;
    peri += sqrt(pow(x[n-1]-x[0],2) + pow(y[n-1]-y[0],2)) ;
    for (int i=0 ; i<n-1; i++) {
        peri+= sqrt(pow(x[i+1]-x[i],2) + pow(y[i+1]-y[i],2));
    }

    //cout << pow(x[2]-x[1],2) << endl;
    //cout << pow(y[2]-y[1],2) << endl;

    return peri;

}

double area(size_t n, const double* x, const double* y){
    double ar=0.0;

    int j = n-1;
    for(int i=0; i<n; i++){
        ar +=  (x[j]+x[i])*(y[j]-y[i]);
        j=i;
    }
    return abs(ar/2.0);
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
