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
        if (str[0] != '#') {
            grid.push_back(str);
            continue;
        } 
        string curRow;
        for (auto & ch : str) {
            if (ch == '@' ) {
                curRow.push_back(ch);
                curRow.push_back('.');
            } else if (ch == 'O') {
                curRow.push_back('[');
                curRow.push_back(']');
            } else {
                curRow.push_back(ch);
                curRow.push_back(ch);
            }
        }
        grid.push_back(curRow);
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
            //cout<<grid[i][j];
        }
        //cout<<endl;
    }
    //cout<<"End Grid"<<endl;
    cout<<m<<" x "<<n<<endl;
    cout<<"Initial Position: "<<x<<", "<<y<<endl;
    cout<<"Grid at Initial Position: "<<grid[x][y]<<endl;
    //cout<<instructions<<endl;
    cout<<"Start Iterations"<<endl;
    for (auto & ch : instructions) {
        //cout<<"Movement: "<<ch<<endl;
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
            if (dx == 0 && dy == 1) { // horizontal movement to the right, starts with [
                assert(grid[rockX][rockY] == '[');
                while (grid[rockX][rockY] == '[') {
                    rockY += 2;
                }
                if (grid[rockX][rockY] == '.') {
                    for (int j = rockY; j > y; j--) { // move everything including the player
                        grid[rockX][j] = grid[rockX][j-1];
                    }
                    grid[x][y] = '.';
                    y++;
                }
            } else if (dx == 0 && dy == -1) { // horizontal movement to the left, look for [
                assert(grid[rockX][rockY] == ']');
                while (grid[rockX][rockY] == ']') {
                    rockY -= 2;
                }
                if (grid[rockX][rockY] == '.') {
                    for (int j = rockY; j < y; j++) { // move everything including the player
                        grid[rockX][j] = grid[rockX][j+1];
                    }
                    grid[x][y] = '.';
                    y--;
                }
            } else {
                // do bfs on rocks, use [ as the coordinate
                int initialX = rockX;
                int initialY = rockY;
                if (grid[initialX][initialY] == ']') {
                    initialY--;
                }
                assert(grid[initialX][initialY] == '[');
                bool moveRocks = true;
                queue<p> bfs;
                set<p> visited;
                bfs.push(make_pair(initialX, initialY));
                visited.insert(make_pair(initialX, initialY));
                while (!bfs.empty()) {
                    auto [curX, curY] = bfs.front();
                    bfs.pop();
                    assert(grid[curX][curY] == '[');
                    if (grid[curX + dx][curY] == '#' || grid[curX + dx][curY + 1] == '#') {
                        moveRocks = false;
                        break;
                    }
                    // 3 cases
                    /* []
                        []

                        []
                        []

                         []
                        []
                    */
                    // middle case, only 1 neighbour
                    if (grid[curX+dx][curY] == '[' && visited.find(make_pair(curX+dx, curY)) == visited.end()) {   
                        bfs.push(make_pair(curX+dx, curY));
                        visited.insert(make_pair(curX+dx, curY));
                        continue;
                    }

                    if (grid[curX+dx][curY - 1] == '[' && visited.find(make_pair(curX+dx, curY - 1)) == visited.end()) {   
                        bfs.push(make_pair(curX+dx, curY - 1));
                        visited.insert(make_pair(curX+dx, curY - 1));
                    }

                    if (grid[curX+dx][curY + 1] == '[' && visited.find(make_pair(curX+dx, curY + 1)) == visited.end()) {   
                        bfs.push(make_pair(curX+dx, curY + 1));
                        visited.insert(make_pair(curX+dx, curY + 1));
                    }
                }
                if (moveRocks) {
                    if (dx == 1) {
                        // when moving upwards (in negative x), move rocks with lowest x values last
                        for (auto it = visited.rbegin(); it != visited.rend(); it++) {
                            auto [curX, curY] = *it;
                            grid[curX + dx][curY] = '[';
                            grid[curX + dx][curY + 1] = ']';
                            grid[curX][curY] = '.';
                            grid[curX][curY + 1] = '.';
                        }

                    } else if (dx == -1) {
                        // when moving upwards (in negative x), move rocks with lowest x values first
                        for (auto it = visited.begin(); it != visited.end(); it++) {
                            auto [curX, curY] = *it;
                            grid[curX + dx][curY] = '[';
                            grid[curX + dx][curY + 1] = ']';
                            grid[curX][curY] = '.';
                            grid[curX][curY + 1] = '.';
                        }
                    }
                    // move player
                    grid[x][y] = '.';
                    x+=dx;
                    y+=dy;
                    grid[x][y] = '@';
                }
            }
        }
        /*
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout<<grid[i][j];
            }
            cout<<endl;
        }
        cout<<"End Grid"<<endl;*/

    }
    cout<<endl;
    long long result;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '[') {
                result += 100*i + j;
            }
            cout<<grid[i][j];
        }
        cout<<endl;
    }
    cout<<"End Grid"<<endl;
    cout<<result<<endl;
}
