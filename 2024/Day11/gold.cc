#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

void insert(unordered_map<ll, ll>& stones, ll k, ll count) {
    if (stones.find(k) == stones.end()) {
        //cout<<"New Element"<<endl;
        stones[k] = count;
    } else {
        //cout<<"Old element"<<endl;
        stones[k]+=count;
    }
}

void erase(unordered_map<ll, ll>& stones, ll k, ll count) {
    if (stones.find(k) == stones.end() || stones[k] < count) {
        cout<<"smth wrong"<<endl;
        return;
    }
    // assume k exists in stones
    if (stones[k] == count) {
        stones[k] = 0;
    } else {
        stones[k]-=count;
    }
}


int main() {
    unordered_map<ll, ll> stones;
    ll n;
    while (cin >> n) {
        insert(stones, n, 1);
    }
    /*cout<<"After transformation "<<0<<": "<<endl;
        for (auto & [k,v] : stones) {
            cout<<k<<": "<<v<<endl;
        }
        cout<<endl;*/
    for (int i = 1; i <= 75; i++) {
        cout<<i<<endl;
        auto copy = stones;
        for (auto & [stone, count] : copy) {
            if (stone == 0) {
                erase(stones, stone, count);
                insert(stones, 1, count);
                continue;
            }
            string stoneString = to_string(stone);
            if (stoneString.size() % 2 == 0) {
                string firstHalf = stoneString.substr(0, stoneString.size() / 2);
                string secondHalf = stoneString.substr(stoneString.size() / 2);
                erase(stones, stone, count);
                insert(stones, stoull(firstHalf), count);
                insert(stones, stoull(secondHalf), count);
                continue;
            }
            erase(stones, stone, count);
            insert(stones, 2024*stone, count);
        }
        ll curcount = 0;
        for (auto & [_,v] : stones) {
            curcount += v;
        }
        cout<<"Current Size: "<<curcount<<endl;
        cout<<"Number of distinct stones: "<<stones.size()<<endl;
        
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
