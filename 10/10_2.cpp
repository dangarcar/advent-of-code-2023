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

map<char, vector<string>> pats = {
    {'-', {"...","X-X","..."}},
    {'|', {".X.",".|.",".X."}},
    {'7', {"...","X7.",".X."}},
    {'F', {"...",".FX",".X."}},
    {'J', {".X.","XJ.","..."}},
    {'L', {".X.",".LX","..."}},
    {'S', {".X.","XSX",".X."}},
    {'.', {"...","...","..."}}
};

int R, C;
vector<string> boardBig;

int incR[] = {0,0,1,-1};
int incC[] = {1,-1,0,0};
 
void fill(int r, int c, char ch) {
    boardBig[r][c] = ch;

    for(int i=0; i<4; ++i) {
        int nr = r+incR[i];
        int nc = c+incC[i];

        if(0 <= nr && nr < R*3
        && 0 <= nc && nc < C*3
        && boardBig[nr][nc] == '.') {
            fill(nr, nc, ch);
        }
    }
}

int main(int argc, char const *argv[]) {
    vector<string> board;
    string buf;
    while(getline(cin, buf)) {
        if(!buf.empty())
            board.push_back(buf);
    }

    R = board.size(), C = board[0].length();

    //Search for loop
    vector<vector<int>> dist(R, vector<int>(C, -1));
    boardBig.assign(R*3, string(C*3, '.'));
    for(int i=0; i<R; ++i) {
        for(int j=0; j<C; ++j) {
            if(board[i][j] == 'S') {
                queue<pair<int,int>> q;
                dist[i][j] = 0;

                for(int r=-1; r<=1; ++r) {
                    for(int c=-1; c<=1; ++c) {
                        if(abs(r+c) == 1) {
                            int ni = i+r, nj = j+c;
                            if(0 <= ni && ni < R
                            && 0 <= nj && nj < C) {
                                auto ch = board[ni][nj];
                                if(find_if(dirs[ch].begin(), dirs[ch].end(), [r,c](const auto& p){
                                    return r+p.first == 0 && c+p.second == 0;
                                }) != dirs[ch].end()) {
                                    dist[ni][nj] = 1;
                                    q.push({ni,nj});
                                }
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

                break;
            }
        }
    }
    
    for(int i=0; i<R; ++i) {
        for(int j=0; j<C; ++j) {
            if(dist[i][j] != -1) {
                auto ch = board[i][j];
                for(int k=0; k<3; ++k) {
                    for(int l=0; l<3; ++l) {
                        boardBig[i*3+k][j*3+l] = pats[ch][k][l];
                    }
                }
            }
        }
    }

    fill(0, 0, ' '); //Remove background

    /*for(auto v: boardBig) {
        for(auto e: v) {
            cout << e;
        }
        cout << '\n';
    }*/

    auto ans = 0;
    for(int i=0; i<R; ++i) {
        for(int j=0; j<C; ++j) {
            if(boardBig[i*3+1][j*3+1] == ' ') {
                cout << ' ';
            }
            else if(dist[i][j] == -1) { //Not in the loop but not outside the loop either
                ans++;
                cout << 'I';
            }
            else {
                cout << board[i][j];
            }
        }
        cout << '\n';
    }
    cout << ans << '\n';

    return 0;
}
