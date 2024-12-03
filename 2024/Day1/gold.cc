#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    vector<int> arr1;
    unordered_map<int, int> arr2;
    bool is1 = true;
    while (cin >> n) {
        if (is1) {
            arr1.push_back(n);
        } else {
            if (arr2.find(n) == arr2.end()) {
                arr2[n] = 1;
            } else {
                arr2[n]++;
            }
        }
        is1 = !is1;
    }
    int result = 0;
    for (auto & m : arr1) {
        if (arr2.find(m) != arr2.end()) {
            result += arr2[m] * m;
        }
    }
    cout<<result<<endl;
}