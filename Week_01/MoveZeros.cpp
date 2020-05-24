class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int id = 0;
        for (auto e: nums)
            if (e) nums[id++] = e;

        for (int i = id; i < nums.size(); ++i)
            nums[i] = 0;
    }
};
