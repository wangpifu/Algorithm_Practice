    bool hasCycle(ListNode *head) {
        auto* slow = head;
        auto* fast = head;
        while(fast != nullptr && fast->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
            if(fast == slow) return true;
        }
        return false;
    }
//================================================================
    ListNode *detectCycle(ListNode *head) {
        auto* slow = head;
        auto* fast = head;
        while(fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
            // there is a cycle, we put res pointer walk from head, 
            // and when it meets slow pointer, it's cycle start point
            if(slow == fast)
            {
                auto* res = head;
                while (res != slow)
                {
                    res = res->next;
                    slow = slow->next;
                }
                return res;
            }
        }
        return nullptr;
    }
//=======================================================================
//Given a linked list, rotate the list to the right by k places, where k is non-negative.
//Input: 1->2->3->4->5->NULL, k = 2 Output: 4->5->1->2->3->NULL
    ListNode* rotateRight(ListNode* head, int k) {
        if(head == nullptr) return nullptr;
        if(head->next == nullptr) return head;
        // we first traverse the whole linked list to get length
        auto* tail = head;
        int len = 1;
        while(tail->next != nullptr)
        {
            tail = tail->next;
            ++len;
        }
        if(len == k) return head;
        k = k % len;
        // find the len - k node, it will be the new tail
        auto* new_tail = head;
        tail->next = head;
        while(len - k - 1 > 0) 
        {
            new_tail = new_tail->next;
            --len;
        }
        auto* ret = new_tail->next;
        new_tail->next = nullptr;
        return ret;
    }
//====================================================================================
//deep copy list with random pointer
    Node* copyRandomList(Node* head) {
        if(!head) return head;
        // first construct a new node after every orig node
        auto* curt = head;
        while(curt != nullptr)
        {
            auto* temp = curt->next;
            curt->next = new Node(curt->val);
            curt->next->next = temp;
            curt = temp;
        }
        // copy the random pointer relation
        curt = head;
        while(curt != nullptr)
        {
            auto* copy = curt->next;
            if(curt->random != nullptr)
            {
                copy->random = curt->random->next;
            }
            curt = curt->next->next;
        }
        // seperate them into two linked list
        curt = head;
        auto* res = head->next;
        auto* copy_curt = res;
        while(curt != nullptr)
        {
            curt->next = curt->next->next;
            copy_curt->next = copy_curt->next == nullptr ? nullptr : copy_curt->next->next;
            curt = curt->next;
            copy_curt=copy_curt->next;
        }
        return res;
    }
//========================================================================================
// reverse linked list
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        while(head)
        {
            auto* temp = head->next;
            head->next = prev;
            prev = head;
            head = temp;
        }
        return prev;
    }
//Input: 1->2->3->4->5->NULL, m = 2, n = 4 Output: 1->4->3->2->5->NULL
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        auto* dummy = new ListNode(-1);  // m might be 1 so we need a dummy to indicate prev
        dummy->next = head;
        auto* curt = dummy;
        // find the last element before m, record it and also node m
        for(int i = 1; i < m; ++i)
        {
            curt = curt->next;
        }
        auto* before_broken = curt;
        auto* broken = curt->next;
        // then reverse the list from m to n
        curt = curt->next;
        ListNode* prev = nullptr;
        for(int i = m; i <= n; ++i)
        {
            auto* temp = curt->next;
            curt->next = prev;
            prev = curt;
            curt = temp;
        }
        // link before_broken to n, link m to curt(which is node after n)
        before_broken->next = prev;
        broken->next = curt;
        return dummy->next;
    }
//======================================================================================
//Given a singly linked list L: L0→L1→…→Ln-1→Ln, reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
    void reorderList(ListNode* head) {
        if(!head || !head->next) return;
        // find the medium node, seperate left and right side
        auto* fast = head;
        auto* slow = head;
        while(fast->next != nullptr && fast->next->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        auto* right = slow->next;
        slow->next = nullptr;
        // reverse right part
        ListNode* prev = nullptr;
        while(right)
        {
            auto* temp = right->next;
            right->next = prev;
            prev = right;
            right = temp;
        }
        right = prev; // now prev is the right part head, reuse right pointer
        // put left and right together
        auto* left = head;
        while(left && right)
        {
            auto* templ = left->next;
            auto* tempr = right->next;
            right->next = left->next;
            left->next = right;
            left = templ;
            right = tempr;
        }
    }
//=========================================================================================
//Add two numbers Input: (2 -> 4 -> 3) + (5 -> 6 -> 4) Output: 7 -> 0 -> 8
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        auto* head = new ListNode{-1};
        auto* iter = head;
        int extra = 0;
        while(l1 || l2 || extra)
        {
            int sum = (l1? l1->val : 0) + (l2? l2->val : 0) + extra;
            extra = sum / 10;
            iter->next = new ListNode{sum%10};
            iter = iter->next;
            l1 = l1? l1->next : l1;
            l2 = l2? l2->next : l2;
        }
        return head->next;
    }
