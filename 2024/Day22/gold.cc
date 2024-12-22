#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll bananasBySequence(vector<int>& sequence, vector<map<vector<int>, int>>& memo) {
    ll result = 0;
    int i = 0;
    for (auto & buyerMap : memo) {
        if (buyerMap.count(sequence)) {
            result += buyerMap[sequence];
        }
    }
    return result;
}

vector<map<vector<int>, int>> getSequenceOccurences(vector<vector<int>> & prices) {
    vector<map<vector<int>, int>> result(prices.size(), map<vector<int>, int>()); // result[i][sequence] is bannas sold after the first occurence of sequence for the ith buyer
    for (int i = 0; i < prices.size(); i++) {
        vector<int> buyerPrice = prices[i];
        for (int j = 4; j < buyerPrice.size(); j++){
            vector<int> curSequence = {
                buyerPrice[j-3] - buyerPrice[j-4],
                buyerPrice[j-2] - buyerPrice[j-3],
                buyerPrice[j-1] - buyerPrice[j-2],
                buyerPrice[j] - buyerPrice[j-1]
            };
            if (result[i].find(curSequence) == result[i].end()) {
                result[i][curSequence] = buyerPrice[j];
            }
        }
    }
    return result;
}

int main() {
    int k;
    vector<int> nums;
    vector<vector<int>> sequences;
    for (int i = -9; i <= 9; i++) {
        for (int j = -9; j <= 9; j++) {
            for (int k = -9; k <= 9; k++) {
                for (int l = -9; l <= 9; l++) {
                    sequences.push_back({i,j,k,l});
                }
            }
        }
    }
    
    while (cin>>k) {
        nums.push_back(k);
    }
    vector<vector<int>> prices; // prices[i] = prices of ith buyer 
    for (auto & m : nums) {
        vector<int> curBuyerPrices;
        ll n = m;
        for (int i = 1; i <= 2000; i++) {
            n = (64*n) ^ n;
            n %= 16777216;
            n = (n / 32) ^ n;
            n %= 16777216;
            n = (2048*n) ^ n;
            n %= 16777216;
            curBuyerPrices.push_back(n % 10);
        }
        prices.push_back(curBuyerPrices);
    }
    ll result = 0;
    cout<<sequences.size()<<endl;
    auto memo = getSequenceOccurences(prices);
    /*vector<int> goalSequence = {-2,1,-1,3};
    for (int i = 0; i < 4; i++) {
        if (memo[i].count(goalSequence)) {
            cout<<i<<": "<<memo[i][goalSequence]<<endl;
        } else {
            cout<<i<<": sequence not found"<<endl;
        }
    }*/
    
    int i = 0;
    for (auto & s : sequences) {
        if (i % 100 == 0) {
            cout<<i<<endl;
        }
        i++;
        result = max(result, bananasBySequence(s, memo));
    }
    cout<<result<<endl;
}
