#include <iostream>
#include <assert.h>
using namespace std;
typedef long long ll;

/*
61156655
0
0

2 4 1 5 7 5 4 3 1 6 0 3 5 5 3 0
2 4 1 5 7 5 


*/

int main() {
    vector<int> goal = {2,4,1,5,7,5,4,3,1,6,0,3,5,5,3,0};
    assert(goal.size() == 16);
    int count = 0;
    for (ll start = pow(8, 8); start < pow(8, 9); start++) {
        count++;
        if (count % 100000 == 0) {
            cout<<count<<endl;
        }
        ll a = start;
        ll b = 0; 
        ll c = 0;
        vector<int> result;
        while (a != 0) {
            b = a % 8; // 2 4
            b = b ^ 5; // 1 5
            c = a / pow(2, b); // 7 5
            b = b ^ c; //  4 3
            b = b ^ 6; // 1 6
            a = a / 8;// 0 3
            result.push_back(b % 8);
        }
        if (result == goal) {
            cout<<"Start Value: "<<start<<endl;
            break;
        }
    }
    /*
    for (auto & n : result) {
        cout<<n<<" ";
    }
    cout<<endl;
    cout<<"Num elements: "<< result.size()<<endl;*/
}
