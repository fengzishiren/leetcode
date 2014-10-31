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
#include <vector>

using namespace std;

/*

 */

class Solution {
public:

    bool _(string s, unordered_set<string> &dict) {
        size_t start = 0;
        //bb b
        for (size_t i = 1; i <= s.length(); ++i) {
            if (dict.find(s.substr(start, i - start)) != dict.end()) {
                start = i;
            }
        }
        return start == s.length();
    }

    //origin
    bool wordBreak(string s, unordered_set<string> &dict) {
        int ends[s.length() + 1];
        //-1 == 0xffffffff if type is int
        memset(ends, -1, sizeof(ends));
        int idx = 0;//命中次数
        ends[idx] = s.length();//命中次数对应的结束位置
        for (int i = s.length() - 1; i >= 0; --i) {
            for (int j = idx; j >= 0; --j) {
                if (dict.find(s.substr(i, ends[j] - i)) != dict.end()) {
                    ends[++idx] = i;
                    break;//优先部分匹配，一经匹配就退出 so: ends.length == s.length + 1
                }
            }
        }
        return ends[idx] == 0;
    }

    //mine
    bool _wordBreak(string s, unordered_set<string> &dict) {
        size_t ends[s.length() + 1];
        memset(ends, -1, sizeof(ends));
        int cnt = 0;
        ends[0] = 0;

        //case: aaaaaaa [aaaa, aaa]
        for (size_t i = 1; i <= s.length(); ++i) {
            for (int j = cnt; j >= 0; --j) {
                // cout << cnt  << ' '<< ends[cnt] << ' '<< s.substr(ends[cnt], i - ends[cnt]) << endl;
                if (dict.find(s.substr(ends[j], i - ends[j])) != dict.end()) {
                    ends[++cnt] = i;
                    break;
                }
            }
        }
        return ends[cnt] == s.length();
    }

    //plus
    /*

Given a string s and a dictionary of words dict, add spaces in s to construct a sentence where each word is a valid dictionary word.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].

     */
    vector<string> wordBreakII(string s, unordered_set<string> &dict) {
        int n = s.length();
        vector<string> vt[n + 1];
        if (n == 0 || dict.empty()) return vt[0];
        for (int i = n - 1; i >= 0; --i) {
            vector<string> wd;
            for (int j = i; j < n; ++j) {
                string seg = s.substr(i, j - i + 1);
                vector<string> a(vt[j + 1]);
                if (dict.find(seg) != dict.end()) {
                    for (size_t k = 0; k < a.size(); ++k) {
                        wd.push_back(a[k].empty() ? seg : seg + ' ' + a[k]);
                    }
                }

            }
            vt[i] = wd;
        }
        return vt[0];
    }

};

int main(int argc, char **argv) {
    //"aaaaaaa", ["aaaa","aaa"]
    //"leetcode", ["leet", "code"]
    //"bb", ["a","b","bbb","bbbb"]
    unordered_set<string> dict = {"a", "b", "bbb", "bbbb"};
    Solution solution;
    bool b = solution._wordBreak("bb", dict);
    cout << b << endl;
    dict = {"leet", "code"};
    b = solution._wordBreak("leetcode", dict);
    cout << b << endl;
    dict = {"aaaa", "aaa"};
    b = solution._wordBreak("aaaaaaa", dict);
    cout << b << endl;
    cout << "end" << endl;
    return 0;
}
