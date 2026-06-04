#include <unordered_map>
#include <string>
#include <iostream>
#include <algorithm>

using std::unordered_map;
using std::string;
using std::cout;
using std::max;
int longestSubstring(string & s){
    // Create two hashmaps
    unordered_map<string, int> indexes;
    unordered_map<char, int> chars(
        { { 'a', 0 }, { 'e', 1 }, 
          { 'i', 2 }, { 'o', 3 }, 
          { 'u', 4 } });

    // Keep the track of frequencies
    // of the vowels
    string evenOdd = "00000";
    indexes[evenOdd] = -1;

    // Stores the maximum length
    int length = 0;

    // Traverse the given string S
    for (int i = 0; i < s.size(); ++i) {

        char c = s[i];

        // Find character in the map
        auto it = chars.find(c);

        // If it is a vowel, then update
        // the frequency
        if (it != chars.end()) {
            evenOdd[it->second] = (evenOdd[it->second] == '0') ? '1' : '0';
        }

        // Find the index of occurrence
        // of the string evenOdd in map
        auto lastIndex = indexes.find(evenOdd);

        if (lastIndex == indexes.end()) {
            indexes[evenOdd] = i;
        }

        // Update the maximum length
        else {
            cout << "evenOdd: " << evenOdd << ", lastIndex: " << lastIndex->second << ", i: " << i << std::endl;
            length = max(length, i - lastIndex->second); // lastIndex is never updated
        }
    }

    return length;
}

int main()
{
    string S = "bcbcbc";
    cout << longestSubstring(S) << std::endl;

    return 0;
}
