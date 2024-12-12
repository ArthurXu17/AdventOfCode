#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> p;
typedef long long ll;

bool inBounds(int x, int y, int m, int n) {
    return x >= 0 && x < m && y >= 0 && y < n;
}

void countEdgesAlongRows(vector<vector<int>>& myGrid, vector<int>& numEdges, int dx) {
    int m = myGrid.size();
    int n = myGrid[0].size();
    // dx = -1 for looking up, dx = 1 for looking below
    int start = 0;
    int end = m-2;
    if (dx == -1) {
        start++;
        end++;
    }
    // comments assume dx == 1
    for (int r = start; r <= end; r++) {
        for (int c = 0; c < n - 1; c++) {
            // 8 possibile configurations
            // No edges ending at index c
            // c c+1
            /* A A         A B         A A         A B         A A
               A A    or   A A    or   A B    or   A B    or   B B
            */
            // edges ending at index c
            /* A A          A B          A B
               B A    or    B B    or    B A
            */

            if (myGrid[r][c] == myGrid[r+dx][c]) {
                continue;
            }
            // assume myGrid[r][c] != myGrid[r+1][c]
            // first condition handles 1 + 2, second condition handles case 3
            if (myGrid[r][c+1] == myGrid[r+dx][c+1] || myGrid[r][c] != myGrid[r][c+1]) {
                numEdges[myGrid[r][c]]++;
                continue;
            }
        }
        // for myGrid[r][n-1], just check row below doesn't match
        if (myGrid[r][n-1] != myGrid[r+dx][n-1]) {
            numEdges[myGrid[r][n-1]]++;
        }
    }

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
    vector<vector<int>> myGrid (m, vector<int>(n, -1));
    vector<int> numNodes;
    int id = 0;
    for (int i = 0 ; i < m ; i++) {
        for (int j = 0 ; j < n; j++) {
            if (visited[i][j]) {
                continue;
            }
            // bfs rooted at i,j
            //cout<<"Bfs Rooted at: "<<i<<", "<<j<<endl;
            queue<p> q;
            int componentNodes = 0;
            q.push(make_pair(i,j));
            visited[i][j] = true;
            char curCharacter = grid[i][j];
            while (!q.empty()) {
                componentNodes++;
                p curNode = q.front();
                q.pop();
                int x = curNode.first;
                int y = curNode.second;
                myGrid[x][y] = id;
                //cout<<"Cur Node: "<<x<<", "<<y<<endl;
                for (auto & d : directions) {
                    int dx = d.first;
                    int dy = d.second;
                    int new_x = x + dx;
                    int new_y = y + dy;
                    if (inBounds(new_x, new_y, m, n) && grid[new_x][new_y] == curCharacter && !visited[new_x][new_y]) {
                        visited[new_x][new_y] = true;
                        q.push(make_pair(new_x, new_y));
                    } 
                }
            }
            //cout<<"Perimeter: "<<componentEdges<<endl;
            //cout<<"Area: "<<componentNodes<<endl;
            numNodes.push_back(componentNodes);
            id++;
        }
    }
    // final value of id is total number of ids used
    vector<int> numEdges(id, 0);
    
    // handle top row/ bottom row, left edge, right edge individually

    // top row
    int curId = myGrid[0][0];
    for (int i = 0; i < n; i++) {
        if (myGrid[0][i] != curId) {
            numEdges[curId]++;
            curId = myGrid[0][i];
        }
    }
    numEdges[curId]++;
    // bottom row
    curId = myGrid[m-1][0];
    for (int i = 0; i < n; i++) {
        if (myGrid[m-1][i] != curId) {
            numEdges[curId]++;
            curId = myGrid[m-1][i];
        }
    }
    numEdges[curId]++;
    // left column
    curId = myGrid[0][0];
    for (int i = 0; i < m; i++) {
        if (myGrid[i][0] != curId) {
            numEdges[curId]++;
            curId = myGrid[i][0];
        }
    }
    numEdges[curId]++;
    // right column
    curId = myGrid[0][n-1];
    for (int i = 0 ; i < m ; i++) {
        if (myGrid[i][n-1] != curId) {
            numEdges[curId]++;
            curId = myGrid[i][n-1];
        }
    }
    numEdges[curId]++;

    countEdgesAlongRows(myGrid, numEdges, 1);
    countEdgesAlongRows(myGrid, numEdges, -1);
    vector<vector<int>> transpose(n, vector<int>(m, 0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            transpose[j][i] = myGrid[i][j];
        }
    }
    countEdgesAlongRows(transpose, numEdges, 1);
    countEdgesAlongRows(transpose, numEdges, -1);

    /*for (int i = 0; i < m; i++) {
        for (int j = 0 ; j < n ; j++) {
            cout<<myGrid[i][j];
        }
        cout<<endl;
    }
    cout<<"Area: "<<endl;
    for (int i = 0; i < id; i++) {
        cout<<i<<": "<<numNodes[i]<<endl;
    }
    cout<<"Edges: "<<endl;
    for (int i = 0; i < id; i++) {
        cout<<i<<": "<<numEdges[i]<<endl;
    }*/

    
    int cost = 0;
    for (int i = 0; i < numNodes.size(); i++) {
        cost += numNodes[i] * numEdges[i];
    }
    cout<<cost<<endl;
}
