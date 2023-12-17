#include <bits/stdc++.h>
using namespace std;

long HASH(const string& s) {
    long a=0; 
    for(auto c: s) {
        a += c;
        a *= 17;
        a %= 256;
    }

    return a;
}

int main(int argc, char const *argv[]){
    string str;
    getline(cin, str);
    istringstream iss(str);

    vector<vector<pair<string,long>>> table(256);
    
    while(getline(iss, str, ',')) {
        if(str.find('=') != str.npos){
            auto s = str.substr(0, str.find('='));
            auto h = HASH(s);
            auto& v = table[h];
            auto n = stol(str.substr(str.find('=')+1));
            auto i = find_if(v.begin(), v.end(), [&s](const auto& e) { return e.first == s; });
            
            if(i != v.end())
                i->second = n;
            else
                v.push_back(make_pair(s, n));
        } else {
            auto s = string(str.begin(), str.end()-1);
            auto h = HASH(s);
            auto& v = table[h];
            v.erase(remove_if(v.begin(), v.end(), [&s](const auto& e) { return e.first == s; }), v.end());
        }
    }

    long ans = 0;
    for(int i=0; i<256; ++i) {
        auto sz = table[i].size();
        for(int j=0; j<sz; ++j) {
            auto v = (i+1) * (j+1) * table[i][j].second;
            ans += v;
        }
    }

    cout << ans << '\n';

    return 0;
}
