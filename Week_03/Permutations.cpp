class Solution {
    void backtrack(int first, vector<int>& output, vector<vector<int>>& res)
    {
        if (first == output.size()) 
        {
            res.emplace_back(output);
            return;
        }

        for (int i = first; i < output.size(); ++i)
        {
            swap(output[i], output[first]);
            backtrack(first+1, output, res);
            swap(output[i], output[first]);
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > res;
        backtrack(0, nums, res);
        return res;
    }
};
