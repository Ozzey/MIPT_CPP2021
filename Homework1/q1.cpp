#include <iostream>
using namespace std;

int main() {
    int  i,j,n,x,y ;
    int c=0;

    cin>>n>>x>>y;

    int ar[8][2]={{x+1,y+2}, {x+1,y-2} , {x-1,y+2}, {x-1,y-2}, {x+2,y+1}, {x+2,y-1}, {x-2,y+1}, {x-2, y-1}};

    for(int i=0;i<8;i++) {
        if((0<=ar[i][0]) && (ar[i][0]<n) && (0<=ar[i][1]) && ( ar[i][1]<n)){
            c=c+1;
            //cout<<ar[i][0]<<",";
            //cout<<ar[i][1]<<"\n";
        } else continue;
    }
    cout<<c;
    return 0;
}
