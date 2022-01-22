#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);
     int n;
     cin >> n;
     int p = 1;
     int ans[n][n];
     int curr = 1;
     for(int i = 0;i<n;i++){
          
          if(p==1){
               int ci = 0 , cj = i;
               while(ci < n and cj >= 0){
                    
                    ci++;
                    cj--;
               }
               ci--;
               cj++;
               while(ci >= 0 and cj < n){

                    ans[ci][cj] = curr++;
                    ci--;
                    cj++;
               }
          } else {
               int ci = 0 , cj = i;
               while(ci < n and cj >= 0){
                    
                    ans[ci][cj] = curr++;
                    ci++;
                    cj--;
               }
          }
          p = 1 - p;
     }
     for(int i = 1;i<n;i++){
          int minadd = i + 1;
          if(p==1){
               int ci = i , cj = n-1;
               while(ci < n and cj >= 0){
                    ci++;
                    cj--;
               }
               ci--;
               cj++;
               while(ci >= 0 and cj < n){
                    ans[ci][cj] = curr++;
                    ci--;
                    cj++;
               }
          } else {
               int ci = i , cj = n-1;
               while(ci < n and cj >= 0){
                    ans[ci][cj] = curr++;
                    ci++;
                    cj--;
               }
          }
          p = 1 - p;
     }
     for(int i = 0;i<n;i++){
          for(int j = 0;j<n;j++){
               cout << ans[i][j] << ' ' ;
          }
          cout << "\n" ;
     }
     return 0;
}
