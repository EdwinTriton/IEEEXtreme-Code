#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include <utility>
#include <map>

using namespace std;

vector<pair<long long, pair<long long, long long>>> edges;

map<string, long long> encode;
//map<long long, string> decode;

vector<long long> parent;
vector<bool> use;

long long leader(long long a) {
    if(parent[a] == a) return a;
    return leader(parent[a]);
}

bool connected(long long a, long long b) {
    return leader(a) == leader(b);
}

int main() {
    ios_base::sync_with_stdio(false);

    unordered_set <string> gradovi;

    long long n;
    cin >> n;

    long long w, coden = 1;
    string s1, s2;
    for(long long i=0;i<n;i++) {
        cin >> s1 >> s2 >> w;
        if(encode[s1] == 0) {
            encode[s1] = coden;
//            decode[coden] = s1;
            coden++;
        }
        if(encode[s2] == 0) {
            encode[s2] = coden;
//            decode[coden] = s2;
            coden++;
        }
        edges.push_back(make_pair(w, make_pair(encode[s1], encode[s2])));
    }

    sort(edges.begin(), edges.end());

    parent.resize(coden);
    use.resize(edges.size());

    for(long long i=1;i<parent.size();i++) {
        parent[i] = i;
//        cout << parent[i] << ' ' << i << " parent i\n";
    }

//    cout << "coden " << coden << '\n';

    long long tw;
    vector <long long> toadd;

    for(long long i=0;i<edges.size();i++) {
        if(connected(edges[i].second.first, edges[i].second.second)) {
//            cout << "povezani " << edges[i].second.first << " i " << edges[i].second.second << endl;
//            cout << "parenti " << parent[edges[i].second.first] << ' ' << parent[edges[i].second.second] << '\n';
            continue;
        }

        toadd.resize(0);
        toadd.push_back(i);
//        cout << "jednom ovdje\n";
        tw = edges[i].first;

        for(i++;edges[i].first==tw && i<edges.size();i++) {
            if(!connected(edges[i].second.first, edges[i].second.second)) {
                toadd.push_back(i);
//                cout << "ovdje\n";
            }
        }
        i--;

        for(long long j=0;j<toadd.size();j++) {
//            cout << "koristi se toadd\n";
            use[toadd[j]] = true;
            long long a = edges[toadd[j]].second.first;
            long long b = edges[toadd[j]].second.second;
            if(connected(a, b)) continue;
            if(leader(a) > leader(b)) {
                swap(a, b);
            }

            parent[leader(b)] = leader(a);
//            parent[b] = leader(a);
        }
    }

    bool ok = true;
    for(long long i=1;i<coden-1;i++) {
        if(leader(i)!=leader(i+1)) ok = false;
    }
    if(!ok) {
        cout << -1;
        return 0;
    }

    long long cost = 0;

    for(long long i=0;i<edges.size();i++) {
        if(use[i]) cost += edges[i].first;
//        cout << use[i] << "  " << edges[i].first << ' ' << edges[i].second.first << ' ' << edges[i].second.second << '\n';
    }

    cout << cost;

    return 0;
}
/*

5
a b 1
b c 1
a c 1
b d 1
a d 1


*/
