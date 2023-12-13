#include <bits/stdc++.h>
using namespace std;

struct Data {
    long i, cnt, perm;
};

long arrangements(const string str, const vector<int>& groups) {
    map<pair<long, long>, long> m;
    m[make_pair(0,0)] = 1;

    for(auto c: str) {
        vector<Data> next;
        for(auto [g, perm]: m) {
            auto [i, cnt] = g;

            if(c != '#') {
                if(cnt == 0) {
                    next.push_back({i, cnt, perm});
                } else if(cnt == groups[i]) {
                    next.push_back({i+1, 0, perm});
                }
            }
            if(c != '.') {
                if(i < groups.size() && cnt < groups[i]) {
                    next.push_back({i, cnt+1, perm});
                }
            }
        }

        m.clear();

        for(auto d: next) {
            m[make_pair(d.i, d.cnt)] += d.perm;
        }
    }

    long ans = 0;
    for(auto [g, perm]: m) {
        auto [i, cnt] = g;
        if(i == groups.size() || (i == groups.size()-1 && cnt == groups[i])) {
            ans += perm;
        }
    }
    return ans;
}

string unfold(const string& str) {
    string ans(str);
    for(int i=0; i<4; ++i) {
        ans += '?';
        ans += str;
    }

    return ans;
}

int main(int argc, char const *argv[]) {
    string buf;
    int number=0;

    long total = 0;

    while(getline(cin, buf)) {
        vector<int> v;
        string str;
        istringstream iss(buf);
        iss >> str;
        int a;
        while(iss >> a) {
            v.push_back(a);
            if(iss.peek() == ',')
                iss.ignore();
        }

        str = unfold(str);
        vector<int> groups;
        for(int i=0; i<5; ++i) {
            groups.insert(groups.begin(), v.begin(), v.end());
        }
        auto ar = arrangements(str, groups);

        total += ar;

        for(auto e:groups) cout << e << ' ';
        cout << str << " Finished line " << ++number << " -> " << ar <<'\n';
    }

    cout << '\n' << total << '\n';

    return 0;
}