//  significat digit comes first Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4) Output: 7 -> 8 -> 0 -> 7
    ListNode* addTwoNumbers2(ListNode* l1, ListNode* l2) {
        stack<ListNode*> stack1, stack2;
        while(l1 != nullptr)
        {
            stack1.push(l1);
            l1 = l1->next;
        }
        while(l2!=nullptr)
        {
            stack2.push(l2);
            l2 = l2->next;
        }
        int sum = 0;
        ListNode* tail = nullptr;
        while(!stack1.empty() || !stack2.empty())
        {
            if(!stack1.empty()) 
            {
                sum += stack1.top()->val;
                stack1.pop();
            }
            if(!stack2.empty())
            {
                sum += stack2.top()->val;
                stack2.pop();
            }
            auto* curt = new ListNode(sum%10);
            curt->next = tail;
            tail = curt;
            sum /= 10;
        }
        if(sum != 0)
        {
            auto* curt = new ListNode(sum);
            curt->next = tail;
            return curt;
        }
        return tail;
    }
//Another solvution is O(1) space, calculate each length first, make l1 the longer one, new another list,
// while(diff) and assign value from l1 to res list. Has a pointer right points to position val= 9
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int n1 = getLength(l1), n2 = getLength(l2), diff = abs(n1 - n2);
        if (n1 < n2) swap(l1, l2);
        ListNode *dummy = new ListNode(0), *cur = dummy, *right = cur;
        while (diff > 0) {
            cur->next = new ListNode(l1->val);
            if (l1->val != 9) right = cur->next;
            cur = cur->next;
            l1 = l1->next;
            --diff;
        }
        while (l1) {
            int val = l1->val + l2->val;
            if (val > 9) {
                val %= 10;
                ++right->val;
                while (right->next) {
                    right->next->val = 0;
                    right = right->next;
                }
                right = cur;
            }
            cur->next = new ListNode(val);
            if (val != 9) right = cur->next;
            cur = cur->next;
            l1 = l1->next;
            l2 = l2->next;
        }
        return (dummy->val == 1) ? dummy : dummy->next;
    }
    int getLength(ListNode* head) {
        int cnt = 0;
        while (head) {
            ++cnt;
            head = head->next;
        }
        return cnt;
    }
//=========================================================================================
//Input: 1->1->2->3->3 Output: 1->2->3
    ListNode* deleteDuplicates(ListNode* head) {
        auto* res = head;
        while(head && head->next)
        {
            if(head->val == head->next->val)
            {
                head->next = head->next->next;
            }
            else
            {
                head = head->next;
            }
        }
        return res;
    }
//Input: 1->1->1->2->3 Output: 2->3 ; Input: 1->2->3->3->4->4->5 Output: 1->2->5
    ListNode* deleteDuplicates(ListNode* head) {
        auto* dummy = new ListNode(-1);
        auto* prev = dummy;
        prev->next = head;
        auto* curt = head;
        auto* tail = head;
        while(tail)
        {
            bool hasDuplicate = false;
            while(tail->next && (tail->next->val == curt->val))
            {
                tail = tail->next;
                hasDuplicate = true;
            }
            if(hasDuplicate)
            {
                prev->next = tail->next;
            }
            else
            {
                prev = tail;
            }
            tail = tail->next;
            curt = tail;
        }
        return dummy->next;
    }
