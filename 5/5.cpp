#include <bits/stdc++.h>
using namespace std;

struct range {
    long s,t, w;
};

vector<pair<long,long>> getSeeds() {
    vector<pair<long,long>> seeds;
    string str;
    cin >> str;
    getline(cin, str);
    istringstream iss(str);
    long a,b;
    while(iss >> a >> b) {
        seeds.push_back({a,b});
    }

    return seeds;
}

int main(int argc, char const *argv[]) {
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    string str;
    vector<range> maps [7];
    auto seeds = getSeeds();

    cin.ignore();

    for(int i=0; i<7; ++i) {
        getline(cin, str);
        while(true){
            getline(cin, str);
            if(str.empty())
                break;
            
            long s=0, t=0, w=0;
            istringstream iss (str);
            iss >> t >> s >> w;

            maps[i].push_back(range{s,t,w});
        }
    }

    /*for(auto v: maps) {
        for(auto e: v) {
            cout << e.t << ' ' << e.s << ' ' << e.w << '\n';
        }
        cout << '\n';
    }*/

    queue<pair<long,long>> q;
    vector<pair<long,long>> tmp(seeds);
    long ans = INT64_MAX;
    for(int i=0; i<7; ++i) {
        for(auto p: tmp)
            q.push(p);
        tmp.clear();

        while(!q.empty()) {
            const auto p = q.front();
            q.pop();

            auto l = p.first, r = p.first+p.second-1;

            bool ended = false;
            for(auto w: maps[i]){
                long b = w.s, e = w.s+w.w-1;
                if(b <= l && e >= r) {
                    auto d = l - b;
                    l = w.t + d;
                    tmp.push_back({l, p.second});
                } 
                else if(b >= l && e <= r) {
                    q.push({l, b-l});
                    q.push({e, r-e});

                    tmp.push_back({w.t, w.w});
                }
                else if(b >= l && b <= r) {
                    q.push({l, b-l});

                    tmp.push_back({w.t, r-b});
                }
                else if(e >= l && e <= r) {
                    q.push({e+1, r-e});

                    auto d = l-b;
                    tmp.push_back({w.t+d, e-l});
                } 
                else
                    continue;
                
                ended = true;
                break;
            }

            if(!ended) {
                tmp.push_back(p);
            }
        }
    }

    for(auto e: tmp) {
        cout << e.first << ' ';
        ans = min(ans, e.first);
    }

    cout << "\n\n\n" << ans << '\n';

    return 0;
}