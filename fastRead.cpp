#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

inline int in(){
   char ch = getchar();
   while( (ch < '0' || ch > '9') && ch != '-') ch = getchar();
   bool flag = false;
   if (ch == '-'){
      flag = true;
      ch = getchar();
   }
   int ans = 0;
   while(ch >= '0' && ch <= '9'){
      ans = ans*10 + ch-'0';
      ch = getchar();
   }
   if (flag) return -ans;
   return ans;
}
