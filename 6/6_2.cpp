#include <bits/stdc++.h>
using namespace std;

/*
    The solution is made in O(1) time because it solves an equation instead of brute forcing

    (t-j)*j > d
    (t-j)*j - d > 0
    -j^2 +tj - d > 0
    j1 = (-t + sqrt(t^2-4d)) / -2
    
    ans = t - j1*2 +1
*/

int main(int argc, char const *argv[]) {
    string str;
    
    cin >> str; 
    getline(cin, str);
    str.erase(remove_if(str.begin(), str.end(), [](char x){ return isspace(x); }), str.end());
    auto t = stol(str);

    cin >> str; 
    getline(cin, str);
    str.erase(remove_if(str.begin(), str.end(), [](char x){ return isspace(x); }), str.end());
    auto d = stol(str);
    
    int j1 = (int) ceil( (-t + sqrt(t*t - 4*d)) / -2 );

    cout << t << ' ' << d <<'\n';
    
    cout << '\n' << t-j1*2+1 << '\n';

    return 0;
}