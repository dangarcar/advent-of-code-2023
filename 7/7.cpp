#include <bits/stdc++.h>
using namespace std;

char cards[] {
    'J','2','3','4','5','6','7','8','9','T','Q','K','A'
};

struct Hand {
    string hand;
};

enum class Rank {
    HighCard, OnePair, TwoPair, ThreeOfAKind, FullHouse, FourOfAKind, FiveOfAKind
};

pair<Rank,int> getRankWithout(string h) {
    map<char,int> c;
    for(auto e: cards) {
        int cnt = count(h.begin(), h.end(), e);
        if(cnt != 0)
            c[e] = cnt;
    }

    bool pair=false, three=false;

    for(auto [e, n]: c) {
        if(e == 'J')
            continue;

        if(n == 5) {
            return make_pair(Rank::FiveOfAKind, c['J']);
        } else if(n == 4) {
            return make_pair(Rank::FourOfAKind, c['J']);
        } else if(n == 3) {
            if(pair)
                return make_pair(Rank::FullHouse, c['J']);
            else 
                three = true;
        } else if(n == 2) {
            if(three)
                return make_pair(Rank::FullHouse, c['J']);
            else if(pair)
                return make_pair(Rank::TwoPair, c['J']);
            else 
                pair = true;
        }
    }

    if(pair)
        return make_pair(Rank::OnePair, c['J']);
    if(three)
        return make_pair(Rank::ThreeOfAKind, c['J']);

    return make_pair(Rank::HighCard, c['J']);
}

Rank getRank(string h) {
    auto [r,c] = getRankWithout(h);

    if(c == 5 || c == 4) {
        return Rank::FiveOfAKind;
    } else if(c == 3) {
        if(r == Rank::HighCard)
            return Rank::FourOfAKind;
        else
            return Rank::FiveOfAKind;
    } else if(c == 2) {
        if(r == Rank::ThreeOfAKind)
            return Rank::FiveOfAKind;
        else if(r == Rank::OnePair)
            return Rank::FourOfAKind;
        else
            return Rank::ThreeOfAKind;
    } else if(c == 1) {
        if(r == Rank::FourOfAKind)
            return Rank::FiveOfAKind;
        else if(r == Rank::ThreeOfAKind)
            return Rank::FourOfAKind;
        else if(r == Rank::TwoPair) 
            return Rank::FullHouse;
        else if(r == Rank::OnePair)
            return Rank::ThreeOfAKind;
        else 
            return Rank::OnePair;
    } else {
        return r;
    }
}

bool operator<(const Hand& a, const Hand& b) {
    auto ra = getRank(a.hand);
    auto rb = getRank(b.hand);

    if(ra != rb) {
        return ra < rb;
    } else {
        for(int i=0; i<5; ++i) {
            if(a.hand[i] != b.hand[i]){
                auto da = distance(cards, find(cards, cards+13, a.hand[i]));
                auto db = distance(cards, find(cards, cards+13, b.hand[i]));

                return da < db;
            }
        }
    }

    return true;
}

int main(int argc, char const *argv[]) {
    string hand; 
    int bid;

    map<Hand, int> map;
    while(cin >> hand >> bid){
        map.insert(make_pair(Hand{hand}, bid));   
    }

    cout << '\n';

    long total=0;
    long i=1;
    for(auto [h, b]: map) {
        //cout << h.hand << ' ' << b << '\n';
        total += b*i;
        
        ++i;
    }

    cout << total << '\n';

    return 0;
}
