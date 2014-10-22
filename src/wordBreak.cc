/*
 Word Break
 Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

 For example, given
 s = "leetcode",
 dict = ["leet", "code"].

 Return true because "leetcode" can be segmented as "leet code".
 */
#include <iostream>
#include <unordered_set>
#include <cstring>
using namespace std;

class Solution {
public:
	bool wordBreak(string s, unordered_set<string> &dict) {
		int ends[s.length() + 1];
		memset(ends, -1, sizeof(ends));
		int idx = 0;
		ends[idx] = s.length();
		for (int i = s.length() - 1; i >= 0; --i) {
			for (int j = idx; j >= 0; --j) {
				if (dict.find(s.substr(i, ends[j] - i)) != dict.end()) {
					ends[++idx] = i;
					break;
				}
			}
		}

		return ends[idx] == 0;
	}
};

int main(int argc, char **argv) {
	//"bb", ["a","b","bbb","bbbb"]
	unordered_set<string> dict = { "a", "b", "bbb", "bbbb" };
	bool b = Solution().wordBreak("bb", dict);
	cout << b << endl;
	return 0;
}

