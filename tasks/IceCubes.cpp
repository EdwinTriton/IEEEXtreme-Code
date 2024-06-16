#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

int main() {
    int T;
    cin >> T;
    
    for(int CASE = 1; CASE <= T; CASE++) {
        
        int n, m, k, b;
        cin >> n >> m >> k >> b;
        
        vector<vector<int>> mat(n, vector<int>(m));
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(k+1, -1)));
        
        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                cin >> mat[i][j];
            }
        }
        
        if(mat[0][0] >= b) {
            dp[0][0][0] = mat[0][0];
        }
        else {
            dp[0][0][1] = mat[0][0];
        }
        
        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                for(int l=0;l<k;l++) {
                    if(j>0 && dp[i][j-1][l] != -1) {
                        if(mat[i][j]>=b) {
                            dp[i][j][0] = max(dp[i][j][0], dp[i][j-1][l]+mat[i][j]);
                        }
                        else {
                            dp[i][j][l+1] = max(dp[i][j][l+1], dp[i][j-1][l]+mat[i][j]);
                        }
                    }
                    if(i>0 && dp[i-1][j][l] != -1) {
                        if(mat[i][j] >= b) {
                            dp[i][j][0] = max(dp[i][j][0], dp[i-1][j][l]+mat[i][j]);
                        }
                        else {
                            dp[i][j][l+1] = max(dp[i][j][l+1], dp[i-1][j][l]+mat[i][j]);
                        }
                    }
                }
            }
        }
        
        int ans = -1;
        for(int i=0;i<k;i++) {
            ans = max(ans, dp[n-1][m-1][i]);
        }
        
        // for(int i=0;i<n;i++) {
        //     for(int j=0;j<m;j++) {
        //         cout << dp[i][j][0] << ' ';
        //     }
        //     cout << '\n';
        // }
        // cout << '\n';
        // for(int i=0;i<n;i++) {
        //     for(int j=0;j<m;j++) {
        //         cout << dp[i][j][1] << ' ';
        //     }
        //     cout << '\n';
        // }
        // cout << '\n';
        // for(int i=0;i<n;i++) {
        //     for(int j=0;j<m;j++) {
        //         cout << dp[i][j][2] << ' ';
        //     }
        //     cout << '\n';
        // }
        
        
        cout << "Case " << CASE << ": ";
        if(ans == -1) {
            cout << "IMPOSSIBLE\n";
        }
        else {
            cout << ans << '\n';
        }
    }
}