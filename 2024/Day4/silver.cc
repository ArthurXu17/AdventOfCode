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
    for (int i = 0; i < puzzle.size(); i++) {
        for (int j = 0; j < puzzle[i].size(); j++) {
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) {
                        continue;
                    }
                    result += checkXmas(puzzle, i, j, dx, dy);
                }
            }
        }
    }
    cout<<result<<endl;

}
