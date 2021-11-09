#include <cstdio>
#include <iostream>

#define SET_MOD 1000000007

#define DEBUG 0

using namespace std;

int tab[100010];

int left_count;
char visited[100010];

uintmax_t fac(int x) {
    uintmax_t s = 1;
    for(int i=2; i<=x; ++i) {
        s *= i;
        s %= SET_MOD;
    }
    return s;
}

int main() {
    // --- get input ---

    int n;
    scanf("%d", &n);
    left_count = n;
    for(int i=0; i<n; ++i) {
        scanf("%d", tab+i);
    }

    // --- check ---

    for(int i=0; i<n; ++i) {
        if(visited[tab[i]] > 0) {
            puts("0\n");
            return 0;
        }
        if(tab[i] == tab[i+2]) {
            // found pair - special visit
            if(visited[tab[i]] == 0) {
                visited[tab[i]] = -1;
            } else {
                puts("0\n");
                return 0;
            }
        } else {
            visited[tab[i]] = 1;
            left_count--;
        }
    }

    if(left_count == 0) {
        if(n%2 == 1) {
            puts("0\n");
        } else {
            puts("1\n");
        }
        return 0;
    }

    // --- calculate ---
    uintmax_t all_poss = fac(left_count);

    if (DEBUG)
    cout << "from left: " << all_poss << endl;

    // evens from left
    int i=0;

    // skip all propagated by first - number of possibilities for them is 1
    while(tab[i] != tab[i+2]) {
        i += 2;
    }
    i += 2;

    // skip all propagated by last if odd
    int our_n = (n%2 == 1 ? n-1 : n-2);
    if(n%2 == 1) {
        while(tab[our_n-2] != tab[our_n] && our_n > i) {
            our_n -= 2;
        }
    }

    if (DEBUG)
    cout << "skipped to: " << i << " - " << our_n << endl;

    int local_poss = 0;
    for(;i<our_n; i+=2) {
        local_poss++;

        if(tab[i] == tab[i+2]) {
            // found end
            all_poss *= local_poss;
            all_poss %= SET_MOD;
            local_poss = 0;
            i += 4;
        }
    }

    if(local_poss > 0)
    all_poss *= local_poss + 1;
    all_poss %= SET_MOD;

    // odds from right
    i = (n%2 == 0 ? n-1 : n-2);

    // skip all propagated by last if even
    if(n%2 == 0) {
        while(tab[i] != tab[i+2]) {
            i -= 2;
        }
    }
    i -= 2;

    if (DEBUG)
    cout << "skipped to: " << i << " - " << 0 << endl;

    local_poss = 0;
    for(;i>0; i-=2) {
        local_poss++;

        if(i > 2 && tab[i] == tab[i-2]) {
            all_poss *= local_poss;
            all_poss %= SET_MOD;
            local_poss = 0;
            i -= 4;
        }
    }

    if(local_poss > 0)
    all_poss *= local_poss + 1;
    all_poss %= SET_MOD;

    cout << all_poss << "\n";

    return 0;
}