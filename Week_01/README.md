# Note @Week01

第一周学习笔记


# 作业题目

2020.05.18 ~ 2020.05.24

## 26. Remove Duplicates from Sorted Array

自己的初版：

    int removeDuplicates(vector<int>& nums) {
	    if (nums.empty()) return 0;
	    int preVal = nums[0];
	    int curIdx = 1;
	    int dupCnt = 0;
	    for (int i = 1; i < nums.size(); ++i) {
		    if (nums[i] == preVal) {
			    dupCnt++;
			    continue;
			}
			nums[curIdx++] = nums[i];
			preVal = nums[i];
		}
		nums.resize(nums.size() - dupCnt);
		return nums.size();
	}
存在的问题：

 1. 题目没要求实际删掉冗余的元素，所以丢到后面就可以了，resize是没必要的
 2. dupCnt实际上不需要

别人好的解法：

    int removeDuplicates(vector<int>& nums) {
	    int count = 0, n = nums.size();
	    for(int i = 1; i < n; i++){
		    if(nums[i] == nums[i-1]) count++;
		    else nums[i-count] = nums[i];
		}
		return n-count;
	}
统计冗余的次数，同时可以得出下一个unique元素的下标，简洁

    int removeDuplicates(vector<int>& nums) {
	    int n = nums.size(), id = 0;
	    if (n < 2) return 0;
	    for (int i = 1; i < n; ++i)
		    if (nums[i] != nums[i-1]) nums[id++] = nums[i];
	    return id;
    }
   id标记下一个unique元素的下标，需要先判断数组大小

    int removeDuplicates(vector<int>& nums) {
	    int i = 0;
	    for (int n : nums)
	        if (!i || n > nums[i-1])
	            nums[i++] = n;
	    return i;
    }
   range-based循环版本，循环中需要特殊判断第一个元素

    int removeDuplicates(vector<int>& nums) {
	    int i = !nums.empty();
	    for (int n : nums)
	        if (n > nums[i-1])
	            nums[i++] = n;
	    return i;
	}
range-based循环版本，第一个元素判断提前，有点绕

## 189.Rotate Array

比较tricky的做法，翻转再局部翻转

    void rotate(vector<int>& nums, int k) {
	    k %= nums.size();
	    reverse(nums.begin(), nums.end());
	    reverse(nums.begin(), nums.begin() + k);
	    reverse(nums.begin() + k, nums.end());
	}

连续交换，注意陷入局部循环

    void rotate(vector<int>& nums, int k) {
        int n = nums.size(), start = 0;
        for (; k %= n; n -= k, start += k) {
            for (int i = 0; i < k; i++) {
                swap(nums[start + i], nums[start + n - k + i]);
            }
        }
    }
  

## 21. Merge Two Sorted List

递归

    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
	    if (!l1) return l2;
		if (!l2) return l1;
		if (l1->val < l2->val) {
			l1->next = mergeTwoLists(l1->next, l2);
			return l1;
		} else {
			l2->next = mergeTwoLists(l1, l2->next);
			return l2;
		}
	}

非递归, 冗余头结点

    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
	    ListNode dummy(-1);
	    ListNode *cur = &dummy, *c1 = l1, *c2 = l2;
	    while (c1 && c2) {
		    ListNode*& c = c1->val <= c2->val ? c1 : c2;
		    cur->next = c;
		    c = c->next;
		    cur = cur->next;
		}
		cur->next = c1 ? c1 : c2;
		return dummy.next;
	}

## 88. Merge Sorted Array

从后往前找大的填充

    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
	    int i = m - 1, j = n - 1, tar = m + n - 1;
	    while (j >= 0) {
		    nums1[tar--] = i >= 0 && nums1[i] > nums2[j] ? nums1[i--] : nums2[j--];
		}
	}

## 1. Two Sum

哈希表 一趟遍历

    vector<int> twoSum(vector<int>& nums, int target) {
	    unordered_map<int, int> imap;
	    for (int i = 0;; ++i) {
	        auto it = imap.find(target - nums[i]);
	        if (it != imap.end()) 
	            return vector<int> {i, it->second};
	        imap[nums[i]] = i;
	    }
	}

##  283. Move Zeros

    void moveZeroes(vector<int>& nums) {
	    int id = 0;
	    for (auto e: nums)
		    if (e) nums[id++] = e;
		
		for (int i = id; i < nums.size(); ++i)
			nums[i] = 0;
	}

## 66. Add One

    vector<int> plusOne(vector<int>& digits) {
	    int n = digits.size();
	    for (int i = n - 1; i >= 0; --i)
		    if (++digits[i] %= 10) return digits;
		
		digits[0] = 1;
		digits.push_back(0);
		return digits;
	}
无进位提前返回，有进位最高位强行设置1，尾巴补0

## 641. Design Circular Deque

    class MyCircularDeque {
	    vector<int> data;
	    int size;
	    int cap;
	    int front;
	    int rear;
	public:
	/** Initialize your data structure here. Set the size of the deque to be k. */
		MyCircularDeque(int k): data(k, 0), size(0), cap(k), front(k-1), rear(0) {}
		
	/** Adds an item at the front of Deque. Return true if the operation is successful. */
		bool insertFront(int value) {
			if (isFull()) return  false;
			data[front] = value;
			front = (cap + front - 1) % cap;
			++size;
			return  true;
		}
		
	/** Adds an item at the rear of Deque. Return true if the operation is successful. */
		bool insertLast(int value) {
			if (isFull()) return  false;
			data[rear] = value;
			rear = (rear + 1) % cap;
			++size;
			return  true;
		}
		
	/** Deletes an item from the front of Deque. Return true if the operation is successful. */
		bool deleteFront() {
			if (isEmpty()) return  false;
			front = (front + 1) % cap;
			--size;
			return  true;
		}
		
	/** Deletes an item from the rear of Deque. Return true if the operation is successful. */
		bool deleteLast() {
			if (isEmpty()) return  false;
			rear = (cap + rear - 1) % cap;
			--size;
			return  true;
		}
	/** Get the front item from the deque. */
		int getFront() {
			if (isEmpty()) return -1;
			return data[(front + 1) % cap];
		}
	/** Get the last item from the deque. */
		int getRear() {
			if (isEmpty()) return -1;
			return data[(cap + rear - 1) % cap];
		}
	/** Checks whether the circular deque is empty or not. */
		bool isEmpty() { return size == 0;}
	/** Checks whether the circular deque is full or not. */
		bool isFull() { return cap == size;}
	};

##  42. Trapping Rain Water

    int trap(vector<int>& height) {
	    int l = 0, r = height.size()-1, level = 0, water = 0;
	    while (l < r) {
		    int lower = height[height[l] < height[r] ? l++ : r--];
		    level = max(level, lower);
		    water += level - lower;
		}
		return water;
	}

