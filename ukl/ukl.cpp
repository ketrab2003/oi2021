#include <cstdint>
#include <iostream>
#define ull uintmax_t
#define MUL_LIMIT 4294967290

using namespace std;

ull tab_n[1000010];
ull tab_w[1000010];
ull tab_wt[1000010];

ull addmod(ull a, ull b, ull m) {
    ull s = 0;

    a %= m;
    b %= m;

    while(a >= MUL_LIMIT) {
        s = (s + MUL_LIMIT)%m;
        a -= MUL_LIMIT;
    }

    s = (s + a)%m;

    while(b >= MUL_LIMIT) {
        s = (s + MUL_LIMIT)%m;
        b -= MUL_LIMIT;
    }

    s = (s + b)%m;
    return s;
}

ull mulmod(ull a, ull b, ull m) {
    ull s = 0;
    a %= m;
    b %= m;

    if(a > MUL_LIMIT) {
        s = mulmod(a/MUL_LIMIT, mulmod(MUL_LIMIT, b, m), m);
        a %= MUL_LIMIT;
    }

    while(b >= MUL_LIMIT) {
        s = addmod(s, MUL_LIMIT * a, m);
        b -= MUL_LIMIT;
    }

    s = addmod(s, b * a, m);
    return s;
}

int main() {
    ull N, M;
    cin >> N >> M;
    N--;

    if(N==1) {
        cout << 1 << endl;
        return 0;
    }

    ull prev_sum_n=1, prev_sum_w=1;
    tab_n[0] = prev_sum_n;
    tab_w[0] = prev_sum_w;
    tab_wt[0] = 0;

    for(ull i=1; i<N-1; ++i) {
        tab_n[i] = ( addmod(prev_sum_n, mulmod(N-i, tab_n[i-1], M), M) + 1 )%M;
        prev_sum_n = addmod(prev_sum_n, tab_n[i], M);

        tab_wt[i] = addmod( addmod(prev_sum_w %M, mulmod((N-i)*(N+i+1)/2, tab_n[i-1], M), M) , mulmod(N-i, tab_wt[i-1], M), M);
        tab_w[i] = addmod(tab_wt[i], mulmod(i+1, tab_n[i], M), M );
        prev_sum_w = addmod(prev_sum_w, tab_w[i], M);
    }

    cout << addmod( mulmod(mulmod(N*(N+1)/2, N, M) , (prev_sum_n+1), M) , mulmod(N+1, prev_sum_w, M), M) << endl;
}
