#include <iostream>
#include <vector>

using namespace std;

void merge_helper (vector<int> & nums, int start, int end, int mid)
{
    int n1 = mid - start + 1;
    int n2 = end - mid;
    
    vector<int> half1(n1);
    vector<int> half2(n2);
    
    for (int i=0; i<n1; i++)
    {
        half1[i] = nums[start+i];
    }
    for (int i=0; i<n2; i++)
    {
        half2[i] = nums[mid+i+1];
    }
    
    // merge two sorted arrays into main nums array
    int k = start;
    int i=0, j=0;
    while (i < n1 && j < n2)
    {
        nums[k++] = half1[i] < half2[j]? half1[i] : half2[j];
        if (nums[k-1] == half1[i])
        {
            i++;
        }
        else
        {
            j++;
        }
    }
    while (i < n1) {
        nums[k++] = half1[i++];
    }

    // Copy the remaining elements of rightVec[], if any
    while (j < n2) {
        nums[k++] = half2[j++];
    }
}

void merge (vector<int> & nums, int start, int end)
{
    if (start < end)
    {
        int mid = start + (end - start) / 2;
        merge(nums, start, mid);
        merge(nums, mid+1, end);
        merge_helper(nums, start, end, mid);
    }
}
vector<int> sortArray(vector<int> nums) {
    int n = nums.size();
    if (n > 0) {
        merge(nums, 0, n-1);
    }
    return nums;
}

int main() {
    vector<vector<int>> tests = {
        {5, 2, 3, 1},
        {5, 1, 1, 2, 0, 0},
        {},
        {2},
        {3, -1, 4, 1, 0}
    };

    for (int i = 0; i < static_cast<int>(tests.size()); i++) {
        vector<int> sorted = sortArray(tests[i]);
        cout << "Test " << i + 1 << ": ";
        for (int num : sorted) {
            cout << num << " ";
        }
        cout << "\n";
    }

    return 0;
}
