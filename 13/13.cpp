#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[]) {
    long total = 0;
    string str;
    vector<string> v;
    
    while(getline(cin, str)) {
        if(str.empty()) {
            cout << '\n';
            for(auto s: v) {
                cout << s << '\n';
            }

            for(int i=0; i+1<v[0].size();  ++i) {
                int smudge = 0;
                for(int j=0 ;; ++j) {
                    int nl = i-j, nr = i+j+1;
                    if(0 > nl || nl >= v[0].size()
                    || 0 > nr || nr >= v[0].size()) {
                        break;
                    }

                    for(int k=0; k<v.size(); ++k) {
                        if(v[k][nl] != v[k][nr]) {
                            smudge++;
                        }   
                    }
                }

                if(smudge == 1) {
                    cout << i+1 << '\n';
                    total += i+1;
                }
            }

            for(int i=0; i+1<v.size();  ++i) {
                int smudge = 0;
                for(int j=0 ;; ++j) {
                    int nu = i-j, nd = i+j+1;
                    if(0 > nu || nu >= v.size()
                    || 0 > nd || nd >= v.size()) {
                        break;
                    }

                    for(int k=0; k<v[0].size(); ++k) {
                        if(v[nu][k] != v[nd][k]) {
                            smudge++;
                        }   
                    }
                }

                if(smudge == 1) {
                    cout << 100*(i+1) << '\n';
                    total += 100*(i+1);
                }
            }

            v.clear();
        } else {
            v.push_back(str);
        }
    }

    cout << '\n' << total << '\n';

    return 0;
}