#include <iostream>
#include <vector>
using std::vector;

class Solution {
    // Constant space and O(n) time - fast-slow pointers
    // Floyd's tortoise and hare method
public:
    int findDuplicate(vector<int>& nums) {

        // Find the intersection point of the two runners.
        int tortoise = nums[0];
        int hare = nums[0];

        do {
            tortoise = nums[tortoise];
            hare = nums[nums[hare]];
        } while (tortoise != hare);

        // Find the "entrance" to the cycle.
        tortoise = nums[0];
        while (tortoise != hare) {
            tortoise = nums[tortoise];
            hare = nums[hare];
        }

        return hare;
    }
};

int main() {
    Solution sol;
    const vector<vector<int>> tests = {
        {1, 3, 4, 2, 2},        // duplicate in the middle
        {3, 1, 3, 4, 2},        // duplicate at the front
        {1, 1},                 // smallest valid case
        {2, 2, 2, 2, 2},        // same duplicate repeated
        {1, 2, 3, 4, 4},        // duplicate at the end
        {2, 5, 1, 4, 3, 2},     // larger array with duplicate cycle
        {1,2,3}          // invalid case (no duplicate), should not be tested as per problem constraints
    };

    for (const auto& nums : tests) {
        std::cout << "Input: ";
        for (int x : nums) {
            std::cout << x << " ";
        }
        std::cout << "\n";
        std::cout << "Duplicate: " << sol.findDuplicate(const_cast<vector<int>&>(nums)) << "\n";
        std::cout << "---\n";
    }

    return 0;
}
