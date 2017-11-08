#include <bits/stdc++.h>
using namespace std;

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
