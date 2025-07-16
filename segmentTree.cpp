#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll, ll> pll;

#define Left(p) ((p)<<1)+1
#define Right(p) ((p)<<1)+2

const ll MOD = 1e9 + 7;

/*
    operation based segment tree
    eg: sum, min, max, gcd, etc
*/
class segmentTreeSum {
    /*
    Segment Tree Sum version
    
    */

    vl sum;
    int size;

    void build(int p, int L, int R, vl& a){
        if(L == R){
            if(L < (int)a.size()) sum[p] = a[L]; 
            return;
        }

        int mid = L + ((R-L)>>1);
        build(Left(p), L, mid, a);
        build(Right(p), mid+1, R, a);

        sum[p] = sum[Left(p)] + sum[Right(p)];
    }

    void set(int p, int L, int R, int ind, int v){
        if(L == R) {sum[p] = v; return;}

        int mid = L + ((R-L)>>1);
        if(ind <= mid) set(Left(p), L, mid, ind, v);
        else set(Right(p), mid+1, R, ind, v);

        sum[p] = sum[Left(p)] + sum[Right(p)];
    }

    long long rangeSum(int p, int L, int R, int l, int r){
        // 3 case -> to get sum
        if(L >= l && R<=r) return sum[p];        // case 1: bounded
        if(R < l || L > r) return 0;             // case 2: unbound

        int mid = L + ((R-L)>>1);

        // case 3: some portion bounded and some unbound
        return rangeSum(Left(p), L, mid, l, r) + rangeSum(Right(p), mid+1, R, l, r);
    }

public:
    segmentTreeSum(int n){
        size = 1;
        while(size < n) size *= 2;
        sum.assign(2*size, 0LL);
    }

    segmentTreeSum(vl& a) : segmentTreeSum((int)a.size()) {
        build(0, 0, size-1, a);
    }

    void set(int ind, int v){ set(0, 0, size-1, ind, v); }
    long long rangeSum(int l, int r){ return rangeSum(0, 0, size-1, l, r);}
};

class segmentTreeMin {
    /*
    segment Tree Minimum version
    */

    int size;
    vl minArr;

    void build(int p, int L, int R, vl& a){
        if(L == R){
            if(L < (int)a.size()) minArr[p] = a[L];
            return;
        }

        int mid = L + ((R-L)>>1);
        build(Left(p), L, mid, a);
        build(Right(p), mid+1, R, a);

        minArr[p] = min(minArr[Left(p)], minArr[Right(p)]);
    }

    void set(int p, int L, int R, int ind, int v){
        if(L == R) {minArr[p] = v; return;}

        int mid = L + ((R-L)>>1);
        if(ind <= mid) set(Left(p), L, mid, ind, v);
        else set(Right(p), mid+1, R, ind, v);

        minArr[p] = min(minArr[Left(p)], minArr[Right(p)]);
    }

    long long rangeMin(int p, int L, int R, int l, int r){
        // 3 case -> to get sum
        if(L >= l && R<=r) return minArr[p];        // case 1: bounded
        if(R < l || L > r) return INT64_MAX;        // case 2: unbound

        int mid = L + ((R-L)>>1);

        // case 3: some portion bounded and some unbound
        return min(rangeMin(Left(p), L, mid, l, r), rangeMin(Right(p), mid+1, R, l, r));
    }

public:
    segmentTreeMin(int n){
        size = 1;
        while(size < n) size *= 2;
        minArr.assign(size * 2, INT64_MAX);
    }

    segmentTreeMin(vl &a) : segmentTreeMin((int)a.size()){
        build(0, 0, size-1, a);
    }

    void set(int ind, int v){
        set(0, 0, size-1, ind, v);
    }

    long long rangeMin(int l, int r){
        return rangeMin(0, 0, size-1, l, r);
    }
};

// good way
class segmentTreeMinCount {
    /*
    segment Tree Minimum and Minimum count version
    */
public:
    struct item {
        int m, c;
    };

private:
    int size;
    vector<item> values;

