#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        map<int, int> map;
        for (int i = 0; i < nums.size(); i++)
        {
            if (map.find(target - nums[i]) != map.end())
            {
                return {map[target - nums[i]], i};
            }
            else
            {
                map[nums[i]] = i;
            }
        }
        return {};
    }
};

int main()
{
    Solution solution;
    vector<int> position;
    int n, target;
    cin >> n;

    int nums[n];
    for (int i = 0; i < n; i++)
        cin >> nums[i];

    vector<int> arr;
    for (int i = 0; i < n; i++)
    {
        arr.push_back(nums[i]);
    }

    cin >> target;

    position = solution.twoSum(arr, target);
    vector<int> res;
    for (auto i : position)
        res.push_back(i);
    cout << res[0]<<" "<<res[1]<<endl;

    system("pause");
    return 0;
}
