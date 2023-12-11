#include <bits/stdc++.h>
using namespace std;

string numbers[] = {
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

int main(int argc, char const *argv[]){
    string str;
    int total = 0;
    while(getline(cin, str)) {
        int l = -1, r;
        size_t sz = str.length();

        for(int i=0; i<sz; ++i) {
            if('0' <= str[i] && str[i] <= '9') {
                if(l == -1) {
                    l = str[i] - '0';
                }
                r = str[i] - '0';
            } else {
                for(int j=0; j<9; ++j) {
                    size_t szN = numbers[j].length();
                    if(strncmp(numbers[j].c_str(), str.c_str() + i, szN) == 0) {
                        if(l == -1) {
                            l = j+1;
                        }
                        r = j+1;
                    }
                }
            }
        }

        cout << l << ' ' << r << '\n';

        total += l*10+r;
    }

    cout << total << '\n';

    return 0;
}
