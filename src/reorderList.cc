/*

 */

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) :
            val(x), next(NULL) {
    }
};

class Solution {
public:
    ListNode *reverseList(ListNode *head) {
        ListNode *p = head;
        ListNode *prev = NULL, *tmp;
        while (p) {
            tmp = p->next;
            p->next = prev;
            prev = p;
            p = tmp;
        }
        return prev;
    }

    ListNode *merge(ListNode *first, ListNode *second) {
        if (!first || !second) return first ? first : second;
        ListNode dummy(0);
        ListNode *node = &dummy;
        while (second) {
            node->next = first;
            first = first->next;
            node = node->next;
            node->next = second;
            second = second->next;
            node = node->next;
        }
        //note: second finish firstly
        node->next = first;
        return node->next;
    }

    ListNode *reorderList(ListNode *head) {
        if (!head || !head->next) return head;
        ListNode *slow = head, *fast = head;
        while (fast != NULL && fast->next != NULL && fast->next->next != NULL) {
            fast = fast->next->next;
            slow = slow->next;
        }
        ListNode *first = head;
        ListNode *second = reverseList(slow->next);
        slow->next = NULL;
        merge(first, second);
        return head;
    }


};

int main() {

    ListNode n1(1), n2(2), n3(3);//, n4(4);
    n1.next = &n2;
    n2.next = &n3;
    n3.next = NULL;
    //n4.next = NULL;
    Solution solution;
    solution.reorderList(&n1);
    ListNode *p = &n1;
    while (p) {
        cout << p->val << ' ';
        p = p->next;

    }
    return 0;
}