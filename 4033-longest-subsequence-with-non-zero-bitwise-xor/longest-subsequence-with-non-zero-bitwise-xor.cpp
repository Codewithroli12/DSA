
class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int n = nums.size();
        int xr = 0;
        bool nonZero = false;

        for (int x : nums) {
            xr ^= x;

            if (x != 0)
                nonZero = true;
        }

        // Case 1: Whole array has non-zero XOR
        if (xr != 0)
            return n;

        // Case 2: XOR is zero, but a non-zero element exists
        if (nonZero)
            return n - 1;

        // Case 3: All elements are zero
        return 0;
    }
};