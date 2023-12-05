#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
using namespace std;

int main() {
    int total = 0;
    string str;
    map<int,int> m;
    while(getline(cin, str)) {
        istringstream iss(str);
        string buf;
        int id;
        iss >> str >> id >> str;

        m[id]++;
        
        vector<int> win, mine;
        char c;
        iss >> c;
        while(c != '|') {
            iss.putback(c);
            int a; iss >> a;
            win.push_back(a);
            iss >> c;
        }
        int a;
        while(iss >> a) {
            mine.push_back(a);
        }

        int n = 0;
        for(auto e: win) {
            if(find(mine.begin(), mine.end(), e) != mine.end()){
                n++;
            }
        }

        for(int i=1; i<=n; ++i){
            m[id+i] += m[id];
        }
    }

    for(auto e:m) {
        total += e.second;
    }
    
    cout << total << '\n';

    return 0;
}