#include <bits/stdc++.h>
using namespace std;

#define MAX (1 << 17)
typedef long long Long;

Long mod = 786433LL;

Long bigmod(Long a, Long pw) {
   Long ret = 1;
   while(pw > 0) {
      if(pw & 1) ret = ret * a % mod;
      a = a * a % mod;
      pw >>= 1;
   }
   return ret;
}

namespace FFT {
   /// MAX should be >= maximum power of polynomial to be multiplied * 2 and a power of 2
   /// functions that are also used by ntt are commented out like this
   /// if using ntt on a modulo ring mod then must ensure, for a polynomial of maximum len = 2^i, mod = c * 2^i + 1
   /// to find primitive root of mod ->
   /// first find prime factors of mu(mod), where mu(mod) is the number of relatively prime numbers with respect to mod
   /// for all prime factors di of mu(mod), if(e ^ (mu(mod) / di) % mod != 1) then e is a primitive root

   int rev[MAX], mlgn, root;
   double FA[MAX][2], FB[MAX][2], omega[MAX][2]; /// use for fft
   /// Long FA[MAX], FB[MAX], omega[MAX]; /// use for ntt

   inline void mult(double A[2], double B[2], double C[2])
   {
      C[0] = A[0]*B[0] - A[1]*B[1];
      C[1] = A[0]*B[1] + A[1]*B[0];
   }

   void calc_rev(int n = MAX)
   {
      while((1 << mlgn) < n) mlgn++;
      int lvl = 1, mx = (1<<mlgn);
      while(lvl < mx) {
         int j = 0, sg = 0;
         for(int i = 0; i < mx; i++) {
            rev[i] = (rev[i]<<1) | sg;
            j++;
            if(j == lvl) j = 0, sg ^= 1;
         }
         lvl <<= 1;
      }

      /// needed for ntt
      /*/// if mod is not a prime use the prime factors of mu(mod)
      vector <int> factors;
      Long mu = mod-1; /// mu(mod) for prime mod
      for(int i = 2; i*i <= mu; i++) {
         if(mu % i) continue;
         factors.push_back(i);
         while(mu % i == 0) mu /= i;
      }
      if(mu > 1) factors.push_back(mu);

      root = 2;
      mu = mod-1; /// mu(mod) for prime mod
      while(1) {
         bool fl = true;
         for(int di : factors) if(bigmod(root, mu / di) == 1) {
            fl = false;
            break;
         }
         if(fl) break;
         root++;
      }*/
   }

   void fft(double X[MAX][2], int n, bool invert)
   {
      int lgn = 0;
      while((1 << lgn) != n) lgn++;
      lgn = mlgn - lgn;
      for(int i = 0; i < n; i++) if(i < rev[i << lgn])
         swap(X[i], X[rev[i << lgn]]);

      double ang = ((2.0*M_PI)/n) * (invert ? -1.0:1.0);
      for(int i = 0; i < n; i++)
         omega[i][0] = cos(ang * i), omega[i][1] = sin(ang * i);
      for(int len = 2; len <= n; len <<= 1) {
         int fact = n / len;
         int len2 = len>>1;

         for(int i = 0; i < n; i += len) for(int j = 0; j < len2; j++) {
            double u[2], v[2];
            u[0] = X[i+j][0], u[1] = X[i+j][1];
            mult(X[i+j+len2], omega[j * fact], v);
            X[i+j][0] = u[0]+v[0], X[i+j][1] = u[1]+v[1];
            X[i+j+len2][0] = u[0]-v[0], X[i+j+len2][1] = u[1]-v[1];
         }
      }

      if(invert) for(int i = 0; i < n; i++)
         X[i][0] /= n, X[i][1] /= n;
   }

   void ntt(Long X[MAX], int n, bool invert) {
      int lgn = 0;
      while((1 << lgn) != n) lgn++;
      lgn = mlgn - lgn;
      for(int i = 0; i < n; i++) if(i < rev[i << lgn])
         swap(X[i], X[rev[i << lgn]]);

      omega[0] = 1;
      omega[1] = bigmod(root, (mod - 1) / n);
      if(invert) omega[1] = bigmod(omega[1], mod-2);
      for(int i = 2; i < n; i++)
         omega[i] = (omega[i-1] * omega[1]) % mod;

      for(int len = 2; len <= n; len <<= 1) {
         int fact = n / len;
         int len2 = len>>1;

         for(int i = 0; i < n; i += len) for(int j = 0; j < len2; j++) {
            Long u = X[i+j], v = (omega[j * fact] * X[i+j+len2]);
            X[i+j] = u+v;
            X[i+j+len2] = u-v;
         }
         for(int i = 0; i < n; i++) {
            X[i] %= mod;
            if(X[i] < 0) X[i] += mod;
         }
      }

      if(invert) {
         Long divBy_n = bigmod(n, mod-2);
         for(int i = 0; i < n; i++)
            X[i] = (X[i] * divBy_n) % mod;
      }
   }

   int multiply(Long A[MAX], Long B[MAX], int na, int nb, Long ret[MAX])
   {
      for(int i = 0; i < na; i++) FA[i][0] = (double)A[i], FA[i][1] = 0.0;
      /// for(int i = 0; i < na; i++) FA[i] = A[i];
      for(int i = 0; i < nb; i++) FB[i][0] = (double)B[i], FB[i][1] = 0.0;
      /// for(int i = 0; i < nb; i++) FB[i] = B[i];
      int n = 1;
      while(n < max(na, nb)) n <<= 1;
      n <<= 1;
      for(int i = na; i < n; i++) FA[i][0] = FA[i][1] = 0.0;
      /// for(int i = na; i < n; i++) FA[i] = 0;
      for(int i = nb; i < n; i++) FB[i][0] = FB[i][1] = 0.0;
      /// for(int i = nb; i < n; i++) FB[i] = 0;

      fft(FA, n, false);
      /// ntt(FA, n, false);
      fft(FB, n, false);
      /// ntt(FB, n, false);

      /// fft
      double tmp[2];
      for(int i = 0; i < n; i++) {
         mult(FA[i], FB[i], tmp);
         FA[i][0] = tmp[0], FA[i][1] = tmp[1];
      }
      fft(FA, n, true);
      int mx = 1;
      for(int i = 0; i < n; i++) {
         ret[i] = (Long)(FA[i][0] + 0.5);
         if(ret[i]) mx = i+1;
      }

      /// ntt
      /// for(int i = 0; i < n; i++)
         /// ret[i] = (FA[i] * FB[i]) % mod;
      /// ntt(ret, n, true);
      /// int mx = 1;
      /// for(int i = 0; i < n; i++) if(ret[i]) mx = i+1;

      return mx;
   }

   void print(Long ret[MAX], int n)
   {
      for(int i = 0; i < n; i++) {
         if(i) printf(" + ");
         printf("%lld", ret[i]);
         if(i) printf("x^%d", i);
      }
      puts("");
   }

   int bigmodFFT(Long x[MAX], Long ret[MAX], int nx, int pow) {
      int n = 1;
      ret[0] = 1;
      while(pow > 0) {
         if(pow & 1) n = multiply(ret, x, n, nx, ret);
         pow >>= 1;
         if(!pow) break;
         nx = multiply(x, x, nx, nx, x);
      }
      return n;
   }
}
