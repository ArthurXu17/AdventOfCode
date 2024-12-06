#include <bits/stdc++.h>

using namespace std;

bool checkXmas(vector<string>& puzzle, int x0, int y0, int dx, int dy) {
    int m = puzzle.size();
    int n = puzzle[0].size();
    if (x0 + 3*dx >= 0 && x0+3*dx < m && y0 + 3*dy >= 0 && y0+3*dy < n) {
        return (puzzle[x0][y0] == 'X' && puzzle[x0+dx][y0+dy] == 'M' && puzzle[x0+2*dx][y0+2*dy] == 'A' && puzzle[x0+3*dx][y0+3*dy] == 'S');
    }
    return false;
}

int main() {
    string str;
    vector<string> puzzle;
    while (getline(cin, str)) {
        puzzle.push_back(str);
    }
    int result = 0;
    for (int i = 1; i < puzzle.size() - 1; i++) {
        for (int j = 1; j < puzzle[i].size() - 1; j++) {
            if (puzzle[i][j] == 'A') {
                unordered_set<int> diag1 = {puzzle[i-1][j-1], puzzle[i+1][j+1]};
                unordered_set<int> diag2 = {puzzle[i+1][j-1], puzzle[i-1][j+1]};
                unordered_set<int> goal = {'M', 'S'};
                if (diag1 == goal && diag2 == goal) {
                    cout<<"A index: "<<i<<", "<<j<<endl;
                    result++;
                }
            }
        }
    }
    cout<<result<<endl;

}