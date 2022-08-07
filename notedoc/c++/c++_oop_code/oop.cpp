//
// Created by 25467 on 2022/5/14.
//
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int ans = 0;
        set<char> derepeat;
        for (int i = 0; i < s.length(); i++) {
            derepeat.insert(s.at(i));
            int j = i + 1;
            for (; j < s.length(); j++) {
                if (derepeat.insert(s.at(j)).second == false)
                    break;
            }
            ans = max(ans, j - i);
            derepeat.clear();
        }
        return ans;
    }
};

int main() {
    string line;
    getline(cin, line);
    Solution s;
    cout << s.lengthOfLongestSubstring(line);

    return 0;
}

