#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    int n, m, p;
    
    cin >> n;
    vector<vector<string>> iter(n);
    
    string st;
    for(int i=0;i<n;i++) {
        cin >> m;
        while(m--) {
            cin >> st;
            iter[i].push_back(st);
        }
    }
    
    
    cin >> p;
    string s1, s2;
    while(p--) {
        cin >> s1 >> s2;
        
        if(s2.size() < s1.size()) swap(s1, s2);
        
        // s1 ce biti manji-jednak po velicini
        
        bool ok = true;
        
        int ind = 0;
        for(ind = 0;ind<s1.size();ind++) {
            if(s1[ind] != s2[ind]) break;
        }
        
        // Provejriti ako s1 je prefiks of s2
        
        vector<string> pot1, pot2;
        
        for(int I=0;I<n;I++) {
            for(int i=0;i<iter[I].size();i++) {
                bool isti = false;
                for(int j=0;j<iter[I].size();j++) {
                    if(i==j) continue;
                    if(iter[I][i].size() > iter[I][j].size()) continue;
                    int ind2;
                    for(ind2 = 0;ind2<iter[I][i].size();ind2++) {
                        if(iter[I][i][ind2] != iter[I][j][ind2]) break;
                    }
                    
                    //Provjeriti ako je jedan prefiks drugog
                    
                    if(ind2 > ind) continue;
                    
                    //Provjeriti da li su tu
                    if(s1.substr(ind-ind2, iter[I][i].size()) != iter[I][i]) continue;
                    if(s2.substr(ind-ind2, iter[I][j].size()) != iter[I][j]) continue;
                    
                    
                    // Da li s1[0:ind-ind2]+iter[I][i]+s1[ind-ind2+iter[I][i].size():end] == drugom
                        // cout << s1.substr(0, ind-ind2)+iter[I][j]+s1.substr(ind-ind2+iter[I][i].size()) << '\n';
                        // cout << s2 << '\n';
                    
                    if(s1.substr(0, ind-ind2)+iter[I][j]+s1.substr(ind-ind2+iter[I][i].size()) == s2) {
                        isti = true;
                        break;
                    }
                }
                if(isti) ok = false;
                if(!ok) break;
            }
            if(!ok) break;
        }
        
        if(ok) {
            cout << "OK\n";
        }
        else {
            cout << "REJECT\n";
        }
    }
    
    
    return 0;
}