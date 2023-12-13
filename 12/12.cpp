#include <bits/stdc++.h>
using namespace std;

vector<int> groups;

long arrangements(const string str, string curr) {
    long ans = 0;

    for(int i=curr.size(); i<str.size(); ++i) {
        if(str[i] == '?') {
            ans += arrangements(str, curr+'#');
            ans += arrangements(str, curr+'.');
            break;
        }
        curr += str[i];
    }

    if(curr.size() == str.size()) {
        int n=0, currIdx=0;
        for(int i=0; i<curr.size(); ++i) {
            if(curr[i] == '#') {
                n++;
            } else if(n != 0) {
                if(n != groups[currIdx])
                    return ans;
                
                currIdx++;
                n = 0;
            }
        }

        if(n != 0) {
            if(n != groups[currIdx])
                return ans;
            ++currIdx;
        }

        if(currIdx != groups.size())
            return ans;

        //cout << curr << '\n';
        ++ans;
    }

    return ans;
}

int main(int argc, char const *argv[]) {
    string buf;
    int number=0;

    long total = 0;

    while(getline(cin, buf)) {
        groups.clear();
        vector<int> v;
        string str;
        istringstream iss(buf);
        iss >> str;
        int a;
        while(iss >> a) {
            groups.push_back(a);
            if(iss.peek() == ',')
                iss.ignore();
        }

        auto ar = arrangements(str, "");
        total += ar;

        for(auto e:groups) cout << e << ' ';
        cout << str << " Finished line " << ++number << " -> " << ar <<'\n';
    }

    cout << '\n' << total << '\n';

    return 0;
}