#include <bits/stdc++.h>
using namespace std;

#define MAX 100005
int odd[MAX], even[MAX];

void manachar(const char *S)
{
   int n = strlen(S), l, r, cur;

   // odd case
   l = r = -1;
   for(int i = 0; i < n; i++) {
      cur = 1;
      if(i < r) cur = min(r - i + 1, odd[l + r - i]);
      while(i+cur < n && i-cur >= 0 && S[i+cur] == S[i-cur]) cur++;
      odd[i] = cur;
      if(i + cur - 1 > r) {
         r = i + cur - 1;
         l = i - cur + 1;
      }
   }
   // even case
   l = r = -1;
   for(int i = 0; i < n; i++) {
      cur = 0;
      if(i < r) cur = min(r - i + 1, even[l + r - i + 1]);
      while(i+cur < n && i-cur-1 >= 0 && S[i+cur] == S[i-cur-1]) cur++;
      even[i] = cur;
      if(i + cur - 1 > r) {
         r = i + cur - 1;
         l = i - cur;
      }
   }
}
