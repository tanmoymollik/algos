#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

/*
Notes:
   written for maximizing values
   while minimizing lines maximize the dual -y = (-mx-c)
*/

typedef long long Long;
const Long inf = 1000000000000000000LL;

struct Line {
   Long m, c;
   Line(Long _m = 0, Long _c = 0) : m(_m), c(_c) {};
   Long get(Long x) const { return m * x + c; }
   bool operator < (const Line &B) const { return m < B.m; }
};
inline bool isBad(Line &P, Line &C, Line &N) {
   return (P.c - C.c) * (N.m - P.m) >= (P.c - N.c) * (C.m - P.m);
}

// special case where lines have nondecreasing slope
struct ConvexHull {
   vector <Line> hull;

   void addLine(Long m, Long c) {
      if(hull.size() > 0 && hull.back().m == m) {
         if(hull.back().c < c) hull.pop_back();
         else return;
      }
      hull.push_back(Line(m, c));
      int sz = hull.size();
      while(sz > 2 && isBad(hull[sz-3], hull[sz-2], hull[sz-1])) {
         swap(hull[sz-2], hull[sz-1]);
         hull.pop_back();
         sz--;
      }
   }

   Long query(Long x) {
      if(hull.size() == 0) return -inf;
      int l = -1, r = hull.size() - 1;
      while(r - l > 1) {
         int m = (l + r) / 2;
         if(hull[m].get(x) <= hull[m+1].get(x)) l = m;
         else r = m;
      }
      return hull[r].get(x);
   }

   void clear() { hull.clear(); }
};

typedef tree <
   Line,
   null_type,
   less<Line>,
   rb_tree_tag,
   tree_order_statistics_node_update>
Oset;

// general case
struct ConvexHull {
   Oset hull;

   void addLine(Long m, Long c) {
      Oset::iterator it = hull.lower_bound(Line(m, c)), tmp;
      if(it != hull.end() && it->m == m) {
         if(it->c < c) hull.erase(it);
         else return;
      }
      hull.insert(Line(m, c));
      it = hull.lower_bound(Line(m, c));

      int p = hull.order_of_key(Line(m, c));
      int sz = hull.size();
      Line prev, cur, nxt;
      while(p >= 2) {
         tmp = it;
         nxt = *it; it--;
         cur = *it; it--;
         prev = *it;
         it = tmp;
         if(!isBad(prev, cur, nxt)) break;
         hull.erase(cur);
         p--; sz--;
      }
      while(sz - p > 2) {
         tmp = it;
         prev = *it; it++;
         cur = *it; it++;
         nxt = *it;
         it = tmp;
         if(!isBad(prev, cur, nxt)) break;
         hull.erase(cur);
         sz--;
      }
   }

   Long query(Long x) {
      if(hull.size() == 0) return -inf;
      int l = -1, r = hull.size() - 1;
      while(r - l > 1) {
         int m = (l + r) >> 1;
         Oset::iterator nxt = hull.find_by_order(m), prev;
         prev = nxt;;
         nxt++;
         if(prev->get(x) <= nxt->get(x)) l = m;
         else r = m;
      }
      return hull.find_by_order(r)->get(x);
   }

   void clear() { hull.clear(); }
};
