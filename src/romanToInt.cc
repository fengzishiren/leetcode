/*
 Roman to Integer Total
 Given a roman numeral, convert it to an integer.

 Input is guaranteed to be within the range from 1 to 3999.
 */

#include <iostream>
#include <cstdlib>
using namespace std;

/*
 拼写规则[编辑]
 罗马数字共有7个，即I（1）、V（5）、X（10）、L（50）、C（100）、D（500）和M（1000）。按照下述的规则可以表示任意正整数。需要注意的是罗马数字中没有“0”，与进位制无关。一般认为罗马数字只用来记数，而不作演算。

 重复数次：一个罗马数字重复几次，就表示这个数的几倍。
 右加左减：
 在较大的罗马数字的右边记上较小的罗马数字，表示大数字加小数字。
 在较大的罗马数字的左边记上较小的罗马数字，表示大数字减小数字。
 左减的数字有限制，仅限于I、X、C。比如45不可以写成VL，只能是XLV
 但是，左减时不可跨越一个位数。比如，99不可以用IC（100 - 1）表示，而是用XCIX（[100 - 10] + [10 - 1]）表示。（等同于阿拉伯数字每位数字分别表示。）
 左减数字必须为一位，比如8写成VIII，而非IIX。
 右加数字不可连续超过三位，比如14写成XIV，而非XIIII。（见下方“数码限制”一项。）
 加线乘千：
 在罗马数字的上方加上一条横线或者加上下标的Ⅿ，表示将这个数乘以1000，即是原数的1000倍。
 同理，如果上方有两条横线，即是原数的1000000（1000^{2}）倍。
 数码限制：
 同一数码最多只能出现三次，如40不可表示为XXXX，而要表示为XL。
 例外：由于IV是古罗马神话主神朱庇特（即IVPITER，古罗马字母里没有J和U）的首字，因此有时用IIII代替IV。


 罗马数字	数值	拉丁语
 Ⅰ	1	unus
 Ⅱ	2	duo
 Ⅲ	3	tres
 Ⅳ	4	quattuor
 Ⅴ	5	quinque
 Ⅵ	6	sex
 Ⅶ	7	septem
 Ⅷ	8	octo
 Ⅸ	9	novem
 Ⅹ	10	decem
 Ⅺ	11	undecim
 Ⅻ	12	duodecim
 XIII	13	tresdecim
 XIV	14	quattuordecim
 XV	15	quindecim
 XVI	16	sedecim
 XVII	17	septendecim
 XVIII	18	duodeviginti
 XIX	19	undeviginti
 XX	20	viginti
 XXX	30	triginta
 XL	40	quadraginta
 L	50	quinquaginta
 LX	60	sexaginta
 LXX	70	septuaginta
 LXXX	80	octoginta
 XC	90	nonaginta
 XCIX	99	nonaginta novem
 C	100	centum
 CI	101	centum et unus
 CII	102	cij
 CXCIX	199	centum nonaginta novem
 CC	200	ducenti
 CCC	300	trecenti
 CD	400	quadringenta
 D	500	quincenti
 DC	600	sexcenta
 DCCC	800	octingenti
 CM	900	nongentos
 罗马数字	数值	拉丁语
 M	1,000	mille
 MCD	1,400	mille et quadringenti
 MCDXXXVII	1,437	triginta septem milia quadringenti
 MD	1,500	mille quincenti
 MDCCC	1,800	ut mille et octingenti
 MDCCCLXXX	1,880	et octoginta millia octingenti
 MCM	1,900	mille et nongentis
 MM	2,000	duo milia
 MMM	3,000	tria milia
 MMMCCCXXXIII	3,333	tria milia trecenti triginta tres
 MV	4,000	quattuor milia
 V	5,000	quinque milia
 X	10,000	decem millia
 L	50,000	quinquaginta millia
 C	100,000	deciens
 D	500,000	quinque deciens
 M	1,000,000	centiens
 */

class Solution {

public:
	int r2i(char n) {
		int ret = 0;
		switch (n) {
		case 'I':
			ret = 1;
			break;
		case 'V':
			ret = 5;
			break;
		case 'X':
			ret = 10;
			break;
		case 'L':
			ret = 50;
			break;
		case 'C':
			ret = 100;
			break;
		case 'D':
			ret = 500;
			break;
		case 'M':
			ret = 1000;
			break;
		default:
			error(string(1, n));
		}
		return ret;
	}
	//XCIX 99 99不可以用IC（100 - 1）表示，而是用XCIX（[100 - 10] + [10 - 1]）表示。（等同于阿拉伯数字每位数字分别表示。）
	int romanToInt(string s) {
		int v = 0;
		int x = 0;
		int p = 0;
		for (char c : s) {
			x = r2i(c);
			v += x > p ? x - 2 * p : x;
			p = x;
		}
		return v;
	}

	void error(const string& info) {
		cerr << info << endl;
		exit(1);
	}

};
//
//int main(int argc, char **argv) {
//
//	string s = "MCDXXXVII";
//	int V = Solution().romanToInt(s);
//	cout << V << endl;
//	return 0;
//}

