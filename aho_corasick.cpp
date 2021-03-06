#include <bits/stdc++.h>
using namespace std;

/*
	NOTES:: clear dict if multiple test cases
			  insert all words in dictionary and then call init_aho_corasick()
*/

namespace aho {
	#define MAXN 250005
	#define MAXW 505
	#define CHAR_SET 26
	#define MIN_CHAR 'a'
	struct automata {
		int next[CHAR_SET], f;
		vector <int> end;

		inline void set() {
		   memset(next, -1, sizeof(next));
		   end.clear();
		}
		void make_root() {
		   for(int i = 0; i < CHAR_SET; i++) next[i] = max(0, next[i]);
		   f = -1;
		}
	} node[MAXN];
	vector <string> dict;
	int NN;

	inline int go(int state, int nx)
	{
		if(node[state].next[nx] != -1) return node[state].next[nx];
		return node[state].next[nx] = go(node[state].f, nx);
	}

	void add(int pos)
	{
		int state = 0;
		for(int i = 0; i < dict[pos].size(); i++) {
		   int ch = dict[pos][i] - MIN_CHAR;
		   if(node[state].next[ch] == -1) {
		      node[NN].set();
		      node[state].next[ch] = NN++;
		   }
		   state = node[state].next[ch];
		}
		node[state].end.push_back(pos);
	}

	void fail()
	{
		queue <int> que;
		for(int i = 0; i < CHAR_SET; i++) if(go(0, i)) {
		   int s = go(0, i);
		   node[s].f = 0;
		   que.push(s);
		}

		while(!que.empty()) {
		   int tp = que.front(); que.pop();

		   for(int i = 0; i < CHAR_SET; i++) {
		      if(node[tp].next[i] == -1) continue;
		      int s = node[tp].next[i], r = go(node[tp].f, i);
		      que.push(s);
		      node[s].f = r;
		      for(int i = 0; i < node[r].end.size(); i++) node[s].end.push_back(node[r].end[i]);
		   }
		}
	}

	void Output(int state)
	{
		if(!node[state].end.size()) printf("no words end here");
		for(int i = 0; i < node[state].end.size()	; i++) {
		   if(i) printf(" ");
		   printf("%s", dict[ node[state].end[i] ].c_str());
		}
		puts("");
	}

	void init_aho_corasick()
	{
		node[0].set(); NN = 1;
		for(int i = 0; i < dict.size(); i++) add(i);
		node[0].make_root();
		fail();

	  // if additional operation be needed
	}
}
