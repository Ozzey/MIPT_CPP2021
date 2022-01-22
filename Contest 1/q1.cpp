#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
     
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);
     long double c1 , l1 , c2 , l2;
     cin >> c1 >> l1 >> c2 >> l2;
     struct lines {
          long double l , r;
     };
     lines one , two;
     one.l = c1 - (l1 * 1.0)/ (2 * 1.0) ;
     one.r = c1 + (l1 * 1.0)/ (2 * 1.0) ;
     two.l = c2 - (l2 * 1.0)/ (2 * 1.0) ;
     two.r = c2 + (l2 * 1.0)/ (2 * 1.0) ;
     long double ans = 0.0;
     ans = max(ans , min(one.r , two.r) - max(one.l , two.l) );
     cout << fixed << setprecision(20) << ans << "\n" ;
     return 0;
}
