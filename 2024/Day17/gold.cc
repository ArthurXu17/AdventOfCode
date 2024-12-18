#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;

/*
61156655
0
0

2 4 1 5 7 5 4 3 1 6 0 3 5 5 3 0
2 4 1 5 7 5 


*/

int main() {
    vector<int> overallGoal = {2,4,1,5,7,5,4,3,1,6,0,3,5,5,3,0};

    ll value = 0;
    deque<int> goal;
    for (int i = 1; i <= 16; i++) {
        goal.push_front(overallGoal[16-i]);
        for (ll start = value; start <= value + 80000; start++) {
            ll a = start;
            ll b = 0; 
            ll c = 0;
            deque<int> result;
            while (a != 0) {
                b = a % 8; // 2 4
                ll temp = b ^ 5; // 1 5
                c = a / pow(2, temp); // 7 5
                b = b ^ c; //  4 3
                b = b ^ 3; // 1 6
                a = a / 8;// 0 3
                result.push_back(b % 8);
            }
            if (result == goal) {
                value = start * 8;
                cout<<"Result for starting at : "<<start<<endl;
                bitset<60> s(start);
                cout<<"Binary value: "<<s<<endl;
                cout<<"Resuting output: ";
                for (auto & n : result) {
                    cout<<n<<" ";
                }
                cout<<endl;
                cout<<"Output size: "<<result.size()<<endl;
                break;
            }
        }
    }

}
