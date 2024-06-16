#include <iostream>

using namespace std;

long long calculateV13(long long v0, long long v1, long long v12) {
    long long v13 = v12 * v0;
    if (2 * v13 > v1) {
        v13 -= v1 * ((v13 + (v1 - 1) / 2) / v1);
    }
    if (v13 <= 0) v13 = -v13;
    return v13;
}

void go(long long v0, long long v1, long long v2) {
    long long bestNumerator = 0, bestDenominator = 1;  // renamed v6 and v9 for clarity
    
    for (long long v12 = 1; v12 <= v2; ++v12) {
        long long v13 = calculateV13(v0, v1, v12);
        
        if (bestDenominator * v13 < bestNumerator * v12) {
            bestDenominator = v12;
            bestNumerator = v13;
        }
    }
    
    cout << bestDenominator << endl;
}

int main() {
    long long t, a, b, c;
    cin >> t;

    while (t--) {
        cin >> a >> b >> c;
        go(a, b, c);
    }

    return 0;
}
