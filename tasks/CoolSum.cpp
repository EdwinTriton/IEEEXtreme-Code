#include <iostream>
#include <vector>
#include <cmath>

long long dva_na_k;
#define MOD 998244353
std::vector<int> pt;
std::vector<long long> aovi;

long long power2(int exponent) {
    return 1LL << exponent;
}

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

long long nChooseK(long long n, long long k) {
    if (k > n) return 0;
    std::vector<long long> factorial(n + 1, 1);
    for (long long i = 2; i <= n; ++i) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }
    long long result = factorial[n];
    result = (result * mod_inv(factorial[k], MOD)) % MOD;
    result = (result * mod_inv(factorial[n - k], MOD)) % MOD;
    return result;
}


long long izrSumu(long long &t, long long &n) {
    long long a_t = 0;
    for(long long i = 0; i <= n; i++) {
        if(i%dva_na_k == t) {
            if(n - i < i)
                a_t += nChooseK(n, n - i);
            else
                a_t += nChooseK(n, i);
        }
    }
    return a_t%998244353;
}

int main() {

    int k;
    long long n;
    std::cin >> k >> n;
    dva_na_k = power2(k);
    
    if(n < 10000 || true) {
        pt.resize(n + 1, 0);
        pt.at(0) = 1;
        for(long long i = 1; i <= n; i++) {
            for(long long j = i; j > 0; j--) {
                pt.at(j) += pt.at(j-1); 
            }
        }
        
        aovi.resize(dva_na_k, 0);
        for(long long i = 0; i <= n; i++) {
            aovi.at(i%dva_na_k) += pt.at(i);
            aovi.at(i%dva_na_k) %= MOD;
        }
        
        for(auto x : aovi)
            std::cout << x << " ";
    } else {

        for(long long t = 0; t < dva_na_k; t++) {
            std::cout << izrSumu(t, n) << " ";
        }
    }


    return 0;
}
