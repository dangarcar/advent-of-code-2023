#include <bits/stdc++.h>
using namespace std;

/*

A very bad implementation of Karger's algorithm I came up by myself,
I don't figure out how I make it work yet
29th December 2023

*/

map<string, vector<string>> m;
vector<string> nodes;
vector<multiset<int>> adj; // The first use case for multisets I've encountered

template <typename I> //If std do this, why not do it myself?
int getRandomElementFromSet(const I& b, const I& e) {
    auto n = rand()%distance(b, e);
    auto it = b;
    for(int i=0; i<n; ++i) {
        ++it;
    }
    return *it;
}

int main(int argc, char const *argv[]) {
    string str;
    while(getline(cin, str)) {
        if(str.empty()) continue;
        istringstream iss(str);

        string name, conn; 
        iss >> name;
        name = name.substr(0, 3);
        while(iss >> conn) {
            m[name].push_back(conn);
            m[conn].push_back(name);
        }
    }

    transform(m.begin(), m.end(), back_inserter(nodes), [](const auto& p){ return p.first; }); //I prefer ints over strings

    auto sz = nodes.size();
    long ans;

    while(true) {
        map<int, set<int>> sets;
        set<int> nodesAvailable; // Redundant data
        for(int i=0; i<sz; ++i)  {
            nodesAvailable.insert(i);
            sets[i].insert({i});
        }

        adj.assign(nodes.size(), {});
        for(const auto& [k, v]: m) {
            auto u = find(nodes.begin(), nodes.end(), k) - nodes.begin();
            for(auto s: v) {
                auto v = find(nodes.begin(), nodes.end(), s) - nodes.begin();
                adj[u].insert(v);
                adj[v].insert(u);
            }
        }

        while(nodesAvailable.size() > 2) {
            auto a = getRandomElementFromSet(nodesAvailable.begin(), nodesAvailable.end());
            auto b = getRandomElementFromSet(adj[a].begin(), adj[a].end());

            for(auto e: adj[b]) { // Change b from its neighbours
                adj[e].erase(b);
                adj[e].insert(a);
            }

            adj[a].insert(adj[b].begin(), adj[b].end()); //Add all of its neighbours
            adj[a].erase(a); // remove duplicates
            
            adj[b].clear(); // remove b from existence
            nodesAvailable.erase(b);
            sets[a].insert(sets[b].begin(), sets[b].end());
            sets.erase(b);
        }

        auto first = *nodesAvailable.begin();
        auto second = *(++nodesAvailable.begin());

        if(adj[first].size() == 6 && adj[second].size() == 6) { // The edges are duplicated and I really don't know why
            auto s1 = sets[first].size();
            auto s2 = sets[second].size();
            cout << s1 << ' ' << s2 << '\n';
            ans = s1*s2;
            break;
        }
    }

    cout << ans << '\n';

    return 0;
}