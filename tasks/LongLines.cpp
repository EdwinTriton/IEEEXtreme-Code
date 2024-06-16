#include <iostream>
#include <vector>

using namespace std;

int main() {
    long long n, h0, a, c, q;
    
    cin >> n >> h0 >> a >> c >> q;
    
    vector <int> v;
    v.push_back(h0);
    
    long long h, ans = 0, left, right, result;
    
    while(--n) {
        ans += v.size();
        // for(auto x : v) {
        //     cout << x << ' ';
        // }
        // cout << '\n';
        if(n == 0) break;
        
        h = (a*v[v.size()-1]+c)%q;
        if(h < v[v.size()-1]) {
            v.push_back(h);
            continue;
        }
        if(h >= v[0]) {
            v[0] = h;
            v.resize(1);
            continue;
        }
        
        // Binary search
        left = 0;
        right = v.size() - 1;
        result = -1;  // If there's no such element, -1 will be the result
    
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (v[mid] > h) {
                // If the mid element is greater than h,
                // then continue searching to the right
                left = mid + 1;
            } else {
                // If the mid element is not larger than h,
                // update the result and continue searching to the left
                result = mid;
                right = mid - 1;
            }
        }
        
        v[result] = h;
        v.resize(result+1);
    }
    
    cout << ans;
    return 0;
}