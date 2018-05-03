#include <bits/stdc++.h>
using namespace std;

__int128 bigmod(__int128 a, __int128 pw, __int128 mod) {
   __int128 ret = 1;
   while(pw > 0) {
      if(pw & 1) ret = ret * a % mod;
      a = a * a % mod;
      pw >>= 1;
   }
   return ret;
}

/// rabin-miller primality test, tests k times for accuracy
bool isPrime(int k, __int128 n) {
   if(n == 2 || n == 3) return true;
   if(n <= 4 || n % 2 == 0) return false;

   int r = 0;
   __int128 d = n-1;
   while((d & 1) == 0) {
      r++;
      d >>= 1;
   }

   srand(time(0));
   while(k--) {
      __int128 a = rand() % (n-2);
      while(a < 2) a = rand() % (n-2);
      a = bigmod(a, d, n);
      if(a == 1 || a == n-1) continue;

      bool com = true;
      for(int i = 1; i < r; i++) {
         a = (a * a) % n;
         if(a == 1) return false;
         if(a == n-1) {
            com = false;
            break;
         }
      }
      if(com) return false;
   }
   return true;
}
