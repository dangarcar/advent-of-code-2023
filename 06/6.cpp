#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[]) {
    vector<int> times, dists;
    string str;
    cin >> str; getline(cin, str);
    istringstream iss(str);
    int a;
    while(iss >> a)
        times.push_back(a);

    cin >> str; getline(cin, str);
    iss = istringstream(str);
    while(iss >> a)
        dists.push_back(a);

    int ans = 1;
    for(int i=0; i<times.size(); ++i) {
        int wins = 0;
        int t = times[i];
        for(int j=1; j<t; ++j) {
            if(j*(t-j) > dists[i])
                wins++;
        }

        if(wins != 0)
            ans *= wins;
    }

    cout << ans << '\n';

    return 0;
}