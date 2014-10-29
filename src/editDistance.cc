/*

 */

#include <iostream>

using namespace std;

//经过增删改(一步) 变成另一个单词的最少步数
//fuck -> duck
//word -> world
//modle -> mode
/*public class Solution {
public  int minDistance(String word1, String word2) {
        //Check if any string is null or 0 size.It is kind of ugly...
        int row = 0;
        int col = 0;

        if (word1 != null)
            row = word1.length();
        if (word2 != null)
            col = word2.length();

        if (row == 0 || col == 0)
            return Math.max(row, col);

        int[][] matrix = new int[row+1][col+1];

            for (int i=0;i<=row;i++)
                matrix[i][0]=i;
            for (int i=0;i<=col;i++)
                matrix[0][i]=i;

            //Algorithm:minDistance(i,j)=min(minDistance(i-1,j),minDistance(i,j-1),minDistance(i-1,j-1))+1;

            for (int i=1;i<=row;i++){
                for (int j=1;j<=col;j++){
                    if (word1.charAt(i-1)==word2.charAt(j-1))
                        matrix[i][j]=matrix[i-1][j-1];//Remove and Add operation are not applicable.
                    else
                        matrix[i][j]=Math.min(Math.min(matrix[i-1][j], matrix[i][j-1]),matrix[i-1][j-1])+1;
                }
            }
            return matrix[row][col];
        }
}*/
class Solution {
public:
    //:
    int minDistance(string xx, string oo) {
        size_t row = xx.length();
        size_t col = oo.length();
        if (row == 0 || col == 0) return max(row, col);

        int opt[row + 1][col + 1];
        for (size_t i = 0; i <= row; ++i) {
            opt[i][0] = i;
        }
        for (size_t j = 0; j <= col; ++j) {
            opt[0][j] = j;
        }

        //Algorithm:minDistance(i,j)=min(minDistance(i-1,j),minDistance(i,j-1),minDistance(i-1,j-1))+1;
        for (size_t i = 1; i <= row; ++i) {
            for (size_t j = 1; j <= col; ++j) {
                if (xx[i - 1] == oo[j - 1]) {
                    opt[i][j] = opt[i - 1][j - 1];
                } else {
                    opt[i][j] = min(min(opt[i - 1][j], opt[i][j - 1]), opt[i - 1][j - 1]) + 1;
                }
            }
        }
        return opt[row][col];
    }

};

int main(int argc, char **argv) {

    Solution solution;

    int dis = solution.minDistance("word", "world");
    cout << dis << endl;
    dis = solution.minDistance("fuck", "duck");
    cout << dis << endl;

    return 0;
}