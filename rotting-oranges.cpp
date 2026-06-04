#include <vector>
#include <climits>
#include <iostream>
#include <cstring>

using namespace std;

class Solution {
    int multiply (vector<vector<int>> & grid, int i, int j, int cur_min, int ** dp)
    {
        int max_min = cur_min;

        if ((i < 0 || i >= grid.size()) || (j < 0 || j >= grid[0].size()) || (dp[i][j] == 1))
        {
            return max_min;
        }

        dp[i][j] = 1;
        
        if (grid[i][j] == 0) 
        {
            return max_min;
        }
        
        if (i+1 < grid.size())
        {
            if (grid[i+1][j] == 1)
            {
                grid[i+1][j] = 2;
                int ret = multiply (grid, i+1, j, cur_min+1, dp);
                if (ret > max_min)
                {
                    max_min = ret;
                }
            }
        }
        if (i-1 >= 0)
        {
            if (grid[i-1][j] == 1)
            {
                grid[i-1][j] = 2;
                int ret = multiply (grid, i-1, j, cur_min+1, dp);
                if (ret > max_min)
                {
                    max_min = ret;
                }
            }
        }
        if (j+1 < grid[0].size())
        {
            if (grid[i][j+1] == 1)
            {
                grid[i][j+1] = 2;
                int ret = multiply (grid, i, j+1, cur_min+1, dp);
                if (ret > max_min)
                {
                    max_min = ret;
                }
            }
        }
        if (j-1 >= 0)
        {
            if (grid[i][j-1] == 1)
            {
                grid[i][j-1] = 2;
                int ret = multiply (grid, i, j-1, cur_min+1, dp);
                if (ret > max_min)
                {
                    max_min = ret;
                }
            }
        }
        if (max_min < cur_min)
        {
            max_min = cur_min;
        }
        return max_min;
    }
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int ** dp = new int*[grid.size()];
        for (int i=0; i<grid.size(); i++)
        {
            dp[i] = new int[grid[0].size()];
            memset (dp[i], 0, grid[0].size() * sizeof(int));
        }
        int max_val = -1;
        for (int i=0; i<grid.size(); i++)
        {
            for (int j=0; j<grid[i].size(); j++)
            {
                if (grid[i][j] == 2)
                {
                    int ret = multiply (grid, i, j, 0, dp);
                    if (ret > max_val)
                    {
                        max_val = ret;
                    }
                }
            }
        }
        for (int i=0; i<grid.size(); i++)
        {
            for (int j=0; j<grid[i].size(); j++)
            {
                if (grid[i][j] == 1)
                {
                    return -1;
                }
            }
        }
        return max_val;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> grid = {{2,1,1},{1,1,0},{0,1,1}};
    cout << sol.orangesRotting(grid) << endl;
    grid = {{2,1,1},{0,1,1},{1,0,1}};
    cout << sol.orangesRotting(grid) << endl;
    grid = {{0,0,0},{0,0,0},{0,0,0}};
    cout << sol.orangesRotting(grid) << endl;   
    grid = {{0,2}};
    cout << sol.orangesRotting(grid) << endl;
    return 0;
}
