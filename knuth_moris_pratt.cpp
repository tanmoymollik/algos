#include <bits/stdc++.h>
using namespace std;

#define PB push_back
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
#define get(a) scanf("%d", &a)

#define MAX 1000005
string text, pattern;
// O[i] keeps longest prefix of pattern that is also a suffix of text[0...i]
int fail[MAX], O[MAX], occurance;

void KMP()
{
  // calculating fail
  fail[0] = 0;
  int j = 0;
  ITR(i, 1, pattern.SZ) {
    fail[i] = j;
    while(j > 0 && pattern[j] != pattern[i]) j = fail[j];
    if(pattern[j] == pattern[i]) j++;
  }
  fail[(int)pattern.SZ] = j;

  // calculating occurance
  j = 0, occurance = 0;
  REP(i, text.SZ) {
    while(j > 0 && pattern[j] != text[i]) j = fail[j];
    if(pattern[j] == text[i]) j++;
    O[i] = j;
    if(j == (int)pattern.SZ) occurance++, j = fail[j];
  }
}
