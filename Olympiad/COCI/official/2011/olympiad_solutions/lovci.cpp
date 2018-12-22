#include <algorithm>
#include <cstdio>
#include <functional>
#include <vector>

using namespace std;

#define MAXN 10

int n, k;
int a[2 * MAXN][2 * MAXN];
const int oo = 1000000000;

int steps[2 * MAXN][2 * MAXN];
int row_size[2 * MAXN], row_sum[2 * MAXN];
int col_size[2 * MAXN], col_sum[2 * MAXN];
int start_row, start_col;
vector<int> opt1, opt2;

void horizontal_flip() {
   for (int row = 0; row < 2 * n; ++row) 
      for (int col = 0; col < n; ++col)
         swap(a[row][col], a[row][2 * n - col - 1]);
}

vector<int> tmp;
void finish(int moves, int score, int max_row, int min_row) {
   int best_row = start_row;
   if (min_row <= start_row) {
      best_row = 0;
      for (int row = 0; row < min_row; ++row) 
  	 if (row_sum[row] > row_sum[best_row])
            best_row = row;
   }

   tmp.clear();
   for (int row = 0; row < max_row; ++row) {
      if (row == start_row || row == best_row) {
         score += row_sum[row];
         moves += row != start_row;
      } else {
         tmp.push_back(row_sum[row]);
      }
   }

   sort(tmp.begin(), tmp.end(), greater<int>());
   if (moves <= k) opt1[moves] = max(opt1[moves], score);
   for (int i = 0; i < tmp.size(); ++i) {
      score += tmp[i];
      moves += 1;
      if (moves <= k) opt1[moves] = max(opt1[moves], score);
   }
}

void rec(int col, int moves, int score, int max_row, int min_row) {
   if (col == 2 * (n - 1)) {
      finish(moves, score, max_row, min_row);
   } else {
      if (col != start_col) {
  	 rec(col + 1, moves, score, max_row, min_row);
      }
      for (int row = 0; row < col_size[col]; ++row)
         row_sum[row] -= steps[row][col];

      rec(col + 1, moves + (col != start_col), score + col_sum[col], 
	  max(max_row, col_size[col]), col_size[col]);

      for (int row = 0; row < col_size[col]; ++row)
         row_sum[row] += steps[row][col];
   }
}

int main(void) {
   scanf("%d%d", &n, &k);
   for (int row = 0; row < 2 * n; ++row) 
      for (int col = 0; col < 2 * n; ++col)
         scanf("%d", &a[row][col]);
   
   for (int player = 0; player < 2; ++player) {
      for( int i = 0; i < 2*n; ++i ) row_size[i] = col_size[i] = 0;
      for( int i = 0; i < 2*n; ++i ) row_sum[i] = col_sum[i] = 0;
      
      for (int i = 0, rows = 0; i < n; ++i) {
         for (int sgn_i = -1; sgn_i <= 1; sgn_i += 2) {
            if (i == 0 && sgn_i == 1) continue;
            for (int j = 0; j < n; ++j) {
               for (int sgn_j = -1; sgn_j <= 1; sgn_j += 2) {
                  int d1 = sgn_i * (2 * i);
                  int d2 = 2 * n - 1 + sgn_j * (2 * j + 1);
                  int r = (d1 + d2)/2;
                  int c = (d2 - d1)/2;
                  if (r >= 0 && r < 2*n && c >= 0 && c < 2*n) {
                     steps[rows][row_size[rows]] = a[r][c];
                     row_sum[rows] += a[r][c];
                     col_sum[row_size[rows]] += a[r][c];
                     ++col_size[row_size[rows]++];
                  }
               }
            }
            ++rows;
         }
      }

      start_row = 2 * (n / 2) - 1;
      start_col = 2 * ((n - 1) / 2);

      opt1.resize(k+1);
      fill(opt1.begin(), opt1.end(), -oo);

      rec(0, 0, 0, 0, 2 * n);

      opt1[0] -= steps[start_row][start_col];
      for (int i = 2; i <= k; ++i)
         opt1[i] = max(opt1[i], opt1[i-1]);

      horizontal_flip();
      swap(opt1, opt2);
   }

   int ret = -oo;
   for (int i = 0; i <= k; ++i) 
      ret = max(ret, opt1[i] + opt2[k-i]);
   printf("%d\n", ret);

   return 0;
}
