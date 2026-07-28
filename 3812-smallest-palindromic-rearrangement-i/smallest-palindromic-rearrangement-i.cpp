class Solution {
public:
    string smallestPalindrome(string s) {
        vector<int> freq(26, 0);

        // Count frequency of every character
        for (char ch : s) {
            freq[ch - 'a']++;
        }

        string firstHalf = "";
        char middle = '\0';

        // Build the smallest first half
        for (int i = 0; i < 26; i++) {
            firstHalf.append(freq[i] / 2, char('a' + i));

            // Odd frequency character goes in the middle
            if (freq[i] % 2 == 1) {
                middle = char('a' + i);
            }
        }

        // Create the second half
        string secondHalf = firstHalf;
        reverse(secondHalf.begin(), secondHalf.end());

        // Final palindrome
        if (middle != '\0') {
            return firstHalf + middle + secondHalf;
        }

        return firstHalf + secondHalf;
    }
};