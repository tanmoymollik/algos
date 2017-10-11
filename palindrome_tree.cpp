#include <bits/stdc++.h>
using namespace std;

// link is the maximum suffix palindrome link and reverse suffix link is optional
#define charset 26
#define minchar 'a'
#define MAX 300005
char S[MAX];
int cur;
struct node {
   int len, link, nxt[charset], cnt;
   //vector <int> rev_link;

   void Set(int len, int link)
   {
      this->len = len;
      this->link = link;
      memset(nxt, -1, sizeof(nxt));
      cnt = 0;
   }
} pal_tree[MAX+2];

void create(const char S[])
{
   int L = strlen(S);
   int lpal = -1, state[2] = {0, 0}, suffix = -1;
   cur = 1;
   for(int i = 0; i < 2; i++) pal_tree[i].Set(i-1, i-1);
   //pal_tree[0].rev_link.PB(1);
   for(int i = 0; i < L; i++) {
      while(i-1-lpal < 0 || S[i] != S[i-1-lpal]) {
         state[0] = pal_tree[state[0]].link;
         lpal = pal_tree[state[0]].len;
      }
      while(suffix >= lpal || S[i] != S[i-1-suffix]) {
         if(suffix == -1) break;
         state[1] = pal_tree[state[1]].link;
         suffix = pal_tree[state[1]].len;
      }
      if(suffix == lpal) suffix = 0, state[1] = 1;
      else suffix += 2, state[1] = pal_tree[state[1]].nxt[S[i] - minchar];
      lpal += 2;
      if(pal_tree[state[0]].nxt[S[i] - minchar] == -1) {
         pal_tree[++cur].Set(lpal, state[1]);
         pal_tree[state[0]].nxt[S[i] - minchar] = cur;
         //pal_tree[state[1]].rev_link.PB(cur);
      }
      state[0] = pal_tree[state[0]].nxt[S[i] - minchar];
      pal_tree[state[0]].cnt++;
   }

   for(int i = cur; i > 1; i--) {
      int u = pal_tree[i].link;
      if(u < 2) continue;
      pal_tree[u].cnt += pal_tree[i].cnt;
   }
}

/*
void clear()
{
   REP(i, cur+1) pal_tree[i].rev_link.clear();
}
*/

void print_tree(int state, string s)
{
   cout << s << ' ' << pal_tree[state].cnt << '\n';
   for(int i = 0; i < charset; i++) if(pal_tree[state].nxt[i] != -1) {
      string x = "";
      x = x + (char)(i+minchar);
      cout << "from " << s << " to " << x << " while state " << state << " to state " << pal_tree[state].nxt[i] << '\n';
      if(state) print_tree(pal_tree[state].nxt[i], x + s + x);
      else print_tree(pal_tree[state].nxt[i], s + x);
   }
}
