#include <bits/stdc++.h>
using namespace std;

/*
Notes:
   *Min cost matching in a bipartite graph partitioned into two sets X and Y
   *define isZero(a) and inf for double cost
   *for maximizing cost use negative cost
   *complexity O(n^3)
*/

#define MAX 1005
template <class Tb>
struct WeightedBPM {
   #define isZero(a) (!(a))
   int nodes, matched;
   int Xmate[MAX], Ymate[MAX], par[MAX];
   Tb inf;
   Tb cost[MAX][MAX], lx[MAX], ly[MAX], slack[MAX];
   bool S[MAX], T[MAX];

   WeightedBPM(int n) : nodes(n), matched(0), inf(numeric_limits<Tb>::max() / 4) {
      memset(Xmate, -1, sizeof(Xmate));
      memset(Ymate, -1, sizeof(Ymate));
   }
   void augment() {
      if(matched == nodes) return;

      memset(S, false, sizeof(S));
      memset(T, false, sizeof(T));
      memset(par, -1, sizeof(par));
      int root, y;
      for(root = 0; root < nodes; root++) if(Xmate[root] == -1) {
         S[root] = true;
         break;
      }
      for(y = 0; y < nodes; y++) {
         slack[y] = cost[root][y] - lx[root] - ly[y];
         par[y] = root;
      }

      while(true) {
         for(y = 0; y < nodes; y++) if(!T[y] && isZero(slack[y])) {
            if(Ymate[y] == -1) break; // augmenting path found
            // add edge (par[y], y) and (y, Ymate[y]) to the alternating tree
            T[y] = true;
            int x = Ymate[y];
            S[x] = true;
            for(int yy = 0; yy < nodes; yy++) if(cost[x][yy] - lx[x] - ly[yy] < slack[yy]) {
               slack[yy] = cost[x][yy] - lx[x] - ly[yy];
               par[yy] = x;
            }
         }
         if(y < nodes) break; // augmenting path found
         // update labels
         Tb del = inf;
         for(y = 0; y < nodes; y++) if(!T[y]) del = min(del, slack[y]);
         for(int i = 0; i < nodes; i++) {
            if(S[i]) lx[i] += del;
            if(T[i]) ly[i] -= del;
            else slack[i] -= del;
         }
      }

      matched++;
      while(y != -1) {
         int tmp = Xmate[ par[y] ];
         Xmate[ par[y] ] = y;
         Ymate[y] = par[y];
         y = tmp;
      }
   }
   Tb findMatch() {
      for(int x = 0; x < nodes; x++) {
         lx[x] = inf;
         ly[x] = 0;
         for(int y = 0; y < nodes; y++)
            lx[x] = min(lx[x], cost[x][y]);
      }
      while(matched < nodes) augment();
      Tb ret = 0;
      for(int x = 0; x < nodes; x++) ret += cost[x][ Xmate[x] ];
      return ret;
   }
};
