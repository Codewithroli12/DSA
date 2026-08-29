class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();

        vector<pair<int, int>> v;

        for (int i = 0; i < n; i++) {
            v.push_back({nums[i], i});
        }

        sort(v.begin(), v.end());

        int start = 0;

        while (start < n) {
            int end = start;

            // Find all elements belonging to the same group
            while (end + 1 < n && v[end + 1].first - v[end].first <= limit) {
                end++;
            }

            // Get original indices of this group
            vector<int> indices;

            for (int i = start; i <= end; i++) {
                indices.push_back(v[i].second);
            }

            // Sort original indices
            sort(indices.begin(), indices.end());

            // Assign smallest values to smallest indices
            for (int i = 0; i < indices.size(); i++) {
                nums[indices[i]] = v[start + i].first;
            }

            start = end + 1;
        }

        return nums;
    }
};