#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> p;

p getDirection(char ch) {
    if (ch == '<') {
        return make_pair(0, -1);
    } else if (ch == '>') {
        return make_pair(0, 1);
    } else if (ch == 'v') {
        return make_pair(1,0);
    } else if (ch == '^') {
        return make_pair(-1, 0);
    } else {
        return make_pair(0,0);
    }
}


int main() {
    vector<string> grid;
    string str;
    int x, y;
    while (cin >> str) {
        grid.push_back(str);
    }
    string instructions = grid.back();
    grid.pop_back();
    int m = grid.size();
    int n = grid[0].size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '@') {
                x = i;
                y = j;
            }
            cout<<grid[i][j];
        }
        cout<<endl;
    }
    cout<<"End Grid"<<endl;
    cout<<m<<" x "<<n<<endl;
    cout<<x<<", "<<y<<endl;
    cout<<instructions<<endl;
    for (auto & ch : instructions) {
        assert(grid[x][y] == '@');
        auto [dx, dy] = getDirection(ch);
        if (grid[x+dx][y+dy] == '#') {
            continue;
        } else if (grid[x+dx][y+dy] == '.') {
            grid[x][y] = '.';
            x += dx;
            y += dy;
            grid[x][y] = '@';
        } else {
            // rocks
            int rockX = x+dx;
            int rockY = y+dy;
            while (grid[rockX][rockY] == 'O') {
                rockX += dx;
                rockY += dy;
            }
            if (grid[rockX][rockY] == '.') {
                grid[rockX][rockY] = 'O';
                grid[x][y] = '.';
                x += dx;
                y += dy;
                grid[x][y] = '@';
            }
            // otherwise it is wall and nothing happens
        }
    }
    long long result;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'O') {
                result += 100*i + j;
            }
            cout<<grid[i][j];
        }
        cout<<endl;
    }
    cout<<"End Grid"<<endl;
    cout<<result<<endl;
}
