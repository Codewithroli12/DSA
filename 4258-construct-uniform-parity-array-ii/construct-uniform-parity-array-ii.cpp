class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int minEl = *min_element(nums1.begin(), nums1.end());

        // If minimum element is odd,
        // all even elements are greater than it,
        // so we can make all elements odd.
        if (minEl % 2 == 1) {
            return true;
        }

        // Minimum is even.
        // If any odd element exists, it is greater than
        // the minimum even element, so we cannot make
        // all elements have the same parity.
        for (int x : nums1) {
            if (x % 2 == 1) {
                return false;
            }
        }

        // All elements are even.
        return true;
    }
};