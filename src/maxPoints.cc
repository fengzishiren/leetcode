/*
 Max Points on a Line

 Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
using namespace std;

//Definition for a point.
struct Point {
	int x;
	int y;
	Point() :
			x(0), y(0) {
	}
	Point(int a, int b) :
			x(a), y(b) {
	}
};
/*
 分析：

 任意一条直线都可以表述为

 y = ax + b

 假设，有两个点(x1,y1), (x2,y2)，如果他们都在这条直线上则有

 y1 = kx1 +b

 y2 = kx2 +b

 由此可以得到关系，k = (y2-y1)/(x2-x1)。即如果点c和点a的斜率为k, 而点b和点a的斜率也为k，可以知道点c和点b也在一条线上。

 取定一个点points[i], 遍历其他所有节点, 然后统计斜率相同的点数，并求取最大值即可


 注意：

 1. 垂直曲线， 即斜率无穷大

 2. 重复节点。
 */
class Solution {
public:
	int maxPoints(vector<Point> &points) {
		unordered_map<float, int> hash;
		int n = points.size();
		int maxNum = 0;
		if (n <= 2)
			return n;
		//主要思想：对于每一个点P，计算P和其他所有点的斜率并统计相同斜率的数目
		//最终求出所有点的maxNum
		for (int i = 0; i < n; ++i) {
			hash.clear();
			hash[INT_MIN] = 0;
			int dup = 1; //包含自己 统计重复的点数
			for (int j = 0; j < n; ++j) {
				if (i == j)
					continue;
				//eg: (2, 3) == (2, 3)
				if (points[i].x == points[j].x && points[i].y == points[j].y) {
					dup++;//记录重复
					continue;
				}
				//斜率
				float k =
						points[i].x == points[j].x ?
								INT_MAX :
								(float) (points[j].y - points[i].y)
										/ (points[j].x - points[i].x);
				hash[k]++;
			}
			//eval max point
			for (const auto& e : hash) {
				//最大点数包含重复点
				maxNum = max(e.second + dup, maxNum);
			}
		}

		return maxNum;
	}
};

//int main(int argc, char **argv) {
//
//	return 0;
//}

