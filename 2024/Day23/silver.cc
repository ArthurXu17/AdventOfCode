#include <bits/stdc++.h>

using namespace std;

int codeToInt(string& str) {
    if (str.size() == 2) {
        int a = str[0] - 'a';
        int b = str[1] - 'a';
        return 26*a + b;
    } else {
        cout<<"Smth wrong with str: "<<str<<endl;
        assert(false);
        return -1;
    }
}

bool startsWithT(int n) {
    return n / 26 == ('t' - 'a');
}

bool atLeastOneT(int a, int b, int c) {
    return startsWithT(a) || startsWithT(b) || startsWithT(c);
}

int main() {
    int total = 26*26;
    string sa, sb;
    vector<unordered_set<int>> neighbours(total, unordered_set<int>());
    while (cin >> sa >> sb) {
        int a = codeToInt(sa);
        int b = codeToInt(sb);
        neighbours[a].insert(b);
        neighbours[b].insert(a);
    }
    int count = 0;
    for (int i = 0; i < total; i++) {
        for (int j = i + 1; j < total; j++) {
            for (int k = j + 1; k < total; k++) {
                if (neighbours[i].count(j) && neighbours[j].count(k) && neighbours[k].count(i) && atLeastOneT(i, j, k)) {
                    count++;
                }
            }
        }
    }
    cout<<"Done"<<endl;
    cout<<"Count: "<<count<<endl;
}
