#include <bits/stdc++.h>
using namespace std;

/*
Another brute-force with optimizations solution, 8 min 7 s in my WSL2 compiled without optimizations
*/

vector<string> board;

int R,C;
int incC[] = {0,0,1,-1};
int incR[] = {1,-1,0,0};

long ans = 0L;
vector<vector<bool>> visited;

void dfs(int r, int c, long l) {
    if(r == R-1) {
        ans = max(ans, l);
        return;
    }

    visited[r][c] = true;

    for(int i=0; i<4; ++i) {
        int nr = r + incR[i];
        int nc = c + incC[i];
        if(0 <= nr && nr < R
        && 0 <= nc && nc < C
        && board[nr][nc] != '#'
        && visited[nr][nc] == false){
            l++;
            dfs(nr, nc, l);
            l--;
        }
    }

    visited[r][c] = false;
}

int main(int argc, char const *argv[]) {    
    string str;
    while(getline(cin, str)) {
        if(str.empty()) continue;
        board.push_back(str);
    }

    R = board.size();
    C = board[0].size();

    visited.assign(R, vector<bool>(C, false));
    dfs(0, 1, 0L);
    cout << ans << '\n';

    return 0;
}