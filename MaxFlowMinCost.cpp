#include <bits/stdc++.h>
using namespace std;

/*
   NOTES:
   class Tf refers to the type of the flow and capacity of edges
   class Tc refers to the type of the cost
*/

#define MAX 2005
bool done[MAX];
int used[MAX];
template <class Tf, class Tc>
struct Edge {
   int from, to, next;
   Tf cap, flow;
   Tc cost;
   Edge(int from, int to, int next, Tf cap, Tc cost) {
      this->from = from;
      this->to = to;
      this->next = next;
      this->cap = cap;
      this->cost = cost;
      this->flow = 0;
   }
};
template <class Tf, class Tc>
struct MinCostFlow {
   typedef pair <Tc, int> Pti;
   const Tf infF;
   const Tc infC;
   const int nodes;
   int source, sink, nodeEnd[MAX];
   Tc dist[MAX], pi[MAX];
   vector < Edge <Tf, Tc> > edgeList;

   MinCostFlow(int n) : nodes(n), infF(numeric_limits<Tf>::max() / 4), infC(numeric_limits<Tc>::max() / 4) {
      memset(nodeEnd, -1, n * sizeof(int));
      fill(pi, pi+nodes, 0);
   }
   void addEdge(int u, int v, Tf cap = 1, Tc cost = 0) {
      edgeList.PB(Edge<Tf, Tc> (u, v, nodeEnd[u], cap, cost));
      nodeEnd[u] = (int)edgeList.SZ-1;
      edgeList.PB(Edge<Tf, Tc> (v, u, nodeEnd[v], 0, -cost));
      nodeEnd[v] = (int)edgeList.SZ-1;
   }

   // dijkstra
   bool augmentPath() {
      memset(used, -1, nodes*sizeof(int));
      memset(done, 0, nodes*sizeof(bool));
      fill(dist, dist+nodes, infC);
      priority_queue < Pti, vector <Pti>, greater <Pti> > que;
      que.push(make_pair(0, source));
      dist[source] = 0;

      while(!que.empty()) {
         int nd = que.top().second, ch;
         que.pop();
         if(done[nd]) continue;
         done[nd] = true;

         for(int i = nodeEnd[nd]; i != -1; i = edgeList[i].next) {
            ch = edgeList[i].to;
            Tc pot = dist[nd] + pi[nd] - pi[ch];
            if(edgeList[i].cap > edgeList[i].flow && pot + edgeList[i].cost < dist[ch]) {
               dist[ch] = pot + edgeList[i].cost;
               used[ch] = i;
               que.push(make_pair(dist[ch], ch));
            }
         }
      }
      for(int i = 0; i < nodes; i++) pi[i] = min(pi[i] + dist[i], infC);

      return dist[sink] != infC;
   }

   pair <Tf, Tc> maxFlow(int src, int snk) {
      source = src, sink = snk;
      Tf flow = 0;
      Tc cost = 0;

      while(augmentPath()) {
         // get blocking flow
         snk = sink;
         Tf bflow = infF;
         while(snk != source) {
            bflow = min(bflow, edgeList[ used[snk] ].cap - edgeList[ used[snk] ].flow);
            snk = edgeList[ used[snk] ].from;
         }
         // augment path
         snk = sink;
         while(snk != source) {
            edgeList[ used[snk] ].flow += bflow;
            edgeList[ used[snk] ^ 1 ].flow -= bflow;
            cost += edgeList[ used[snk] ].cost * bflow;
            snk = edgeList[ used[snk] ].from;
         }
         flow += bflow;
      }
      return make_pair(flow, cost);
   }
};
