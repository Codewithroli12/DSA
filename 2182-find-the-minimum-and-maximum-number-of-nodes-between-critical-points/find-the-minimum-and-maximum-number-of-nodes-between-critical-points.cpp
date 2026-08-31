class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int> ans = {-1, -1};

        if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
            return ans;

        ListNode* prev = head;
        ListNode* curr = head->next;

        int index = 1;
        int first = -1;
        int last = -1;

        int minDist = INT_MAX;

        while (curr->next != nullptr) {
            ListNode* next = curr->next;

            // Critical point
            if ((curr->val > prev->val && curr->val > next->val) ||
                (curr->val < prev->val && curr->val < next->val)) {

                if (first == -1) {
                    first = index;
                } else {
                    minDist = min(minDist, index - last);
                }

                last = index;
            }

            prev = curr;
            curr = next;
            index++;
        }

        if (first == -1 || first == last)
            return ans;

        int maxDist = last - first;

        ans[0] = minDist;
        ans[1] = maxDist;

        return ans;
    }
};