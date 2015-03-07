
#include <bits/stdc++.h>
using namespace std;
/*
*Author : Prateek Kumar Nischal @prateeknischal
*email  : prateeknischal25@gmail.com
*License : GPL v2.0
*
*Usage:
*	RollingHash object = RollingHash(string, [base = 0)
*	object.init()
*
*	Data Members:
*	strins s : the string given for hashing	
*	int length : length of the string
*	int base : base character for the character set
*	
*	Member functions:
*	void init() : initiates the hashing process
*	void setPrimeValue(long long) : set custom prime
*	void setModValue(long long)   : set custom MOD value
*	long long pow_mod(long long base, long long exp) : returns (base ^ exp) % MOD
*	long long getPrefixHash(int pos) : return hash[s[1..pos]]
*	long long getSubstringHash(int s, int e) : return hash[s[s..e]] inclusive 1-based index
*	bool compareSubstrings(int a, int b, int c, int d) : returns boolean true or false 
*														 if s[a..b] == s[c..d]
*/
class RollingHash
{
private:
	long long PRIME;
	long long MOD;
	long long *p;
	long long *Hash;
	int defaultLength;
	bool pre;
	/*
	*Precalculation of prime powers for hashing and offset
	*/
	void calculatePrimePowers(){
		p[0] = 1LL;
		for(int i = 1; i <= length; i++)
			p[i] = (p[i-1] * PRIME) % MOD;
		pre = true;
	}

	void hashString(){
		Hash[0] = 0LL;
		for(int i = 1; i<= length; i++){
			Hash[i] = (Hash[i-1] + (s[i-1] - base + 1) * p[i-1]) % MOD;
		}
	}
public:
	int length;
	int base;
	string s;

	/*
	*Default hash parameters for ASCII 'A'-'Z' and 'a'-'z'
	*base = the smallest value of the character set;
	*/
	RollingHash(){
		PRIME = 123LL;
		MOD = 1000000007LL;
		defaultLength = 100000;
		length = 0;
		base = 0;
		pre = false;
		p = (long long *)calloc(defaultLength, sizeof(long long));
		Hash = (long long *)calloc(defaultLength, sizeof(long long));
	}
	/*
	*Constructor with parameterized string input
	*declares a precomputation array of prime powers
	*base, in case you need to change the base of the 
	*character set;
	*/
	RollingHash(string ss, int b = 0){
		PRIME = 123LL;
		MOD = 1000000007LL;
		s = ss;
		base = b;
		pre = false;
		length = ss.size();
		p = (long long *)calloc(length + 2, sizeof(long long));
		Hash = (long long *)calloc(length + 2, sizeof(long long));
	}
	/*
	*User Defined MOD and Prime values in case the number of
	*unique characters is different than english alphabets
	*/
	void setPRIMEvalue(long long newPrime){
		PRIME = newPrime;
	}
	void setMODvalue(long long newMod){
		MOD = newMod;
	}
	
	/*
	*logarithmic time exponentiation
	*calculates (a ^ n) % MOD
	*/
	long long pow_mod(long long a, long long n){
		long long ans = 1LL, d = a;
		while (n){
			if (n & 1) ans = (ans * d) % MOD;
			n >>= 1;
			d = (d * d) % MOD;
		}
		return ans;
	}
	/*
	*1-based indexing in prefix position
	*returns the hash value of s[1..position]
	*/
	long long getPrefixHash(int position){
		return Hash[position];
	}

	/*
	*returns the substring hash value
	*H[i] = SUM_{q = 1..i}[ s[q] * PRIME^q ]
	*Hash(s[a..b]) = (Hash[b] - Hash[a-1]) * PRIME^-(a-1)
	*/
	long long getSubstringHash(int start, int end){
		long long inv = pow_mod(PRIME, MOD-2);
		inv = pow_mod(inv, start-1);
		long long hashValue = (Hash[end] - Hash[start - 1] + MOD) % MOD;
		hashValue = (hashValue * inv) % MOD;
		return hashValue;
	}
	/*
	*Compares two substrings s[a_s..a_e] and s[b_s..b_e]
	*returns boolean true or false
	*/
	bool compareSubstrings(int a_s, int a_e, int b_s, int b_e){
		/*
		*Strings of unequal lengths are never equal
		*/

		if (a_e - a_s != b_e - b_s) return false;

		/*
		*String hence now with same length if start with the 
		*same starting index
		*/

		if (b_s == a_s) return true;

		/*
		*arranging the indices for equal comparision
		*{a_s - a_e} < {b_s - b_e}
		*/

		if (b_s < a_s){
			swap(a_s, b_s);
			swap(a_e, b_e);
		}

		long long aHash = (Hash[a_e] - Hash[a_s-1] + MOD) % MOD;
		long long bHash = (Hash[b_e] - Hash[b_s-1] + MOD) % MOD;
		aHash = (aHash * p[b_s - a_s]) % MOD;
		return (aHash == bHash);
	}
	/*
	*General procedure for hashing a string
	*calculate
	*/
	void init(){
		if (!pre)
			calculatePrimePowers();
		hashString();
	}
	~RollingHash(){
		free(p);
		free(Hash);
	}
};

/*
Code to demostrate Hashing technique
SPOJ : http://www.spoj.com/problems/FILRTEST/
*/
/*
int main()
{
	int n = 0;
	while (n != -1){
		string s;
		cin >> n >> s;
		if (n == -1)return 0;
		int len = s.size();
		if (n < len){
			cout << 0 << endl;
			continue;
		}
		RollingHash h = RollingHash(s);
		h.init();
		int pref = 0;
		for(int i = 1; i<len; i++){
			if (h.compareSubstrings(1, i, len-i+1, len))
				pref = i;
		}
		cout << (int)((n - pref) / (len - pref)) << endl;
	}
	return 0;
}
*/