    item NEUTRAL_ELEMENT = {INT_MAX, 0};

    item merge(item a, item b) {
        if(a.m < b.m) return a;
        if(a.m > b.m) return b;

        return {a.m, a.c + b.c};
    }

    item single(int v){
        return {v, 1};
    }

    void build(int p, int L, int R, vl& a){
        // single operation
        if(L == R){
            if(L < (int)a.size()) values[p] = single(a[L]);
            return;
        }

        int mid = L + ((R-L)>>1);
        build(Left(p), L, mid, a);
        build(Right(p), mid+1, R, a);

        // merge
        values[p] = merge(values[Left(p)], values[Right(p)]);
    }

    void set(int p, int L, int R, int ind, int v){
        // single operation
        if(L == R) {values[p] = single(v); return;}

        int mid = L + ((R-L)>>1);
        if(ind <= mid) set(Left(p), L, mid, ind, v);
        else set(Right(p), mid+1, R, ind, v);

        // merge
        values[p] = merge(values[Left(p)], values[Right(p)]);
    }

    item calc(int p, int L, int R, int l, int r){
        // 3 case -> to get sum
        if(L >= l && R<=r) return values[p];              // case 1: bounded
        if(R < l || L > r) return NEUTRAL_ELEMENT;        // case 2: unbound

        int mid = L + ((R-L)>>1);

        // case 3: some portion bounded and some unbound
        item a = calc(Left(p), L, mid, l, r);
        item b = calc(Right(p), mid+1, R, l, r);

        return merge(a, b);
    }

public:
    segmentTreeMinCount(int n){
        size = 1;
        while(size < n) size *= 2;
        values.resize(size * 2);
    }

    segmentTreeMinCount(vl &a) : segmentTreeMinCount((int)a.size()){
        build(0, 0, size-1, a);
    }

    void set(int ind, int v){
        set(0, 0, size-1, ind, v);
    }

    item calc(int l, int r){
        return calc(0, 0, size-1, l, r);
    }
};

/*
    other type
*/

class segmentTreeMaxSegSum {
    /*
    segment Tree Max Sum Segment version
    */
public:
    struct item {
        ll seg, pref, suf, sum;
    };

private:
    int size;
    vector<item> values;

    item NEUTRAL_ELEMENT = {0, 0, 0, 0};

    item merge(item a, item b) {
        return {
            max(a.seg, max(b.seg, a.suf + b.pref)),
            max(a.pref, a.sum + b.pref),
            max(b.suf, b.sum + a.suf),
            a.sum + b.sum
        };
    }

    item single(int v){
        if(v > 0) return {v, v, v, v};
        return {0, 0, 0, v};
    }

    void build(int p, int L, int R, vl& a){
        // single operation
        if(L == R){
            if(L < (int)a.size()) values[p] = single(a[L]);
            return;
        }

        int mid = L + ((R-L)>>1);
        build(Left(p), L, mid, a);
        build(Right(p), mid+1, R, a);

        // merge
        values[p] = merge(values[Left(p)], values[Right(p)]);
    }

    void set(int p, int L, int R, int ind, int v){
        // single operation
        if(L == R) {values[p] = single(v); return;}

        int mid = L + ((R-L)>>1);
        if(ind <= mid) set(Left(p), L, mid, ind, v);
        else set(Right(p), mid+1, R, ind, v);

        // merge
        values[p] = merge(values[Left(p)], values[Right(p)]);
    }

    item calc(int p, int L, int R, int l, int r){
        // 3 case -> to get sum
        if(L >= l && R<=r) return values[p];              // case 1: bounded
        if(R < l || L > r) return NEUTRAL_ELEMENT;        // case 2: unbound

        int mid = L + ((R-L)>>1);

        // case 3: some portion bounded and some unbound
        item a = calc(Left(p), L, mid, l, r);
        item b = calc(Right(p), mid+1, R, l, r);

        return merge(a, b);
    }

public:
    segmentTreeMaxSegSum(int n){
        size = 1;
        while(size < n) size *= 2;
        values.resize(size * 2);
    }

