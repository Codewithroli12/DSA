class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // right[i] = position in word1 where word2[i]
        // can be matched while matching word2[i...m-1]
        // as far to the right as possible.
        vector<int> right(m, -1);

        int p = n - 1;

        for (int i = m - 1; i >= 0; i--) {
            while (p >= 0 && word1[p] != word2[i]) {
                p--;
            }

            if (p < 0)
                break;

            right[i] = p;
            p--;
        }

        // If word2 cannot be matched even with one mismatch
        // this will be handled by the greedy process below.

        vector<int> ans;

        int pos = 0;
        bool usedMismatch = false;

        for (int i = 0; i < m; i++) {

            while (pos < n) {

                // Option 1: exact match
                if (word1[pos] == word2[i]) {
                    ans.push_back(pos);
                    pos++;
                    break;
                }

                // Option 2: use the one allowed mismatch
                if (!usedMismatch) {

                    bool suffixPossible = true;

                    // Remaining word2[i+1 ... m-1] must
                    // be matched exactly after pos.
                    if (i + 1 < m) {
                        if (right[i + 1] == -1 ||
                            right[i + 1] <= pos) {
                            suffixPossible = false;
                        }
                    }

                    if (suffixPossible) {
                        ans.push_back(pos);
                        pos++;
                        usedMismatch = true;
                        break;
                    }
                }

                pos++;
            }

            // Could not find a valid position
            if ((int)ans.size() != i + 1)
                return {};
        }

        return ans;
    }
};