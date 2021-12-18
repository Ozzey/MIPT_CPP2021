#include <cmath>
#include <bits/stdc++.h>
 
using namespace std;
 
bool double_equal(const double d1, const double d2){
    return fabs(d1-d2)<1e-6;
}
bool double_gt(const double d1, const double d2){
    return (d1-d2) > 1e-6;
}
bool double_gteq(const double d1, const double d2){
    return (d1-d2) >= -1e-6;
}
 
int intersection(double x1, double y1, double x2, double y2, double r1, double r2) {
    double distanceBetweenCenters = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
 
    // inside case
    if (double_gt(r1,distanceBetweenCenters) || double_gt(r2,distanceBetweenCenters) ) {
        // if one circle inside other and it's too small to reach other circle's bound
        if (double_gt(r1,distanceBetweenCenters+r2) || double_gt(r2,distanceBetweenCenters+r1) ) return 0;
        // if one circle inside other and it reaches one bound
        if (double_equal(r2,distanceBetweenCenters+r1)|| double_equal(r1,distanceBetweenCenters+r2)) return 1;
        // if one circle inside other but it intersects
        if (double_gt(distanceBetweenCenters+r1,r2)|| double_gt(distanceBetweenCenters+r2,r1)) return 2;
    }
        // outside case
    else {
        // if circles are far away from each others
        if (double_gt(distanceBetweenCenters,r1+r2)) return 0;
        // if circles are connected by one point
        if (double_equal(distanceBetweenCenters,r1+r2)) return 1;
        // if circles are connected more then one point
        if (double_gt(r1+r2,distanceBetweenCenters)) return 2;
    }
 
    return 0;
}
 
// Driver code
int main() {
    double x1, x2, y1, y2, r1, r2;
    cin >> x1 >> y1 >> r1;
    cin >> x2 >> y2 >> r2;
    if (x1 == x2 && y1 == y2 && r1 == r2) {
        if (r1 == 0) cout << 1;
        else cout << "infinity";
    } else cout << intersection(x1, y1, x2, y2, r1, r2);
    return 0;
}
