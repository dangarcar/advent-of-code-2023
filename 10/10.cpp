#include <bits/stdc++.h>
using namespace std;

map<char, vector<pair<int,int>>> dirs = {
    {'-', {{0,1},  {0,-1}} },
    {'|', {{1,0},  {-1,0}} },
    {'7', {{1,0},  {0,-1}} },
    {'F', {{1,0},  {0,1}} },
    {'J', {{-1,0}, {0,-1}} },
    {'L', {{-1,0}, {0,1}} },
    {'S', {{0,1}, {0,-1}, {1,0}, {-1,0}}},
    {'.', {}}
};

int main(int argc, char const *argv[]) {
    vector<string> board;
    string buf;
    while(getline(cin, buf)) {
        if(!buf.empty())
            board.push_back(buf);
    }

    int R = board.size(), C = board[0].length();

    for(int i=0; i<R; ++i) {
        for(int j=0; j<C; ++j) {
            if(board[i][j] == 'S') {
                vector<vector<int>> dist(R, vector<int>(C, -1));
                queue<pair<int,int>> q;
                dist[i][j] = 0;

                for(int r=-1; r<=1; ++r) {
                    for(int c=-1; c<=1; ++c) {
                        if(abs(r+c) == 1) {
                            int ni = i+r, nj = j+c;
                            auto ch = board[ni][nj];
                            if(0 <= ni && ni < R
                            && 0 <= nj && nj < C
                            && find_if(dirs[ch].begin(), dirs[ch].end(), [r,c](const auto& p){
                                return r+p.first == 0 && c+p.second == 0;
                            }) != dirs[ch].end()) {
                                dist[ni][nj] = 1;
                                q.push({ni,nj});
                            }
                        }
                    }
                }

                while(!q.empty()) {
                    auto [r,c] = q.front();
                    q.pop();

                    auto ch = board[r][c];

                    for(auto [ir, ic]: dirs[ch]) {
                        int nr = r+ir, nc = c+ic;

                        if(0 <= nr && nr < R
                        && 0 <= nc && nc < C
                        && dist[nr][nc] == -1
                        && board[nr][nc] != '.'){
                            dist[nr][nc] = dist[r][c] +1;
                            q.push({nr,nc});
                        }
                    }
                }

                int ans = -1;
                for(int i=0; i<R; ++i) {
                    for(int j=0; j<C; ++j) {
                        ans = max(ans, dist[i][j]);
                        cout << dist[i][j] << ' ';
                    }
                    cout << '\n';
                }

                cout << ans << '\n';
            }
        }
    }

    return 0;
}
