#include <iostream>
#include <string>
#include <vector>
#include <set>

// To finish writing words, it needs to write the "done".

using namespace std;

int main() {
    vector<set<char>>list;
    string word;
    set<char> nw;

    int mn = 2147483647;
    int ind = 0;
    int ind_cur = 0;

    while (cin >> word && word != "done") {
        nw.clear(); 
        for (char i:word){
            if ((('a' <= i) && (i <= 'z')) || (('A' <= i) && (i <= 'Z'))){
               nw.insert(i); 
            }
        }
        if (word.length() < mn) {
            mn = word.length();
            ind = ind_cur;
        }
        list.push_back(nw);
        ind_cur += 1;
    }
    int f = 1;
    
    for (set<char>::iterator i = list[ind].begin(); i != list[ind].end(); i++) {
        for (auto j : list) {
            if (j.find(*i) == j.end()) {
                f = 0;
                break;
            }
        }
        if (f == 1) {
            cout << *i;
        }
        f = 1;
    }
    cout << endl;
}
