class Solution {
public:
    bool checkValidString(string s) {
        int low = 0, high = 0;

        for (char c : s) {
            if (c == '(') {
                low++;
                high++;
            }
            else if (c == ')') {
                low--;
                high--;
            }
            else { // '*'
                low--;
                high++;
            }

            // We cannot have negative minimum
            low = max(low, 0);

            // Even the maximum is negative => invalid
            if (high < 0)
                return false;
        }

        return low == 0;
    }
};