    segmentTreeMaxSegSum(vl &a) : segmentTreeMaxSegSum((int)a.size()){
        build(0, 0, size-1, a);
    }

    void set(int ind, int v){
        set(0, 0, size-1, ind, v);
    }

    item calc(int l, int r){
        return calc(0, 0, size-1, l, r);
    }
};

class segmentTreeKthOne {
    /*
    segment Tree Minimum and Minimum count version
    */
public:
    typedef int item;
    // struct item {
    //     int m, c;
    // };

private:
    int size;
    vector<item> values;

    item NEUTRAL_ELEMENT = 0;

    item merge(item a, item b) {
        return a + b;
    }

    item single(int v){
        return v;
    }

    void build(int p, int L, int R, vl& a){
        // single operation
        if(L == R){
            if(L < (int)a.size()) values[p] = single(a[L]);
            return;
        }

        int mid = L + ((R-L)>>1);
        build(Left(p), L, mid, a);
        build(Right(p), mid+1, R, a);

        // merge
        values[p] = merge(values[Left(p)], values[Right(p)]);
    }

    void set(int p, int L, int R, int ind, int v){
        // single operation
        if(L == R) {values[p] = single(v); return;}

        int mid = L + ((R-L)>>1);
        if(ind <= mid) set(Left(p), L, mid, ind, v);
        else set(Right(p), mid+1, R, ind, v);

        // merge
        values[p] = merge(values[Left(p)], values[Right(p)]);
    }

    item calc(int p, int L, int R, int l, int r){
        // 3 case -> to get sum
        if(L >= l && R<=r) return values[p];              // case 1: bounded
        if(R < l || L > r) return NEUTRAL_ELEMENT;        // case 2: unbound

        int mid = L + ((R-L)>>1);

        // case 3: some portion bounded and some unbound
        item a = calc(Left(p), L, mid, l, r);
        item b = calc(Right(p), mid+1, R, l, r);

        return merge(a, b);
    }

    int find(int p, int L, int R, int k){
        if(R == L) return L;

        int mid = L + ((R-L)>>1);

        int sl = values[Left(p)];
        if(k < sl) return find(Left(p), L, mid, k);
        return find(Right(p), mid+1, R, k - sl);

    }

public:
    segmentTreeKthOne(int n){
        size = 1;
        while(size < n) size *= 2;
        values.resize(size * 2);
    }

    segmentTreeKthOne(vl &a) : segmentTreeKthOne((int)a.size()){
        build(0, 0, size-1, a);
    }

    void set(int ind, int v){
        set(0, 0, size-1, ind, v);
    }

    item calc(int l, int r){
        return calc(0, 0, size-1, l, r);
    }

    int find(int k){
        return find(0, 0, size-1, k);
    }
};

/*
    also use in inversion, inverse inversion, etc problem
*/


// range update segment tree
class segmentTreeAddSeg {
    /*
        Segment tree Addition to segment
    */

    vl operations;
    int size;

    void build(int p, int L, int R, vl& a){
        if(L == R){
            if(L < (int)a.size()) operations[p] = a[L]; 
            return;
        }

        int mid = L + ((R-L)>>1);
        build(Left(p), L, mid, a);
        build(Right(p), mid+1, R, a);

        operations[p] = operations[Left(p)] + operations[Right(p)];
    }

    void set(int p, int L, int R, int ind, int v){
        if(L == R) {operations[p] = v; return;}

        int mid = L + ((R-L)>>1);
        if(ind <= mid) set(Left(p), L, mid, ind, v);
        else set(Right(p), mid+1, R, ind, v);

        operations[p] = operations[Left(p)] + operations[Right(p)];
    }

    long long rangeSum(int p, int L, int R, int l, int r){
        // 3 case -> to get sum
        if(L >= l && R<=r) return operations[p];        // case 1: bounded
        if(R < l || L > r) return 0;             // case 2: unbound

        int mid = L + ((R-L)>>1);

        // case 3: some portion bounded and some unbound
        return rangeSum(Left(p), L, mid, l, r) + rangeSum(Right(p), mid+1, R, l, r);
    }

