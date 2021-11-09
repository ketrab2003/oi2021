#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct Movie {
    int i, t, d;
    bool used=false;
};

bool movie_sort_cmp(Movie* a, Movie* b) {
    return (a->d != b->d ? a->d < b->d : a->t < b->t);
}

Movie vals[500010];
Movie* tab[500010];

int main() {
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; ++i) {
        tab[i] = &(vals[i]);
        tab[i]->i = i+1;
        scanf("%d%d", &(tab[i]->t), &(tab[i]->d));
    }

    sort(tab, tab+n, movie_sort_cmp);

    auto cmp = [](Movie* a, Movie* b) { return (a->t != b->t ? a->t < b->t : a->t-a->d < b->t-b->d); };
    priority_queue<Movie*, vector<Movie*>, decltype(cmp)> longest_used(cmp);
    long long sum_time = 0;
    int used_n = 0;

    for(int i=0; i<n; ++i) {
        Movie* m = tab[i];

        // printf("%d %d %d\n", used_n, m->t, m->d);
        
        if(m->t > m->d) {
            continue;
        }

        if(sum_time + m->t <= m->d) {
            sum_time += m->t;
            longest_used.push(m);
            m->used = true;
            used_n++;
            continue;
        }

        Movie* longest = longest_used.top();

        // printf("l: %d %d\n", longest->t, longest->d);

        if(longest->t > m->t) {
            sum_time += m->t - longest->t;
            longest_used.pop();
            longest_used.push(m);
            longest->used = false;
            m->used = true;
            continue;
        }

        if(longest->t == m->t && (longest->d - longest->t) < (m->d - m->t)) {
            longest_used.pop();
            longest_used.push(m);
            longest->used = false;
            m->used = true;
            continue;
        }
    }

    printf("%d\n", used_n);

    int t = 1;
    for(int i=0; i<n; ++i) {
        Movie* m = tab[i];
        if(m->used) {
            printf("%d %d\n", m->i, t);
            t += m->t;
        }
    }

    return 0;
}