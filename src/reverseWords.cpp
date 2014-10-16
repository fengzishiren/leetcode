#include <iostream>
using namespace std;

static string &reverseWord(string &s, int start, int end) {
	while (start < end) {
		swap(s[start], s[end]);
		start++;
		end--;
	}
	return s;
}

void reverseWords(string &s) {
	int start = 0, end = s.size() - 1;
	while (start <= end) {
		if (s[start] == ' ')
			start++;
		else if (s[end] == ' ')
			end--;
		else
			break;
	}
	s = s.substr(start, end - start + 1);

	int cursor = 0;
	for (size_t i = 0; i < s.size(); ++i) {
		if (s[i] == ' ') {
			do
				i++;
			while (i < s.size() && s[i] == ' ');
			s[cursor++] = ' ';
		}
		s[cursor++] = s[i];
	}
	s = s.substr(0, cursor);

	//cout << "strip:" << s << endl;
	start = 0;
	for (size_t i = 0; i <= s.size(); ++i) {
		if (s[i] == ' ') {
			end = i - 1;
			while (i + 1 < s.size() && s[i + 1] == ' ')
				i++;
			reverseWord(s, start, end);
			start = i + 1;
		}

//		if (i == s.size()) {
//			end = i - 1;
//			reverseWord(s, start, end);
//			//start = i + 1;
//		}
	}
	reverseWord(s, start, s.size() - 1);
	//cout << "reverse:" << s << endl;
	reverseWord(s, 0, s.size() - 1);
}
//
//We can do better in one-pass.
//While iterating the string in reverse order, we keep track of a word’s begin and end position.
//When we are at the beginning of a word, we append it.
//eg:   one.   +two three?   ~four   !five-
//		!five- ~four three? +two one. 29
void _reverseWords(string& s) {
	string reverse;
	int j = s.size();
	for (int i = j - 1; i >= 0; --i) {
		if (s[i] == ' ')
			j = i;
		else if (i == 0 || s[i - 1] == ' ') {
			if (!reverse.empty())
				reverse += ' ';
			reverse.append(s.substr(i, j - i));
		}
	}
	s = reverse;
}


int main(int argc, char **argv) {

	std::string s = "   one.   +two three?   ~four   !five- ";
	cout << s << endl;
	_reverseWords(s);
	cout << s << " " << s.size();
	return 0;
}
