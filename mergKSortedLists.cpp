/*
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// k lists, each size n, T(k) = 2 T(k/2) + O(nk) , O(nklogk)
// k lists, overall length n, T(k) = 2 T(k/2) + O(n), O(nlogk)
// space O(logk) if balanced
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
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        return merge(lists, 0, lists.size() - 1);
    }
    
    ListNode* merge(vector<ListNode *> &lists, int s, int e) {
        if (s > e) return NULL;
        if (s == e) return lists[s];
        int m = s + (e - s)/2;
        auto l1 = merge(lists, s, m);
        auto l2 = merge(lists, m + 1, e);
        return merge(l1, l2);
    }
    
    ListNode* merge(ListNode* l1, ListNode* l2) {
        if (l1 == NULL) return l2;
        if (l2 == NULL) return l1;
        ListNode* head = NULL;
        if (l1->val < l2->val) {
            head = l1; head->next = merge(l1->next, l2);
        } else {
            head = l2; head->next = merge(l1, l2->next);
        }
        return head;
    }
    
};


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
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return mergeLists(lists, 0, lists.size() - 1);
    }
    
    ListNode *mergeLists(vector<ListNode *> &lists, int s, int e) {
        if (s > e) return NULL;
        if (s == e) return lists[s];
        int mid = s + (e -s)/2;
        ListNode *left = mergeLists(lists, s, mid);
        ListNode *right = mergeLists(lists, mid + 1, e);
        return merge(left, right);        
    }
    // merge two sorted lists
    ListNode *merge(ListNode *l1, ListNode *l2) {
        if (l1 == NULL) return l2;
        if (l2 == NULL) return l1;
        ListNode *head = NULL;
        ListNode *tail = NULL;
        while(l1 && l2) {
            if (l1->val < l2->val) {
                if (tail == NULL) { // first elem
                    head = l1; tail = l1;
                } else {
                    tail->next = l1; tail = l1;
                }
                l1 = l1->next;
            } else {
                if (tail == NULL) {
                    head = l2; tail = l2;
                } else {
                    tail->next = l2; tail = l2;
                }
                l2 = l2->next;
            }
        }
        tail->next = NULL;
        if (l1) tail->next = l1;
        if (l2) tail->next = l2;
        
        return head;
    }
    
};



//algorithm 2, O(nlogk)
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#include<priority_queue>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 
class comp{
    public :
        bool operator () (ListNode *a, ListNode *b) {
            assert(a && b);
            return (a->val > b->val);
        }
};
 
class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        priority_queue<ListNode*, vector<ListNode* >, comp> mheap;
        // KlogK
        for (int i = 0; i < lists.size(); ++i) {
           if (lists[i]) mheap.push(lists[i]);
        }
        ListNode *head = NULL;
        ListNode *tail = NULL;
        // (N-K)logK
        while(!mheap.empty()) {
            ListNode *cur = mheap.top();
            mheap.pop();
       //     if (cur == NULL) continue; // skip
            // add cur node
            if (head == NULL) {
                head = cur; tail = cur;
            } else {
                tail->next = cur; tail = cur;
            }
            if (cur->next) {
                mheap.push(cur->next);
            }
        }
        
        return head;
    }
};
