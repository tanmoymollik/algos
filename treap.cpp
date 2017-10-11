#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

#define MAX 100005
#define MAX_PRIORITY 1000000000
struct Treap {
   int key, prior, size;
   Treap *left, *right;
   Treap() {}
   Treap(int ky, int pr, Treap *l = NULL, Treap *r = NULL) :
      key(ky), prior(pr), left(l), right(r), size(1)  {}
   void update() {
      size = 1;
      if(left) size += left->size;
      if(right) size += right->size;
   }
   void push() {
      // lazy propagation
   }
};
typedef Treap* pTreap;
inline int count(pTreap id) { return (id) ? id->size : 0; }

void split(pTreap t, pTreap &l, pTreap &r, int key)
{
   if(!t) return void(l = r = NULL);
   t->push();
   if(key >= t->key)
      split(t->right, t->right, r, key), l = t;
   else
      split(t->left, l, t->left, key), r = t;
   t->update();
}
//implicit split
void split(pTreap t, pTreap &l, pTreap &r, int key)
{
   if(!t) return void(l = r = NULL);
   t->push();
   int cur_key = count(t->left) + 1;
   if(key >= cur_key)
      split(t->right, t->right, r, key - cur_key), l = t;
   else
      split(t->left, l, t->left, key), r = t;
   t->update();
}
void merge(pTreap &t, pTreap l, pTreap r)
{
   if(!l || !r) return void(t = (l) ? l : r);
   l->push();
   r->push();
   if(l->prior > r->prior)
      merge(l->right, l->right, r), t = l;
   else
      merge(r->left, l, r->left), t = r;
   t->update();
}
void insert(pTreap &t, pTreap it)
{
   if(!t) return void(t = it);
   t->push();
   if(it->prior > t->prior)
      split(t, it->left, it->right, it->key), t = it;
   else
      insert(it->key < t->key ? t->left : t->right, it);
   t->update();
}
//implicit insert (key should be 1 indexed)
void insert(pTreap &t, pTreap it, int key)
{
   if(!t) return void(t = it);
   t->push();
   int cur_key = count(t->left) + 1;
   if(it->prior > t->prior)
      split(t, it->left, it->right, key-1), t = it;
   else if(key <= cur_key) insert(t->left, it, key);
   else insert(t->right, it, key - cur_key);
   t->update();
}
void erase(pTreap &t, int key)
{
   t->push();
   if(t->key == key)
      merge(t, t->left, t->right);
   else
      erase(key < t->key ? t->left : t->right, key);
   t->update();
}
// implicit erase
void erase(pTreap &t, int key)
{
   t->push();
   int cur_key = count(t->left) + 1;
   if(cur_key == key)
      merge(t, t->left, t->right);
   else if(key < cur_key) erase(t->left, key);
   else erase(t->right, key - cur_key);
   t->update();
}
pTreap unite(pTreap l, pTreap r)
{
   if(!l || !r) return (l ? l : r);
   l->push();
   r->push();
   if(l->prior < r->prior) swap(l, r);
   pTreap lt, rt;
   split(r, lt, rt, l->key);
   l->left = unite(l->left, lt);
   l->right = unite(l->right, rt);
   l->update();
   return l;
}


// include srand(unsigned(time(NULL))) in main()
// intialize pTreap root = NULL;
// then insert(root, new Treap(rand() % MAX_PRIORITY + 1, ...), ...);