//=========================================================================================
// reverse nodes in k group
// 1->2->3->4->5  k = 2 => 2->1->4->3->5
// 1. set a dummyhead which next points to head
// 2  use "head" as the node before group, "end" as the one after group
// 3.1  if enough elements in group, reverse them inside group
// 3.2  link head to group_end and link group_begin to end
// 4  if no enough elements in group, break
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        std::unique_ptr<ListNode> dummyhead(new ListNode(-1));
        dummyhead->next = head;
        // head will be used as the element before the first element in group
        head = dummyhead.get();
        ListNode* end = nullptr;
        while(head->next)
        {
            auto* group_begin = head->next;
            auto* group_end = getNextKth(head, k);
            // if no enough k elements in group, break
            if(!group_end)
            {
                break;
            }
            // end will be used as the element after the last element in group
            end = group_end->next;
            // if there is enough elements, iterate them and reverse them
            auto* curt = group_begin;
            auto* prev = head;
            while (prev != group_end)
            {
                auto* tmp = curt->next;
                curt->next = prev;
                prev = curt;
                curt = tmp;
            }
            // link this group to outer linked list
            head->next = group_end;
            group_begin->next = end;
            // update head
            head = group_begin;

        }
        return dummyhead->next;
    }
    
    // function used to get the last node in the k group
    ListNode* getNextKth(ListNode* prev, int k)
    {
        int i = 0;
        while (prev->next && i < k)
        {
            ++i;
            prev = prev->next;
        }
        if (i == k)
        {
            return prev;
        }
        return nullptr;
    }
};
//==============================================
// merge k sorted list
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto comp = [](ListNode* a, ListNode* b){return a->val > b->val;};
        std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(comp)> q(comp);
        // put all head into queue
        for (auto* head : lists)
        {
            // to detect nullptr head
            if(head)
            {
                q.push(head);
            }
        }
        ListNode dummy(-1);
        ListNode* head = &dummy;
        while (!q.empty())
        {
            ListNode* curt_min = q.top();
            q.pop();
            head->next = curt_min;
            head = head->next;
            if (curt_min->next)
            {
                q.push(curt_min->next);
            }
        }
        return dummy.next;
    }
};
//=======================================================================
// Input: 1->2->2->1 Output: true
    bool isPalindrome(ListNode* head) {
        if(!head) return true;
        // find median point, reverse right half part and compare
        // if modify is not allowed, we ned to use stack to push first half nodes
        auto* fast = head;
        auto* slow = head;
        while(fast->next && fast->next->next)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        auto* right = slow->next;
        ListNode* prev = nullptr;
        while(right)
        {
            auto* temp = right->next;
            right->next = prev;
            prev = right;
            right = temp;
        }
        right = prev;
        while(right)
        {
            if(right->val != head->val) return false;
            right = right->next;
            head = head->next;
        }
        return true;
    }
//=================================================================================
//Sort a linked list in O(n log n) time using constant space complexity.
//Input: -1->5->3->4->0 Output: -1->0->3->4->5
    //we use merge sort, divide list to two parts and merge
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next) return head;
        auto* fast = head;
        auto* slow = head;
        while(fast->next && fast->next->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        auto* right = slow->next;
        slow->next = nullptr;
        return merge(sortList(head), sortList(right));
    }
    // merge two sorted list
    ListNode* merge(ListNode* l, ListNode* r)
    {
        auto* dummy = new ListNode(-1);
        auto* curt = dummy;
        while(l && r)
        {
            if(l->val > r->val)
            {
                curt->next = r;
                r = r->next;
            }
            else
            {
                curt->next = l;
                l = l->next;
            }
            curt = curt->next;
        }
        if(l) curt->next = l;
        if(r) curt->next = r;
        return dummy->next;
    }
//==========================================================================================
    void deleteNode(ListNode* node) {
        auto* temp = node->next;
        swap(node->val, temp->val);
        node->next = temp->next;
        delete temp;
    }
//===========================================================================================
//root = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], k = 3 Output: [[1, 2, 3, 4], [5, 6, 7], [8, 9, 10]]
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        vector<ListNode*> res(k);
        int len = 0;
        for(auto* node = root; node != nullptr; node = node->next) ++len;
        int avg = len / k;
        int extra = len % k;
        for(int i = 0; i < k && root!= nullptr; ++i)
        {
            res[i] = root;
            int group_size = avg;
            if(i< extra) group_size += 1;
            for(int j = 1; j < group_size; ++j)
            {
                root = root->next;
            }
            auto* temp = root->next;
            root->next = nullptr;
            root = temp;
        }
        return res;
    }