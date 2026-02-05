class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> last(256, -1);  // last seen index
        int left = 0, ans = 0;

        for (int right = 0; right < s.size(); right++) {
            char c = s[right];

            // If character seen in current window, move left
            if (last[c] >= left) {
                left = last[c] + 1;
            }

            last[c] = right;
            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};
