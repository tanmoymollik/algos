#include <bits/stdc++.h>
using namespace std;

#define MAX 200005
vector <int> G[MAX];

/// use 0 indexed or 1 indexed graph
namespace DominatorTree {
   int cnt, pos[MAX], best[MAX], p[MAX], parent[MAX], order[MAX];
   int link[MAX], idom[MAX], sdom[MAX];
   vector <int> G_rev[MAX], bucket[MAX];

   void dfs(int nd) {
      pos[nd] = cnt;
      order[cnt++] = nd;
      for(int ch : G[nd]) if(pos[ch] == -1) {
         dfs(ch);
         parent[ch] = nd;
      }
   }
   int findBest(int x) {
      if(p[x] != x) {
         int u = findBest(p[x]);
         if(pos[sdom[u]] < pos[sdom[best[x]]])
            best[x] = u;
         p[x] = p[p[x]];
      }
      return best[x];
   }
   void dominators(int N, int root) {
      cnt = 0;
      for(int i = 0; i <= N; i++) {
         pos[i] = parent[i] = idom[i] = -1;
         p[i] = best[i] = sdom[i] = i;
      }
      for(int i = 0; i <= N; i++)
         for(int u : G[i])
            G_rev[u].push_back(i);

      dfs(root);
      for(int i = cnt-1; i >= 1; i--) {
         int w = order[i];
         for(int u : G_rev[w]) if(pos[u] != -1) {
            int t = findBest(u);
            if(pos[sdom[t]] < pos[sdom[w]])
               sdom[w] = sdom[t];
         }
         bucket[sdom[w]].push_back(w);
         idom[w] = sdom[w];
         int pw = parent[w];
         for(int u : bucket[pw]) link[u] = findBest(u);
         bucket[pw].clear();
         p[w] = pw;
      }
      for(int i = 1; i < cnt; i++) {
         int u = order[i];
         idom[u] = idom[link[u]];
      }
      for(int i = 0; i <= N; i++) G_rev[i].clear();
   }
}
