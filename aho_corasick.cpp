#include <bits/stdc++.h>
using namespace std;

//NOTES: link[] is a linked list to keep the occurance list

#define MAXN 250005
#define MAXW 505
#define char_set 26
struct automata {
   int next[char_set], f, end, head, tail;

   inline void set() {
      memset(next, -1, sizeof(next));
      end = 0;
      head = tail = -1;
   }
   void make_root() {
      for(int i = 0; i < char_set; i++) next[i] = max(0, next[i]);
      f = -1;
   }
} node[MAXN];
vector <string> dict;
string text;
int NN, link[MAXW];

inline int go(int state, int nx)
{
   if(node[state].next[nx] != -1) return node[state].next[nx];
   return node[state].next[nx] = go(node[state].f, nx);
}

// works with either lower case alphabets or upper case
void add(int pos)
{
   int state = 0;
   for(int i = 0; i < dict[pos].size(); i++) {
      int ch = dict[pos][i]-'a';
      if(node[state].next[ch] == -1) {
         node[NN].set();
         node[state].next[ch] = NN++;
      }
      state = node[state].next[ch];
   }
   node[state].end++;
   if(node[state].tail != -1) link[ node[state].tail ] = pos;
   if(node[state].head == -1) node[state].head = pos;
   node[state].tail = pos;
}

void fail()
{
   queue <int> que;
   for(int i = 0; i < char_set; i++) if(go(0, i)) {
      int s = go(0, i);
      node[s].f = 0;
      que.push(s);
   }

   while(!que.empty()) {
      int tp = que.front(); que.pop();

      for(int i = 0; i < char_set; i++) {
         if(node[tp].next[i] == -1) continue;
         int s = node[tp].next[i], r = go(node[tp].f, i);
         que.push(s);
         node[s].f = r;
         node[s].end += node[r].end;
         if(node[r].head == -1) continue;
         if(node[s].head == -1) node[s].head = node[r].head, node[s].tail = node[r].tail;
         else {
            link[ node[s].tail ] = node[r].head;
            node[s].tail = node[r].tail;
         }
      }
   }
}

void Output(int state)
{
   if(!node[state].end) printf("no words end here");
   for(int i = node[state].head; i != -1; i = link[i]) {
      if(i != node[state].head) printf(" ");
      printf("%s", dict[i].c_str());
   }
   puts("");
}

void init_aho_corasick()
{
   memset(link, -1, sizeof(link));
   node[0].set(); NN = 1;
   for(int i = 0; i < dict.size(); i++) add(i);
   node[0].make_root();
   fail();

  // if additional operation be needed
}
