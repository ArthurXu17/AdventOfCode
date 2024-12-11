#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

void insert(unordered_map<ll, ll>& stones, ll k) {
    if (stones.find(k) == stones.end()) {
        //cout<<"New Element"<<endl;
        stones[k] = 1;
    } else {
        //cout<<"Old element"<<endl;
        stones[k]++;
    }
}

void erase(unordered_map<ll, ll>& stones, ll k) {
    if (stones.find(k) == stones.end()) {
        cout<<"smth wrong"<<endl;
        return;
    }
    // assume k exists in stones
    if (stones[k] == 1) {
        stones[k] = 0;
    } else {
        stones[k]--;
    }
}


int main() {
    unordered_map<ll, ll> stones;
    ll n;
    while (cin >> n) {
        insert(stones, n);
    }
    /*cout<<"After transformation "<<0<<": "<<endl;
        for (auto & [k,v] : stones) {
            cout<<k<<": "<<v<<endl;
        }
        cout<<endl;*/
    for (int i = 1; i <= 25; i++) {
        auto copy = stones;
        for (auto & [stone, count] : copy) {
            for (int i = 1; i <= count;i++) {
                if (stone == 0) {
                    erase(stones, stone);
                    insert(stones, 1);
                    continue;
                }
                string stoneString = to_string(stone);
                if (stoneString.size() % 2 == 0) {
                    string firstHalf = stoneString.substr(0, stoneString.size() / 2);
                    string secondHalf = stoneString.substr(stoneString.size() / 2);
                    erase(stones, stone);
                    insert(stones, stoull(firstHalf));
                    insert(stones, stoull(secondHalf));
                    continue;
                }
                erase(stones, stone);
                insert(stones, 2024*stone);
            }
        }
        
        /*cout<<"After transformation "<<i<<": "<<endl;
        for (auto & [k,v] : stones) {
            cout<<k<<": "<<v<<endl;
        }
        cout<<endl;*/
        //cout<<"Total Size: "<<stones.size()<<endl;
    }
    ll result = 0;
    for (auto & [_,v] : stones) {
        result += v;
    }
    cout<<result<<endl;
}
