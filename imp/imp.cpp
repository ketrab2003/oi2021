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

    if(DEBUG)
    printf("initial: %llu\n", all_poss);

    // from left
    int prev = 0;
    for(int i=0; i<n; i += 2) {
        if (tab[i] == tab[i+2]) {
            // found pair

            // ignore if first block
            if(prev != 0) {
                if(DEBUG)
                //printf("block: %d - %d term: %d\n", prev, i, tab[i]);
                printf("%llu * %d\n", all_poss, (i - prev)/2 + 1);

                all_poss *= (i - prev)/2 + 1;
                all_poss %= SET_MOD;
            }

            prev = i + 4;
            i += 2;
        }
    }

    if(n%2==0) {
        // not ignore last block
        if(DEBUG)
        //printf("[left] last block: %d - %d\n", prev, n-2);
        printf("%llu * %d\n", all_poss, (n-2 - prev)/2 + 2);

        if(prev <= n-2) {
            all_poss *= (n-2 - prev)/2 + 2;
            all_poss %= SET_MOD;
        }
    }

    if(DEBUG)
    printf("\n");

    // from right
    prev = 1;
    for(int i=1; i<n; i += 2) {
        if (tab[i] == tab[i+2]) {
            // found pair
            if(DEBUG)
            //printf("block: %d - %d term: %d\n", prev, i, tab[i]);
            printf("%llu * %d\n", all_poss, (i - prev)/2 + 1);

            all_poss *= (i - prev)/2 + 1;
            all_poss %= SET_MOD;
            prev = i + 4;
            i += 2;
        }
    }

    if(n%2==1) {
        // not ignore last block
        if(DEBUG)
        //printf("[right] last block: %d - %d\n", prev, n-2);
        printf("%llu * %d\n", all_poss, (n-2 - prev)/2 + 2);

        if(prev <= n-2) {
            all_poss *= (n-2 - prev)/2 + 2;
            all_poss %= SET_MOD;
        }
    }

    cout << all_poss << '\n';

    return 0;
}