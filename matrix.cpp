#include <bits/stdc++.h>
using namespace std;
#define PB push_back
#define MP make_pair
#define SZ size()
#define all(v) v.begin(), v.end()
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define ITR(i, j, n) for(int i = j; i < (int)n; i++)
#define mem(array, val) memset(array, val, sizeof(array))
#define READ(filename) freopen(filename, "r", stdin)
#define WRITE(filename) freopen(filename, "w", stdout)
#define Pii pair <int, int>
#define Fr first
#define Sc second
#define Long long long
#define si(a) scanf("%d", &a)
#define sii(a, b) scanf("%d%d", &a, &b)
#define sdd(a, b) scanf("%lf%lf", &a, &b)
#define Fast_IO ios_base::sync_with_stdio(0);cin.tie(0)

const Long mod = 1000000007;
const Long mod2 = mod*mod;
// structure matrix for use in matrix multiplication
struct Matrix {
   #define MAX_DIM 100
   int dim;
   Long val[MAX_DIM][MAX_DIM];

   Matrix(int dim) { this->dim = dim; memset(val, 0, sizeof(val)); }
   void identity() {
      memset(val, 0, sizeof(val));
      for(int i = 0; i < dim; i++) val[i][i] = 1;
   }
   Matrix operator * (const Matrix &A)
   {
      Matrix ret(dim);
      for(int i = 0; i < dim; i++)
         for(int j = 0; j < dim; j++) {
            Long sum = 0;
            for(int k = 0; k < dim; k++) {
               sum = sum + this->val[i][k] * A.val[k][j];
               if(sum >= mod2) sum -= mod2;
            }
            ret.val[i][j] = sum % mod;
      }
      return ret;
   }
   void print()
   {
      for(int i = 0; i < dim; i++) {
         for(int j = 0; j < dim; j++) {
            if(j) printf(" ");
            printf("%lld", val[i][j]);
         }
         puts("");
      }
   }
};
Matrix bigmod_mat(Matrix &A, Long pow)
{
   Matrix ret(A.dim);
   ret.identity();
   while(pow > 0) {
      if(pow & 1) ret = ret * A;
      A = A * A;
      pow >>= 1;
   }
   return ret;
}
