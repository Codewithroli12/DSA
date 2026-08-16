class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        vector<int> cnt(3, 0);

        // Count numbers according to remainder when divided by 3
        for (int x : stones) {
            cnt[x % 3]++;
        }

        // Alice chooses remainder 1 first
        vector<int> c1 = cnt;

        // Alice chooses remainder 2 first
        vector<int> c2 = {cnt[0], cnt[2], cnt[1]};

        return check(c1) || check(c2);
    }

private:
    bool check(vector<int>& cnt) {
        // Alice must pick a stone with remainder 1
        if (--cnt[1] < 0)
            return false;

        int turns = 1 + min(cnt[1], cnt[2]) * 2 + cnt[0];

        if (cnt[1] > cnt[2]) {
            cnt[1]--;
            turns++;
        }

        return turns % 2 == 1 && cnt[1] != cnt[2];
    }
};