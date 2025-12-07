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
