class Solution {
public:
    int dp[501][501];

    int solve(vector<int>& a, vector<int>& prefix, int l, int r) {
        if (l == r)
            return 0;

        if (dp[l][r] != -1)
            return dp[l][r];

        int ans = 0;

        for (int k = l; k < r; k++) {
            int leftSum = prefix[k + 1] - prefix[l];
            int rightSum = prefix[r + 1] - prefix[k + 1];

            if (leftSum < rightSum) {
                // Right part is discarded
                ans = max(ans,
                         leftSum + solve(a, prefix, l, k));
            }
            else if (leftSum > rightSum) {
                // Left part is discarded
                ans = max(ans,
                         rightSum + solve(a, prefix, k + 1, r));
            }
            else {
                // Both are equal, Alice can choose either
                ans = max(ans,
                         max(leftSum + solve(a, prefix, l, k),
                             rightSum + solve(a, prefix, k + 1, r)));
            }
        }

        return dp[l][r] = ans;
    }

    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();

        vector<int> prefix(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + stoneValue[i];
        }

        memset(dp, -1, sizeof(dp));

        return solve(stoneValue, prefix, 0, n - 1);
    }
};