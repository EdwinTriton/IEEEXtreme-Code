#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

std::pair<int, int> findPrefixInterval(const std::vector<std::string>& sortedStrings, const std::string& prefix) {
    // Construct strings representing the range for the prefix
    std::string lowerBound = prefix;
    std::string upperBound = prefix;
    // Increment the last character of the upperBound string to cover all strings with the given prefix
    upperBound.back() += 1;

    // Find the lower and upper bounds of the prefix interval using binary search
    auto lowerIt = std::lower_bound(sortedStrings.begin(), sortedStrings.end(), lowerBound);
    auto upperIt = std::lower_bound(sortedStrings.begin(), sortedStrings.end(), upperBound);

    // Convert iterators to indices
    int lowerIndex = lowerIt - sortedStrings.begin();
    int upperIndex = upperIt - sortedStrings.begin();

    return {lowerIndex, upperIndex - 1};  // upperIndex - 1 since upperIndex is the position after the last element of the interval
}

vector<string> v;

string mojRev(string s) {
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    int n, M;
    cin >> n >> M;
    
    v.resize(n);
    
    for(int i=0;i<n;i++) {
        cin >> v[i];
        if(v[i].size()<3) {
            i--;
            v.resize(n-1);
            n--;
        }
    }
    
    sort(v.begin(), v.end());
    
    vector<string> vr(v);
    for(int i=0;i<vr.size();i++) {
        reverse(vr[i].begin(), vr[i].end());
    }
    sort(vr.begin(), vr.end());
    
    string s, prefix, suffix;
    int l, u;
    int prefpoc, prefkraj, suffpoc, suffkraj;
    bool ok;
    
    while(M--) {
        cin >> s;
        
        string sr = s;
        reverse(sr.begin(), sr.end());
        
        if(s.size()<5) {
            cout << "none\n";
            continue;
        }
        
        if(s.size()==5) {
            std::pair<int, int> interval1, interval2;
            prefix = s.substr(0, 3);
            interval1 = findPrefixInterval(v, prefix);
            suffix = sr.substr(0, 3);
            interval2 = findPrefixInterval(vr, suffix);
            
            if(interval1.first == interval1.second && interval2.first == interval2.second) {
                cout << v[interval1.first] << ' ' << mojRev(vr[interval2.first]) << '\n';
                continue;
            }
            
            if(interval1.first > interval1.second || interval2.first > interval2.second) {
                cout << "none\n";
                continue;
            }
            
            cout << "ambiguous\n";
            continue;
        }
        
        std::pair<int, int> interval;
        ok = true;
        
        int plen = 2;
        
        
        bool flag1 = 0;
        do {
            plen++;
            if(plen == s.size()-2) {
                plen--;
                flag1 = 1;
                break;
            }
            prefix = s.substr(0, plen);
            interval = findPrefixInterval(v, prefix);
        } while(interval.second-interval.first >= 0);
        
        
        if(flag1) {
            // Za suffix samo pogledati zadnja 3. Ako su oba jedinstvena ok, ako je drugi 0 onda none, inace ambiguous
            std::pair<int, int> interval2;
            suffix = sr.substr(0, 3);
            interval2 = findPrefixInterval(vr, suffix);
            
            if(interval.first==interval.second && interval2.first==interval2.second) {
                cout << v[interval.first] << ' ' << mojRev(vr[interval2.first]) << '\n';
                continue;
            }
            else if(interval2.first > interval2.second) {
                cout << "none\n";
                continue;
            }
            else {
                cout << "ambiguous\n";
                continue;
            }
        }
        
        plen--;
        prefix = s.substr(0, plen);
        interval = findPrefixInterval(v, prefix);
        prefpoc = interval.first;
        prefkraj = interval.second;
        
        if(prefkraj-prefpoc>0) {
            ok = false;
        }
        
        int slen = 2;
        bool flag2=0;
        do {
            slen++;
            if(slen == s.size()-2) {
                slen--;
                flag2 = 1;
                break;
            }
            suffix = sr.substr(0, slen);
            interval = findPrefixInterval(vr, suffix);
        } while(interval.second-interval.first >= 0);
        
        if(!flag2) {
            slen--;
            suffix = sr.substr(0, slen);
            interval = findPrefixInterval(vr, suffix);
        }
        
        suffpoc = interval.first;
        suffkraj = interval.second;
        
        if(plen+slen < s.size()) {
            cout << "none\n";
            continue;
        }
        if(!ok) {
            cout << "ambiguous\n";
            continue;
        }
        if(prefkraj-prefpoc > 0 || suffkraj-suffpoc > 0) {
            cout << "ambiguous\n";
            continue;
        }
        std::pair<int, int> interval1, interval2;
        prefix = s.substr(0, s.size()-slen+1);
        interval1 = findPrefixInterval(v, prefix);
        suffix = sr.substr(0, s.size()-plen+1);
        interval2 = findPrefixInterval(vr, suffix);
        if(interval1.second-interval1.first > 0 || interval2.second-interval2.first>0) {
            cout << "ambiguous\n";
            continue;
        }
        cout << v[prefpoc] << ' ' << mojRev(vr[suffpoc]) << '\n';
        
    }
    
    return 0;
}