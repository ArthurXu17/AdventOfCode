#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    int k;
    vector<int> nums;
    while (cin>>k) {
        nums.push_back(k);
    }
    ll result = 0;
    for (auto & m : nums) {
        ll n = m;
        for (int i = 1; i <= 2000; i++) {
            n = (64*n) ^ n;
            n %= 16777216;
            n = (n / 32) ^ n;
            n %= 16777216;
            n = (2048*n) ^ n;
            n %= 16777216;
        }
        cout<<n<<endl;
        result += n;
    }
    cout<<result<<endl;
}