    void add(int p, int L, int R, int l, int r, int v){
        // 3 case -> to get sum
        if(L >= l && R<=r){operations[p] += v; return;}        // case 1: bounded
        if(R < l || L > r) return;             // case 2: unbound

        int mid = L + ((R-L)>>1);

        // case 3: some portion bounded and some unbound
        add(Left(p), L, mid, l, r, v);
        add(Right(p), mid+1, R, l, r, v);
    }

    ll get(int p, int L, int R, int ind){
        if(L == R) return operations[p];

        int mid = L + ((R-L)>>1);
        ll ans;
        if(ind <= mid) ans = get(Left(p), L, mid, ind);
        else ans = get(Right(p), mid+1, R, ind);

        return ans + operations[p];
    }

public:
    segmentTreeAddSeg(int n){
        size = 1;
        while(size < n) size *= 2;
        operations.assign(2*size, 0LL);
    }

    segmentTreeAddSeg(vl& a) : segmentTreeAddSeg((int)a.size()) {
        build(0, 0, size-1, a);
    }

    void set(int ind, int v){ set(0, 0, size-1, ind, v); }
    long long rangeSum(int l, int r){ return rangeSum(0, 0, size-1, l, r);}
    void add(int l, int r, int v){ add(0, 0, size-1, l, r, v);}
    ll get(int i) {return get(0, 0, size-1, i);}
};

class segmentTreeRURM {
    /*
        Segment Tree Range Update Range Minimum
    */

    int size;
    vl operations, mins;

    void add(int p, int L, int R, int l, int r, int val){
        if(L > r || R < l) return;
        if(L >= l && R<=r){operations[p] += val; mins[p] += val; return;}

        int mid = L + ((R-L)>>1);
        add(Left(p), L, mid, l, r, val);
        add(Right(p), mid+1, R, l, r, val);

        mins[p] = min(mins[Left(p)], mins[Right(p)]) + operations[p];
    }

    ll rangeMin(int p, int L, int R, int l, int r){
        if(L > r || R < l) return LLONG_MAX;
        if(L >= l && R<=r) return mins[p];

        int mid = L + ((R-L)>>1);
        ll a = rangeMin(Left(p), L, mid, l, r);
        ll b = rangeMin(Right(p), mid+1, R, l, r);

        return min(a, b) + operations[p];
    }

public:
    segmentTreeRURM(int n){
        size = 1;
        while(size < n) size *= 2;
        operations.assign(2 * size, 0LL);
        mins.assign(2 * size, 0LL);
    }

    void add(int l, int r, int v){add(0, 0, size-1, l, r, v);}
    ll rangeMin(int l, int r){return rangeMin(0, 0, size-1, l, r);}
};

class segmentTreeRURQ {
    /*
        Segment Tree Range Update Range Query
        two type of operation in one

        eg: this involve multiple * and addition +
        modify: multiple each values in (l, r) range, hence modify_op
        query: add each value in (l, r) range, hence query_op

        another example: bitwise OR and AND operation
        modify: Bitwise OR each values in (l, r) range, hence modify_op
        query: Bitwise AND each value in (l, r) range, hence query_op
    */

    int size;
    vl operations, values;

    ll NEUTRAL_ELEMENT = 0;

    ll modify_op(ll a, ll b){
        return (a * b) % MOD;
    }

    ll query_op(ll a, ll b){
        return (a + b) % MOD;
    }

    void apply_mod_op(ll &a, ll b){
        a = modify_op(a, b);
    }

    void modify(int p, int L, int R, int l, int r, int val){
        if(L > r || R < l) return;
        if(L >= l && R<=r){
            apply_mod_op(operations[p], val);
            apply_mod_op(values[p], val);
            return;
        }

        int mid = L + ((R-L)>>1);
        modify(Left(p), L, mid, l, r, val);
        modify(Right(p), mid+1, R, l, r, val);

        values[p] = query_op(values[Left(p)], values[Right(p)]);
        apply_mod_op(values[p], operations[p]);
    }

