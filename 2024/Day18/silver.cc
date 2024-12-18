#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

bool inBounds(int a, int b, int n) {
    return 0 <= a && a < n && 0 <= b && b < n;
}

int main() {
    int n = 71;
    vector<vector<bool>> grid(n, vector<bool>(n, false));
    int a,b;
    for (int i = 0; i < 1024; i++) {
        cin >> a >> b;
        //cout<<a<<" "<<b<<endl;
        grid[b][a] = true;
    }
    
    for (int i = 0; i < n; i++ ){
        for (int j = 0; j < n; j++) {
            if (grid[i][j]) {
                cout<<"#";
            } else {
                cout<<".";
            }
        }
        cout<<endl;
    }

    vector<p> directions = {{1,0},{-1,0},{0,1},{0,-1}};
    vector<vector<int>> distance(n, vector<int>(n, -1));
    queue<p> bfs;
    bfs.push(make_pair(0,0));
    distance[0][0] = 0;
    while (!bfs.empty()) {
        auto [x,y] = bfs.front();
        //cout<<x<<", "<<y<<endl;
        bfs.pop();
        for (auto & [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;
            if (inBounds(nx, ny, n) && distance[nx][ny] == -1 && !grid[nx][ny] ) {
                distance[nx][ny] = distance[x][y] + 1;
                bfs.push(make_pair(nx, ny));
            }
        }
    }
    /*for (int i = 0 ; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j]) {
                cout<<"# ";
            } else {
                cout<<distance[i][j]<<" ";
            }
            
        }
        cout<<endl;
    }*/
    cout<<distance[n-1][n-1]<<endl;

    
}
