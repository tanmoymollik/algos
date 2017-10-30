#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

Long bigmod(Long x, Long pw, Long mod) {
   Long rt = 1 % mod;
   x %= mod;
   while(pw > 0) {
      if(pw & 1) rt = (rt * x) % mod;
      x = (x * x) % mod;
      pw >>= 1;
   }
   return rt;
}

// Chinese remainder Theorem
Long chinese_remainder(int r[], int p[], int n) {
   Long ans = 0, prod = 1;
   for(int i = 0; i < n; i++) prod *= p[i];

   for(int i = 0; i < n; i++) {
      Long rem = prod / p[i], inv = bigmod(rem, p[i]-2, p[i]);
      ans += (rem * inv % prod) * r[i] % prod;
      if(ans >= prod) ans -= prod;
   }
   return ans;
}

// Baby-step Giant-step
// returns smallest x for a^x = b (modulo mod)
// -1 for no solution
int baby_step(int a, int b, int mod) {
   map <int, int> mp;
   Long an = bigmod(a, N, mod), a_inv = bigmod(a, mod-2, mod);
   int n = sqrt(mod) + 1;
   Long cur = b;

   for(int i = 0; i < n; i++) {
      if(mp.find(cur) == mp.end()) mp[cur] = i;
      cur = cur * a_inv % mod;
   }
   cur = 1;
   for(int i = 0; i < n; i++) {
      if(mp.find(cur) != mp.end()) return i * n + mp[cur];
      cur = cur * an % mod;
   }
   return -1;
}


// extended euclid for ax + by = gcd(a, b)
// solutions x[i] = x[i-1] +- (b / gcd(a, b)), y[i] = y[i-1] -+ (a / gcd(a, b))
pair <Long, Long> extended_euclid(Long a, Long b) {
   if(!a) return make_pair(0, 1);
   pair <Long, Long> tmp = extended_euclid(b%a, a);
   return make_pair(tmp.second - (b / a) * tmp.first, tmp.first);
}
