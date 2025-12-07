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
