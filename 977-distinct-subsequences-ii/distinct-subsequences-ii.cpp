class Solution {
public:
    int distinctSubseqII(string s) {
        const int MOD = 1e9 + 7;
        int n = s.length();

        vector<long long> dp(n + 1, 0);
        dp[0] = 1;

        // Last occurrence of each character
        vector<int> last(26, 0);

        for (int i = 1; i <= n; i++) {
            int ch = s[i - 1] - 'a';

            // Every previous subsequence can either take or skip s[i-1]
            dp[i] = (2 * dp[i - 1]) % MOD;

            // Remove duplicate subsequences
            dp[i] = (dp[i] - last[ch] + MOD) % MOD;

            // Current total becomes the last contribution
            last[ch] = dp[i - 1];
        }

        // Empty subsequence is not counted
        return (dp[n] - 1 + MOD) % MOD;
    }
};