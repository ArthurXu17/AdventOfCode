#include <bits/stdc++.h>
typedef long long ll;
using namespace std;


int main() {
    int m = 103;
    int n = 101;
    ll t = 100;
    vector<vector<int>> grid(m, vector<int>(n, 0));
    string str;
    while (getline(cin, str)) {
        for (auto & ch : str) {
            if (!(isdigit(ch) || ch == '-')) {
                ch = ' ';
            }
        }
        istringstream stream(str);
        ll x, y, dx, dy;
        stream >> y >> x >> dy >> dx;
        int xf = (x+t*dx) % m;
        int yf = (y+t*dy) % n;
        if (xf < 0) {
            xf += m;
        }  
        if (yf < 0) {
            yf += n;
        }
        grid[xf][yf]++;
    }
    ll q1 = 0;
    ll q2 = 0;
    ll q3 = 0;
    ll q4 = 0;
    for (int i = 0; i < m / 2; i++) {
        for (int j = 0; j < n / 2; j++) {
            q1+=grid[i][j];
        }
    }

    
    for (int i = 0; i < m / 2; i++) {
        for (int j = n/2  + 1; j < n; j++) {
            q2+=grid[i][j];
        }
    }

    for (int i = m / 2 + 1; i < m; i++) {
        for (int j = 0; j < n / 2; j++) {
            q3+=grid[i][j];
        }
    }

    for (int i = m / 2 + 1; i < m; i++) {
        for (int j = n/2  + 1; j < n; j++) {
            q4+=grid[i][j];
        }
    }
    /*
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j]) {
                cout<<grid[i][j];
            } else {
                cout<<'.';
            }
        }
        cout<<endl;
    }
    cout<<"Q1: "<<q1<<endl;
    cout<<"Q2: "<<q2<<endl;
    cout<<"Q3: "<<q3<<endl;
    cout<<"Q4: "<<q4<<endl;*/
    cout << q1 * q2 * q3 * q4 <<endl;
}
