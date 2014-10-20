/*
 * Sort List
 *
 * Sort a linked list in O(n log n) time using constant space complexity.
 * reference: http://www.cnblogs.com/tenosdoit/p/3666585.html
 */
/**
 * Definition for singly-linked list.
 */
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <climits>

using namespace std;
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};

/*
 Sort List Total
 Sort a linked list in O(n log n) time using constant space complexity.
 */
class Solution {
public:

	ListNode *partition(ListNode *start, ListNode *end) {
		int key = start->val;
		ListNode *sep = start;
		for (ListNode *idx = start->next; idx != end; idx = idx->next) {
			if (idx->val <= key) {
				sep = sep->next;
				swap(idx->val, sep->val);
			}
		}
		swap(sep->val, start->val);
		return sep;
	}

	ListNode *sortList(ListNode *head, ListNode *tail) {
		if (head != tail && head->next != tail) {
			ListNode *mid = partition(head, tail);
			sortList(head, mid);
			sortList(mid->next, tail);
		}
		return head;
	}

	ListNode *_sortList(ListNode *head) {
		assert(head != NULL);
		return sortList(head, NULL);
	}
	ListNode * merge(ListNode *first, ListNode *second) {
		if (first == NULL)
			return second;
		if (second == NULL)
			return first;
		ListNode *p, *ret;
		if (first->val < second->val) {
			p = first;
			first = first->next;
		} else {
			p = second;
			second = second->next;
		}
		ret = p;
		while (first != NULL && second != NULL) {
			if (first->val < second->val) {
				p->next = first;
				first = first->next;
			} else {
				p->next = second;
				second = second->next;
			}
			p = p->next;
		}
		if (first == NULL)
			p->next = second;
		else if (second == NULL)
			p->next = first;
		return ret;
	}
	ListNode *sortList(ListNode* head) {
		if (head == NULL || head->next == NULL)
			return head;
		ListNode* slow = head, *fast = head;
		while (fast != NULL && fast->next != NULL && fast->next->next != NULL) {
			fast = fast->next->next;
			slow = slow->next;
		}
		fast = slow->next;
		slow->next = NULL;
		ListNode *first = sortList(head);
		ListNode *second = sortList(fast);
		return merge(first, second);
	}

	ListNode *insertionSortList(ListNode *head) {
		if (head == NULL || head->next == NULL)
			return head;
//		ListNode *start = head->next;
//		for(ListNode *p = head->next; p != NULL; p = p->next) {
//			ListNode *q = start;
//			while(q != p && p->val > q->val) {
//				q = q->next;
//			}
//
//		}

//
//		ListNode *insertionSortList(ListNode *head) {
//
//		        if(head == NULL || head->next == NULL)
//		            return head;

		ListNode dummy(INT_MIN);
		dummy.next = head;
		head = &dummy;

		ListNode *p = head->next;
		head->next = NULL;

		while (p) {
			ListNode *nextP = p->next;
			p->next = NULL;

			ListNode *pre = head;
			while (pre->next && pre->next->val <= p->val)
				pre = pre->next;
			//insert it
			p->next = pre->next;
			pre->next = p;

			p = nextP;
		}

		return head->next;
	}

};

int main(int argc, char **argv) {

	ListNode l1(3), l2(100), l3(1);
	l1.next = &l2;
	l2.next = &l3;
	l3.next = NULL;

	ListNode *p = Solution().sortList(&l1);

	//cout << l1.val << ' ' << l2.val << ' ' << l3.val << endl;
	while (p) {
		cout << p->val << ' ';
		p = p->next;
	}
	return 0;
}

