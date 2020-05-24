class Solution {
public:
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
};
