class Solution {
public:
    vector<int> constructTransformedArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);

        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                result[i] = nums[i];
                continue;
            }

            int new_index = (i + nums[i]) % n;

            // Fix negative modulo
            if (new_index < 0) {
                new_index += n;
            }

            result[i] = nums[new_index];
        }

        return result;
    }
};
