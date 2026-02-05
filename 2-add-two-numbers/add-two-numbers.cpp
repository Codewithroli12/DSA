/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0);
        ListNode* temp = dummy;

        int carry = 0;

        while (l1 != NULL || l2 != NULL || carry != 0) {
            int v1 = (l1 != NULL) ? l1->val : 0;
            int v2 = (l2 != NULL) ? l2->val : 0;

            int sum = v1 + v2 + carry;
            carry = sum / 10;

            temp->next = new ListNode(sum % 10);
            temp = temp->next;

            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
        }

        return dummy->next;
    }
};
