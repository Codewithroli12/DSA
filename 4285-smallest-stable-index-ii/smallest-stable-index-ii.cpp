class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();

        // Suffix minimum
        vector<int> right(n);

        right[n - 1] = nums[n - 1];

        for (int i = n - 2; i >= 0; i--) {
            right[i] = min(right[i + 1], nums[i]);
        }

        // Prefix maximum
        int left = nums[0];

        for (int i = 0; i < n; i++) {
            left = max(left, nums[i]);

            // Instability = max(nums[0...i]) - min(nums[i...n-1])
            if (left - right[i] <= k) {
                return i;
            }
        }

        return -1;
    }
};