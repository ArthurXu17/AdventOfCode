#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> p;
typedef long long ll;

bool inBounds(int x, int y, int m, int n) {
    return x >= 0 && x < m && y >= 0 && y < n;
}

int main() {
    vector<string> grid;
    string str;
    while (cin>>str) {
        grid.push_back(str);
    }
    vector<p> directions = {{1,0}, {-1,0}, {0,-1}, {0,1}};
    int m = grid.size();
    int n = grid[0].size();
    int result = 0;
    cout<<m<<" x "<<n<<endl;
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    ll cost = 0;
    for (int i = 0 ; i < m ; i++) {
        for (int j = 0 ; j < n; j++) {
            if (visited[i][j]) {
                continue;
            }
            // bfs rooted at i,j
            //cout<<"Bfs Rooted at: "<<i<<", "<<j<<endl;
            queue<p> q;
            ll componentNodes = 0;
            ll componentEdges = 0;
            q.push(make_pair(i,j));
            visited[i][j] = true;
            char curCharacter = grid[i][j];
            while (!q.empty()) {
                componentNodes++;
                p curNode = q.front();
                q.pop();
                int x = curNode.first;
                int y = curNode.second;
                //cout<<"Cur Node: "<<x<<", "<<y<<endl;
                for (auto & d : directions) {
                    int dx = d.first;
                    int dy = d.second;
                    int new_x = x + dx;
                    int new_y = y + dy;
                    if (inBounds(new_x, new_y, m, n)) {
                        if (grid[new_x][new_y] == curCharacter) {
                            if (!visited[new_x][new_y]) {
                                visited[new_x][new_y] = true;
                                q.push(make_pair(new_x, new_y));
                            }
                        } else {
                            componentEdges++;
                        }
                    } else {
                        componentEdges++;
                    }
                }
            }
            //cout<<"Perimeter: "<<componentEdges<<endl;
            //cout<<"Area: "<<componentNodes<<endl;
            cost += componentEdges * componentNodes;
        }
    }
    cout<<cost<<endl;
}
