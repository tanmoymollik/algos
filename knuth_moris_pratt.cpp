#include <bits/stdc++.h>
using namespace std;

// O[i] keeps longest prefix of pattern that is also a suffix of text[0...i]
// fail[i] keeps longest prefix of pattern that is also a **PROPER** suffix of pattern[0...i-1]
// returns number of occurance of pattern in text

int KMP(char *pattern, int plen, int *fail,  char *text, int tlen, int *O)
{
  // calculating fail
	fail[0] = 0;
	int j = 0;
	for(int i = 1; i < plen; i++) {
		fail[i] = j;
		while(j > 0 && pattern[j] != pattern[i]) j = fail[j];
		if(pattern[j] == pattern[i]) j++;
	}
	fail[plen] = j;

	// calculating occurance
	j = 0;
	int occurance = 0;
	for(int i = 0; i < tlen; i++) {
		while(j > 0 && pattern[j] != text[i]) j = fail[j];
		if(pattern[j] == text[i]) j++;
		O[i] = j;
		if(j == plen) occurance++, j = fail[j];
	}
	return occurance;
}