    ll query(int p, int L, int R, int l, int r){
        if(L > r || R < l) return NEUTRAL_ELEMENT;
        if(L >= l && R<=r) return values[p];

        int mid = L + ((R-L)>>1);
        ll a = query(Left(p), L, mid, l, r);
        ll b = query(Right(p), mid+1, R, l, r);
        ll ans = query_op(a, b);
        apply_mod_op(ans, operations[p]);
        return ans;
    }

    // void build(int p, int L, int R){
    //     if(L == R) {values[p] = 1; return;}

    //     int mid = L + ((R-L)>>1);
    //     build(Left(p), L, mid);
    //     build(Right(p), mid+1, R);

    //     values[p] = query_op(values[Left(p)], values[Right(p)]);
    // }

public:
    segmentTreeRURQ(int n){
        size = 1;
        while(size < n) size *= 2;
        operations.assign(2 * size, 1LL);
        values.assign(2 * size, 0LL);
        // build(0, 0, size-1);
    }

    void modify(int l, int r, int v){modify(0, 0, size-1, l, r, v);}
    ll query(int l, int r){return query(0, 0, size-1, l, r);}
};

class segmentTreeRURQLazy {
    /*
        Segment Tree Range Update Range Query Lazy Propagation
    */

    int size;
    vl operations, values;

    ll NEUTRAL_ELEMENT = LLONG_MAX;
    ll NO_OPERATION = LLONG_MAX - 1;

    ll modify_op(ll a, ll b){
        if(b == NO_OPERATION) return a;
        return b;
    }

    ll query_op(ll a, ll b){
        return min(a, b);
    }

    void apply_mod_op(ll &a, ll b){
        a = modify_op(a, b);
    }

    void propagate(int p, int L, int R){
        if(L == R) return;

        int mid = L +  ((R-L)>>1);
        apply_mod_op(operations[Left(p)], operations[p]);
        apply_mod_op(values[Left(p)], operations[p]);
        apply_mod_op(operations[Right(p)], operations[p]);
        apply_mod_op(values[Right(p)], operations[p]);
        operations[p] = NO_OPERATION;
    }

    void modify(int p, int L, int R, int l, int r, int val){
        propagate(p, L, R);
        if(L > r || R < l) return;
        if(L >= l && R<=r){
            apply_mod_op(operations[p], val);
            apply_mod_op(values[p], val);
            return;
        }

        int mid = L + ((R-L)>>1);
        modify(Left(p), L, mid, l, r, val);
        modify(Right(p), mid+1, R, l, r, val);

        values[p] = query_op(values[Left(p)], values[Right(p)]);
        apply_mod_op(values[p], operations[p]);
    }

    ll query(int p, int L, int R, int l, int r){
        propagate(p, L, R);
        if(L > r || R < l) return NEUTRAL_ELEMENT;
        if(L >= l && R<=r) return values[p];

        int mid = L + ((R-L)>>1);
        ll a = query(Left(p), L, mid, l, r);
        ll b = query(Right(p), mid+1, R, l, r);
        ll ans = query_op(a, b);
        apply_mod_op(ans, operations[p]);
        return ans;
    }

    // void build(int p, int L, int R){
    //     if(L == R) {values[p] = 1; return;}

    //     int mid = L + ((R-L)>>1);
    //     build(Left(p), L, mid);
    //     build(Right(p), mid+1, R);

    //     values[p] = query_op(values[Left(p)], values[Right(p)]);
    // }

public:
    segmentTreeRURQLazy(int n){
        size = 1;
        while(size < n) size *= 2;
        operations.assign(2 * size, 0LL);
        values.assign(2 * size, 0LL);
        // build(0, 0, size-1);
    }

    void modify(int l, int r, int v){modify(0, 0, size-1, l, r, v);}
    ll query(int l, int r){return query(0, 0, size-1, l, r);}
};