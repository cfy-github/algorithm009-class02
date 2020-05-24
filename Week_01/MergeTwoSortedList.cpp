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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(-1);
        ListNode* cur = &dummy;
        ListNode* c1 = l1, * c2 = l2;
        while (c1 && c2) {
            ListNode*& c = c1->val <= c2->val ? c1 : c2;
            cur->next = c;
            c = c->next;
            cur = cur->next;
        }
        cur->next = c1 ? c1 : c2;
        return dummy.next;
    }
};
