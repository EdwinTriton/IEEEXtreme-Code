#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <utility>

using namespace std;

const long long MOD = 1000000007;

string s;
unordered_map<long long, long long> memo;
unordered_map<long long, long long> memoc;

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

long long mod_inv(long long a, long long mod) {
    return mod_pow(a, mod - 2, mod);
}

long long nChoosek(long long n, long long k) {
    // cout << n << " choose " << k << " called\n";
    if (k > n) return 0;
    if(memoc[8000*n+k]>0) return memoc[8000*n+k];
    std::vector<long long> factorial(n + 1, 1);
    for (long long i = 2; i <= n; ++i) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }
    long long result = factorial[n];
    result = (result * mod_inv(factorial[k], MOD)) % MOD;
    result = (result * mod_inv(factorial[n - k], MOD)) % MOD;
    memoc[8000*n+k] = result;
    // cout << n << " choose " << k << " = " << result << '\n';
    return result;
}


long long perm(int start, int end) {
    long long tmp;
    // cout << "Perm called: " << start << ' ' << end << '\n';
    if(memo[8000*start+end]>0) return memo[8000*start+end];
    if(end-start<3) return 1;
    long long ret = 0;
    if(s[start]=='>') {
        ret += perm(start+1, end);
        ret %= MOD;
    }
    if(s[end-2]=='<') {
        ret += perm(start, end-1);
        ret %= MOD;
    }
    
    for(int i=start;i<end-1;i++) {
        if(s[i]=='<' && s[i+1]=='>') {
            tmp = nChoosek(end-start-1, end-i-2);
            tmp *= perm(start, i+1);
            tmp %= MOD;
            tmp *= perm(i+2, end);
            tmp %= MOD;
            // cout << "Added " << tmp << " to ret, which was " << ret << " with start-end: " << start << ' ' << end << '\n';
            ret += tmp;
            ret %= MOD;
        }
    }
    
    ret %= MOD;
    memo[8000*start+end] = ret;
    // cout << "From "  << start << ' ' << end << " returned " << ret << '\n';
    return ret;
}

int main() {
    int n;
    cin >> n;
    
    cin >> s;
    
    cout << perm(0, n);
    
    
    return 0;
}