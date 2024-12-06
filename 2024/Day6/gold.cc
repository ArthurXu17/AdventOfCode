#include <bits/stdc++.h>

using namespace std;

void changeDirection(int& dx, int& dy) {
    if (dx == -1 && dy == 0) {
        dx = 0;
        dy = 1;
    } else if (dx == 0 && dy == 1) {
        dx = 1;
        dy = 0;
    } else if (dx == 1 && dy == 0) {
        dx = 0;
        dy = -1;
    } else if (dx == 0 && dy == -1) {
        dx = -1;
        dy = 0;
    }
}

bool goesOutOfBounds(int x, int y, int dx, int dy, int m, int n) {
    return x + dx < 0 || x + dx >= n || y + dy < 0 || y+dy >= m;
}

bool isLoop(int x, int y, int dx, int dy, int m, int n, vector<string>& grid) {
    int x0 = x;
    int y0 = y;
    int dx0 = dx;
    int dy0 = dy;
    int numTurns = 0;
    int firstStraightLength = -1;
    int reverseStraightLength = -1;
    int curLength = 0;
    while (true) {
        if (goesOutOfBounds(x,y,dx,dy,m,n)) {
            break;
        }
        if (grid[x+dx][y+dy] == '#') {
            changeDirection(dx,dy);
            if (numTurns == 0) {
                numTurns++;
                firstStraightLength = curLength;
                curLength = 0;
            } else if (numTurns == 1) {
                numTurns++;
                curLength = 0;
            } else if (numTurns == 2) {
                reverseStraightLength = curLength;
                if (firstStraightLength == reverseStraightLength) {
                    cout<<"Found solution"<<endl;
                    cout<<"Initial position: "<<x0<<", "<<y0<<endl;
                    cout<<"Initial direction: "<<dx0<<", "<<dy0<<endl;
                    cout<<"Straight Length: "<<firstStraightLength<<endl;
                }
                return firstStraightLength == reverseStraightLength;
            }
        }
        curLength++;
        x += dx;
        y += dy;
    }
    return false;
}

int main() {
    string str;
    vector<string> grid;
    int x, y;
    int i = 0;
    while (cin>>str) {
        grid.push_back(str);
        //cout<<"\""<<str<<"\""<<endl;
        //cout<<str.size()<<endl;
        for (int j = 0; j < str.size(); j++) {
            if (str[j] == '^') {
                x = i;
                y = j;
                //cout<<"Start: "<<x<<", "<<y<<endl;
            }
        }
        i++;
    }
    int n = grid.size();
    int m = grid[0].size();
    //cout<<n<<" x "<< m<<endl;
    int dx = -1;
    int dy = 0;
    int result = 0;
    while (true) {
        if (goesOutOfBounds(x,y,dx,dy,m,n)) {
            break;
        }
        
        if (grid[x+dx][y+dy] == '#') {
            changeDirection(dx,dy);
        } else {
            int new_dx = dx;
            int new_dy = dy;
            changeDirection(new_dx, new_dy);
            if (isLoop(x, y, new_dx, new_dy, m, n, grid)) {
                cout<<"O placement: "<<x+dx<<", "<<y+dy<<endl;
                result++;
            }
        }
        x += dx;
        y += dy;
    }
    cout<<result<<endl;
}

