#include <iostream>
#include<iomanip>
#include <cmath>
using namespace std;

int main() {
    int n;
    double p;
    double j = 0 ;
    cin >> n;
    cin >> p;
    //cin >> x;
    //cin >> y;
    //cin >> z;

    double r;
    r= 1/p;
    for (int i=1; i<n+1 ; i++) {
        double var;
        cin>>var;
        j = j + (pow(fabs(var),p));
    }
    double v= pow(j,r);
    cout << v <<endl;
    return 0;
}
