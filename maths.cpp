#include <bits/stdc++.h>
using namespace std;

int MOD = 1e9 + 7;

long long GCD(long long a, long long b) {
    // recursive
    if(b == 0) return a;
    return GCD(b, a%b);

    // iterative
    /*
    long long tmp;
    while(b) {
        tmp = a;
        a = b;
        b = tmp % b;
    }
    return a;
    */
}

long long LCM(long long a, long long b) {
    return a / GCD(a, b) * b;
}

long long power(int x, int n){
    if(n == 0) return 1;
    long long ans = power(x, n / 2);
    ans *= ans; ans %= MOD;
    if(n % 2 != 0){ ans *= x; ans %= MOD;}
    return ans;
}

long long fact(int n){
    long long ans = 1;
    for(int i=1; i<=n; i++){ ans *= i; ans %= MOD;}
    return ans;
}

long long nCr(int n, int r){
    /*
    nCr = n!/(r!*(n-r)!)
    A = n!
    B = r!*(n-r)!
    nCr = (A / B) % MOD
        = (A * B^-1) % MOD
        
        // Fermat's Little Theorem
        // a^(MOD−1) ≡ 1 (mod MOD)
        // a^(MOD−2) ≡ a^−1 (mod MOD)
        
        = (A * B^(MOD - 2)) % MOD
    */
    long long nume = fact(n);
    long long deno = (fact(r) * fact(n-r)) % MOD;

    return (nume * power(deno, MOD-2)) % MOD;
}

long long modInverse(long long n) {
    return power(n, MOD - 2);
}

/*
    Extended Euclidean Algorithm
    a*x + b*y = gcd(a, b);
    a*s + b*t = gcd(a, b);
*/
int extEuclid(int a, int b, int &x, int &y) {      // pass x and y by ref
    int xx = y = 0;
    int yy = x = 1;
    int q, t;
    while (b) {                                    // repeats until b == 0
        q = a / b;
        t = b; b = a%b; a = t;                     // r
        t = xx; xx = x-q*xx; x = t;                // s
        t = yy; yy = y-q*yy; y = t;                // t
    }
    return a;                                      // returns gcd(a, b)
}


/*
    Prime Number

    1. bool isPrime(long long n):  
        O(n) : 2..(n-1)
        O(n^0.5) : 2..(n^0.5)
        O(n^0.5 / 2) : 2, 3, 5, 7 .. (n^0.5), only odd number except 2
        O(n^0.5 / ln(n^0.5)):  if list of prime number < n^0.5 known, O(m/ln(m)) number of primes less than m.
        
    2. sieve(n): generate list of prime numbers < n
        O(nlnln(n))

        to cheak if a number is prime: O(nlnln(n) + (n^0.5 / ln(n^0.5)))
*/

bool isPrime(long long n) {
    long long n_sqrt = sqrt(n);
    if(n == 2) return true;
    if(n < 2 || n % 2 == 0) return false;
    
    for(long long i=3; i<=n_sqrt; i+=2) {
        if(n % i == 0) return false;
    }

    return true;
}

// global variable for sieve
long long sieve_size;
bitset<10000010> bs;                     // 10^7 limit
vector<long long> prime;

void sieve(long long upperbound) {
    sieve_size = upperbound + 1;
    bs.set();
    bs[0] = bs[1] = 0;

    for(long long i=2; i<sieve_size; i++) {
        if(bs[i]) {
            for(long long j=i*i; j<sieve_size; j+=i) bs[j] = 0;
            prime.push_back(i);
        }
    }
}

// uses sieve
bool isPrime(long long n) {
    if(n < sieve_size) return bs[n];

    int m = prime.size();
    for(int i=0; i<m && (prime[i]*prime[i] <= n); i++)
        if(n % prime[i] == 0)
            return false;
    return true;
}

vector<long long> primeFactor(long long n) {
    vector<long long> factors;
    int m = prime.size();
    for(int i=0; i<m && (prime[i]*prime[i] <= n); i++) {
        while(n % prime[i] == 0) {
            n /= prime[i];
            factors.push_back(prime[i]);
        }
    }

    if(n != 1) factors.push_back(n);
    return factors;
}

long long CountDivisors(long long n) {
		int m = prime.size();
		long long ans = 1, cnt;
		for(int i=0; i<m && (prime[i]*prime[i] <= n); i++) {
			cnt = 0;
			while(n % prime[i] == 0) {
				n /= prime[i]; cnt++;
			}
			ans *= (cnt + 1);
		}

		if(n != 1) ans *= 2;
		return ans;
	}
