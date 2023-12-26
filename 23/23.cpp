#include <bits/stdc++.h>
using namespace std;

vector<string> board;

int R,C;
int incC[] = {0,0,1,-1};
int incR[] = {1,-1,0,0};

set<long> paths;

void dfs(int r, int c, set<pair<int,int>> visited, set<pair<int,int>> path) {
    if(board[r][c] == '#' || visited.count({r,c})) return;

    visited.insert({r,c});

    if(r == R-1 && board[r][c] == '.') {
        paths.insert(path.size());
        return;
    }

    switch (board[r][c]) {
        case '<': 
            path.insert({r, c-1}); 
            dfs(r, c-1, visited, path);
            path.erase({r, c-1}); 
            break;
        case '>': 
            path.insert({r, c+1}); 
            dfs(r, c+1, visited, path); 
            path.erase({r, c+1}); 
            break;
        case '^': 
            path.insert({r-1, c}); 
            dfs(r-1, c, visited, path);
            path.erase({r-1, c}); 
            break;
        case 'v': 
            path.insert({r+1, c}); 
            dfs(r+1, c, visited, path); 
            path.erase({r+1, c}); 
            break;
        default:
            for(int i=0; i<4; ++i) {
                int nr = r + incR[i];
                int nc = c + incC[i];
                if(0 <= nr && nr < R
                && 0 <= nc && nc < C
                && board[nr][nc] != '#'
                && visited.count({nr,nc}) == 0){
                    path.insert({nr,nc});
                    dfs(nr, nc, visited, path);
                    path.erase({nr,nc});
                }
            }
            break;
    }
}

int main(int argc, char const *argv[]) {    
    string str;
    while(getline(cin, str)) {
        if(str.empty()) continue;
        board.push_back(str);
    }

    R = board.size();
    C = board[0].size();

    dfs(0, 1, {}, {});

    for(auto e: paths) {
        cout << e << '\n';

        /*cout << e.size() << '\n';
        for(int i=0; i<R; ++i) {
            for(int j=0; j<C; ++j) {
                if(e.count({i,j}))
                    cout << 'O';
                else
                    cout << board[i][j];
            }
            cout << '\n';
        }
        cout << '\n';*/
    }
    cout << '\n';

    return 0;
}