#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int longestRow(vector<vector<int>> &grid) {
    int maxLength = 0;
    for (int i = 0; i < grid.size(); i++) {
        int curLength = 0;
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] <= 0) {
                curLength = 0;
            } else {
                curLength++;
                maxLength = max(curLength, maxLength);
            }
        }
    }
    return maxLength;
}

void updateGrid(vector<vector<int>>& grid, vector<array<int, 4>>& robots) {
    int m = grid.size();
    int n = grid[0].size();

    for (auto & [x, y, dx, dy] : robots) {
        grid[x][y]--;
        int xf = (x+dx) % m;
        int yf = (y+dy) % n;
        if (xf < 0) {
            xf += m;
        }  
        if (yf < 0) {
            yf += n;
        }
        grid[xf][yf]++;
        x = xf;
        y = yf;
    }
}

int main() {
    int m = 103;
    int n = 101;
    vector<vector<int>> grid(m, vector<int>(n, 0));
    vector<array<int, 4>> robots; 
    /*
    robots[i][0] = x
    robots[i][1] = y
    robots[i][2] = dx
    robots[i][3] = dy
    */
    string str;
    while (getline(cin, str)) {
        for (auto & ch : str) {
            if (!(isdigit(ch) || ch == '-')) {
                ch = ' ';
            }
        }
        istringstream stream(str);
        int x, y, dx, dy;
        stream >> y >> x >> dy >> dx;
        array<int, 4> robot = {x,y,dx,dy};
        robots.push_back(robot);
        grid[x][y]++;
    }
    int maxIterations = 100000;
    int maxRowLength = 0;
    for (int i = 0; i < maxIterations; i++) {
        int curRow = longestRow(grid);
        if (curRow > maxRowLength) {
            cout<<"New Max Row Length of: "<<curRow<<" occured after "<<i<<" iterations"<<endl;
            maxRowLength = curRow;
        }
        updateGrid(grid, robots);
    }

}
