/*
 Simplify Path Total
 Given an absolute path for a file (Unix-style), simplify it.

 For example,
 path = "/home/", => "/home"
 path = "/a/./b/../../c/", => "/c"
 click to show corner cases.

 Corner Cases:
 Did you consider the case where path = "/../"?
 In this case, you should return "/".
 Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
 In this case, you should ignore redundant slashes and return "/home/foo".
 */
#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
	string simplifyPath(string path) {
		vector<string> vt;
		string sp;
		size_t start = 1;
		for (size_t i = 1; i < path.size(); ++i) {
			if (path[i] == '/' || i == path.size() - 1) {
				const string& s = path.substr(start,
						path[i] == '/' ? i - start : i - start + 1);
				//cout << s << endl;
				if (s == ".")
					start = i + 1;
				else if (s == "..") {
					if (!vt.empty()) {
						vt.pop_back();
					}
				} else if (!s.empty())
					vt.push_back(s);
				start = i + 1;
			}
		}

		for (auto s : vt) {
			sp += '/';
			sp += s;
		}
		return sp.empty() ? "/" : sp;
	}
};
//int main(int argc, char **argv) {
//	string s = Solution().simplifyPath("///");
//	cout << "KEY: " << s << endl;
//
//	return 0;
//}
