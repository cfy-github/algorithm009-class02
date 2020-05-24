class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        int start = 0;
        for (; k %= n; n -= k, start += k)
            for (int i = 0; i < k; ++i)
                swap(nums[start + i], nums[n + start + i - k]);
    }
};
