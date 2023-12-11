#include <bits/stdc++.h>
using namespace std;

int incI[] = {1,1,1,-1,-1,-1,0,0};
int incJ[] = {0,1,-1,0,1,-1,1,-1};

int main(int argc, char const *argv[])
{
    
    vector<string> board;
    string str;
    int i = 0;
    while(cin >> str) {
        board.push_back(str);
        ++i;
    }

    int C = board[0].length(), R = board.size();
    int total = 0;

    for(int i=0; i<R; ++i) {
        for(int j=0; j<C; ++j) {
            if(board[i][j] == '*') {
                vector<int> nums;

                for(int k=0; k<8; ++k) {
                    int ni = i+incI[k];
                    int nj = j+incJ[k];

                    if(0 <= ni && ni < R
                    && 0 <= nj && nj < C
                    && isdigit(board[ni][nj])) {
                        while(nj > 0 && isdigit(board[ni][nj-1]))
                            --nj;
                        
                        int n = 0;
                        while(nj < C && isdigit(board[ni][nj])) {
                            n *= 10;
                            int a = board[ni][nj] - '0';
                            n += a;

                            board[ni][nj] = '.';
                            nj++;
                        }

                        nums.push_back(n);
                    }
                }

                if(nums.size() == 2) {
                    int n = nums[0] * nums[1];
                    cout << nums[0] << '*' << nums[1] << '=' << n << '\n';
                    total += n;
                }
            }
        }
    }

    cout << '\n' << total << '\n';

    return 0;
}