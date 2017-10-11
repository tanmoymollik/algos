#include <bits/stdc++.h>
using namespace std;


#define MAX 100005
int Count[MAX], output[MAX];
struct suffixArray {
   #define MAX_lg 17
   #define minchar 'a'
   #define Index(a) (((a) < len) ? index[mlgn][a] : -1)
   int pos[MAX], index[MAX_lg][MAX], lcp[MAX], len, mlgn;

   suffixArray() {}
   suffixArray(const char *S) { create(S); }
   void CountSort(int add) {
      int to = max(len, 26);
      memset(Count, 0, sizeof(Count));
      for(int i = 0; i < len; i++) ++Count[ Index(pos[i] + add) + 1 ];
      for(int i = 1; i <= to; i++) Count[i] += Count[i-1];
      for(int i = len-1; i >= 0; i--) output[ --Count[ Index(pos[i] + add) + 1 ] ] = pos[i];
      for(int i = 0; i < len; i++) pos[i] = output[i];
   }
   int Lcp(int x, int y) {
      int ret = 0;
      for(int i = mlgn; i >= 0 && x < len && y < len; i--) if(index[i][x] == index[i][y])
         x += (1 << i),
         y += (1 << i),
         ret += (1 << i);
      return ret;
   }
   void create(const char *S) {
      len = strlen(S), mlgn = 0;
      for(int i = 0; i < len; i++) index[0][i] = S[i] - minchar;
      for(int done = 1; done < len; done <<= 1) {
         for(int i = 0; i < len; i++) pos[i] = i;
         CountSort(done);
         CountSort(0);
         for(int i = 0; i < len; i++) {
            int sc1 = (i > 0) ? Index(pos[i-1] + done) : -1;
            int sc2 = Index(pos[i] + done);
            index[mlgn+1][pos[i]] = (i > 0 && index[mlgn][pos[i]] == index[mlgn][pos[i-1]] && sc1 == sc2) ? index[mlgn+1][pos[i-1]] : i;
         }
         mlgn++;
      }
      lcp[0] = 0;
      for(int i = 1; i < len; i++) lcp[i] = Lcp(pos[i], pos[i-1]);
   }
};
