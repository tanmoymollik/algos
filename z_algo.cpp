#include <bits/stdc++.h>
using namespace std;

// when using one string as pattern and another as text,
// should keep in mind that [l...r] segment is the prefix of pattern
// it may not be equal to the prefix of the text

#define MAX 100005
int Z[MAX];

void zAlgo(const char *S, int n)
{
   int l = 0, r = 0;
   Z[0] = n;
   for(int i = 1; i < n; i++) {
      if(i <= r && Z[i-l] < r-i+1) Z[i] = Z[i-l];
      else {
         l = i;
         if(i > r) r = i;
         while(r < n && S[r-l] == S[r]) r++;
         Z[i] = r-l; r--;
      }
   }
}
