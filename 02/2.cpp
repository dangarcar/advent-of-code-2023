#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[]){
    string str;
    int total = 0;

    while(getline(cin, str)) {
        istringstream iss(str);
        int r=0, g=0, b=0;

        string buf;
        int id;
        iss >> buf >> id;
        iss.ignore();

        while(true) {
            int a; iss >> a;
            string col; iss >> col;
            if(!iss)
                break;

            if(col.find("red") != col.npos) {
                r = max(r, a);
            } else if(col.find("blue") != col.npos) {
                b = max(b, a);
            } else if(col.find("green") != col.npos) {
                g = max(g, a);
            }
        }

        total += r*g*b;
        cout << total << '\n';
    }

    return 0;
}
