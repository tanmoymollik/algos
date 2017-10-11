#include <bits/stdc++.h>
using namespace std;

/*
   NOTES:
   should use a tree with 0 based indexing of nodes. if 1 based indexing node then initialize chainHead[1] = 1 and chainPos[1] = 0
   example:
   chainHead[1] = 1;
   dfs(1, 1);
   hld(1);
   create(1, 0, BN-1);
*/

#define MAX 100005
int N, Q, Ara[MAX];
vector <int> adj[MAX];
int par[MAX], subSize[MAX], lvl[MAX];
int Base[MAX], BN;
int chainHead[MAX], chainID[MAX], chainPos[MAX], chainNext[MAX], posInBase[MAX], chains;

int dfs(int nd, int l)
{
   lvl[nd] = l;
   subSize[nd] = 1;
   for(int i = 0; i < adj[nd].size(); i++) {
      if(adj[nd][i] == par[nd]) continue;
      par[adj[nd][i]] = nd;
      subSize[nd] += dfs(adj[nd][i], l+1);
   }
   return subSize[nd];
}

void hld(int nd)
{
   chainID[nd] = chains;
   Base[BN] = Ara[nd];
   posInBase[nd] = BN++;
   int mx = 0, id = -1;
   for(int i = 0; i < adj[nd].size(); i++) {
      int ch = adj[nd][i];
      if(ch == par[nd]) continue;
      if(subSize[ch] > mx) mx = subSize[ch], id = ch;
   }
   chainNext[nd] = id;
   if(id != -1) {
      chainHead[id] = chainHead[nd];
      chainPos[id] = chainPos[nd]+1;
      hld(id);
   }

   for(int i = 0; i < adj[nd].size(); i++) {
      int ch = adj[nd][i];
      if(ch == par[nd] || ch == id) continue;
      chains++;
      chainHead[ch] = ch;
      chainPos[ch] = 0;
      hld(ch);
   }
}

int Lca(int u, int v)
{
   while(chainID[v] != chainID[u]) {
      if(lvl[chainHead[u]] < lvl[chainHead[v]]) v = par[chainHead[v]];
      else u = par[chainHead[u]];
   }
   return (lvl[u] < lvl[v]) ? u:v;
}
