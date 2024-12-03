#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    vector<int> arr1;
    vector<int> arr2;
    bool is1 = true;
    while (cin >> n) {
        if (is1) {
            arr1.push_back(n);
        } else {
            arr2.push_back(n);
        }
        is1 = !is1;
    }
    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());
    int result;   
    for (int i = 0; i <arr1.size(); i++) {
        result += abs(arr1[i] - arr2[i]);
    }
    cout<<result<<endl;
}