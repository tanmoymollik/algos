#include <bits/stdc++.h>
using namespace std;

#define MAX 100005
// strongly connected component
int disc[MAX+MAX], low[MAX+MAX], comp[MAX+MAX], components, Tm; // they should be initialized
bool inStack[MAX+MAX];
vector <int> adj[MAX+MAX];
stack <int> S;
// Var is the number of variables without including the complements
// graph should be 0-based
// assign[i] is the value variable i
int Var, Tot;
bool assign[MAX+MAX];


inline int Not(int nd)
{
   return (nd < Var) ? nd+Var:nd-Var;
}

// takes clause (A || B)
inline void clause(int A, int B)
{
   adj[Not(A)].push_back(B);
   if(A == B) return;
   adj[Not(B)].push_back(A);
}

void dfs(int nd)
{
   disc[nd] = low[nd] = ++Tm;
   S.push(nd);
   inStack[nd] = true;
   for(int i = 0; i < adj[nd].size(); i++) {
      int ch = adj[nd][i];
      if(!disc[ch]) {
         dfs(ch);
         low[nd] = min(low[nd], low[ch]);
      }
      else if(inStack[ch]) {
         low[nd] = min(low[nd], disc[ch]);
      }
   }

   if(low[nd] == disc[nd]) {
      comp[nd] = components++;
      int u;
      do {
         u = S.top();
         S.pop();
         inStack[u] = false;
         comp[u] = comp[nd];
      } while(u != nd);
   }
}

bool two_SAT()
{
   memset(disc, 0, sizeof(disc));
   memset(low, 0, sizeof(low));
   Tm = components = 0;
   for(int i = 0; i < Tot; i++) if(!disc[i]) dfs(i);
   for(int i = 0; i < Var; i++) {
      if(comp[i] == comp[i+Var]) return false;
      assign[i] = (comp[i] > comp[i+Var]) ? false:true;
      assign[i+Var] = !assign[i];
   }
   return true;
}

void create_graph(int n)
{
   Var = n, Tot = n+n;
   for(int i = 0; i < Tot; i++) adj[i].clear();
}
