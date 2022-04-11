#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <stack>

using namespace std;

int visited_key = 0;
int visited[1010][1010];
int n, m;
char tab[1010][1010];

char pattern[1010];
int pattern_n;
int chain_lengths_gcd;

void mark_visited(int x, int y, bool d, int n, bool shadow=false) {
    for(int i=0; i<n; ++i) {
        if(d == 0) {
            visited[x+i][y] = visited_key + shadow;
        } else {
            visited[x][y+i] = visited_key + shadow;
        }
    }
}

void back_mark_visited(int x, int y, bool d, int n) {
    for(int i=0; i<n; ++i) {
        if(d == 0) {
            visited[x-i][y] = visited_key;
        } else {
            visited[x][y-i] = visited_key;
        }
    }
}

// int check(int x, int y, bool direction) {

//     if(direction == 0 && x + pattern_n > n) {
//         return 0;
//     }
//     if(direction == 1 && y + pattern_n > m) {
//         return 0;
//     }

//     for(int i=0; i < pattern_n; ++i) {
//         if(direction == 0) {
//             // horizontal check
//             if(tab[x+i][y] != pattern[i]) {
//                 return 0;
//             }
//         } else {
//             // vertical check
//             if(tab[x][y+i] != pattern[i]) {
//                 return 0;
//                 break;
//             }
//         }
//     }

//     if(direction == 0) {
//         return check(x+pattern_n, y, direction) + 1;
//     } else {
//         return check(x, y+pattern_n, direction) + 1;
//     }
// }

bool short_check(int x, int y, bool d) {
    for(int i=0; i<pattern_n; ++i) {
        if(d == 0) {
            if(tab[x+i][y] != pattern[i] || visited[x+i][y] == visited_key) {
                return false;
            }
        } else {
            if(tab[x][y+i] != pattern[i] || visited[x][y+i] == visited_key) {
                return false;
            }
        }
    }

    return true;
}

bool lookup_h(int x, int y, bool mark) {
    for(int i=0; i<pattern_n; ++i) {
        if(tab[x+i][y] != pattern[i] || visited[x+i][y] == visited_key) {
            return false;
        }
        if(mark) {
            visited[x+i][y] = visited_key;
        }
    }

    return true;
}

bool lookup_v(int y, int x, bool mark) {
    for(int i=0; i<pattern_n; ++i) {
        if(tab[x][y+i] != pattern[i] || visited[x][y+i] == visited_key) {
            return false;
        }
        if(mark) {
            visited[x][y+i] = visited_key;
        }
    }

    return true;
}

int locked_x[1010];
int locked_y[1010];
int locked_n;

int x_offset, y_offset;

bool _exp_check(bool (*lookup)(int, int, bool), int w, int h, int glob_offset) {
    locked_n = 0;
    
    int offset;

    // printf("target = %d / %d\n", w-glob_offset, pattern_n);

    if((w-glob_offset)%pattern_n != 0) {
        return false;
    }

    int target_locked = (w-glob_offset)/pattern_n;

    // find offset
    for(int x=0; x<w; ++x) {
        for(int y=0; y<h; ++y) {
            if(lookup(x, y, false)) {
                offset = x;
                locked_x[locked_n] = x;
                locked_y[locked_n++] = y;
                target_locked -= 1;
                // printf("offset: %d %d\n", x, y);
                break;
            }
        }
        if(locked_n > 0) {
            break;
        }
    }

    for(int x=offset+pattern_n; x<w; x += pattern_n) {

        if(target_locked == 0) {
            break;
        }

        for(int y=0; y<h; ++y) {
            if(lookup(x, y, false)) {
                locked_x[locked_n] = x;
                locked_y[locked_n++] = y;
                target_locked--;
                // printf("find: %d %d\n", x, y);
                break;
            }
        }
    }

    if(target_locked == 0) {
        // mark all locked as visited
        for(int i=0; i<locked_n; ++i) {
            // printf("locking: %d %d\n", locked_x[i], locked_y[i]);
            lookup(locked_x[i], locked_y[i], true);
        }
    }

    return (target_locked == 0);
}

bool exp_check() {
    x_offset = 0;
    y_offset = 0;
    visited_key++;

    while(m-x_offset > 0 && n-y_offset > 0) {
        if(_exp_check(lookup_v, m, n, y_offset)) {
            x_offset++;
        } else
        if(_exp_check(lookup_h, n, m, x_offset)) {
            y_offset++;
        } else {
            return false;
        }
    }

    return true;
}

stack<pair<int, int>> undecided_stack;

int short_check(int x, int y) {
    bool res0 = short_check(x, y, 0);
    bool res1 = short_check(x, y, 1);

    if(res0 && res1) {
        // printf("undecided %d %d\n", x, y);
        mark_visited(x, y, 0, pattern_n, true);
        mark_visited(x, y, 1, pattern_n, true);
        undecided_stack.push(make_pair(x, y));
        return 2;
    }
    if(res0) {
        mark_visited(x, y, 0, pattern_n);
        return 1;
    }
    if(res1) {
        mark_visited(x, y, 1, pattern_n);
        return 1;
    }
    return 0;
    // return short_check(x, y, 0) | short_check(x, y, 1);
}

bool back_check(int x, int y, bool d) {
    if(d == 0 && x-pattern_n < -1) {
        return false;
    }
    if(d == 1 && y-pattern_n < -1) {
        return false;
    }

    for(int i=0; i<pattern_n; ++i) {
        if(d == 0) {
            if(tab[x-pattern_n+1+i][y] != pattern[i] || visited[x-pattern_n+1+i][y] == visited_key) {
                return false;
            }
        } else {
            if(tab[x][y-pattern_n+1+i] != pattern[i] || visited[x][y-pattern_n+1+i] == visited_key) {
                return false;
            }
        }
    }

    back_mark_visited(x, y, d, pattern_n);

    return true;
}

bool _back_check(int x, int y) {
    return back_check(x, y, 0) | back_check(x, y, 1);
}

bool back_check(int x, int y) {
    if(y >= pattern_n-1) {
        if(visited[x][y-pattern_n+1] != visited_key) {
            if(short_check(x, y-pattern_n+1, 1)) {
                mark_visited(x, y-pattern_n+1, 1, pattern_n);
                return true;
            }
        }
    }

    if(x >= pattern_n-1) {
        if(visited[x-pattern_n+1][y] != visited_key) {
            if(short_check(x-pattern_n+1, y, 0)) {
                mark_visited(x-pattern_n+1, y, 0, pattern_n);
                return true;
            }
        }
    }

    return false;
}

bool check() {
    visited_key+=2;
    chain_lengths_gcd = 0;
    undecided_stack = stack<pair<int, int>>();

    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            if(visited[i][j] != visited_key && visited[i][j] != visited_key + 1) {
                // int l1 = check(i, j, 0);
                // int l2 = check(i, j, 1);
                // if(l1 > l2) {
                //     mark_visited(i, j, 0, pattern_n*l1);
                //     // chain_lengths_gcd = __gcd(chain_lengths_gcd, l1);
                // } else {
                //     mark_visited(i, j, 1, pattern_n*l2);
                //     // chain_lengths_gcd = __gcd(chain_lengths_gcd, l2);
                // }
                
                if(short_check(i, j) == 0) {
                    // printf("bad %d %d (%c)\n", i, j, tab[i][j]);
                    // return false;
                }
                // printf("%d %d\n", i, j);
            }
        }
    }

    // puts("back");

    while(!undecided_stack.empty()) {
        auto p = undecided_stack.top();
        undecided_stack.pop();
        int r = short_check(p.first, p.second);
        if(r != 1) {
            // printf("bbad %d %d (%c) (%d)\n", p.first, p.second, tab[p.first][p.second], r);
            return false;
        }
    }

    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            if(visited[i][j] != visited_key) {
                // printf("cbad %d %d (%c)\n", i, j, tab[i][j]);
                return false;
            }
        }
    }

    // for(int i=n-1; i>=0; --i) {
    //     for(int j=m-1; j>=0; --j) {
    //         if(visited[i][j] != visited_key) {
    //             if(!back_check(i, j)) {
    //                 printf("bbad %d %d (%c)\n", i, j, tab[i][j]);
    //                 return false;
    //             }
    //             // printf("%d %d\n", i, j);
    //         }
    //     }
    // }

    return true;
}

int tab_c[26];
int pattern_c[26];

void tab_gcd() {
    int g = 0;
    for(int i=0; i<26; ++i) {
        g = __gcd(g, tab_c[i]);
    }

    for(int i=0; i<26; ++i) {
        tab_c[i] /= g;
    }
}

bool verifyc() {
    // verify gcd of pattern with tab
    int ratio = -1;
    for(int i=0; i<26; ++i) {
        if(tab_c[i] == 0) {
            if(pattern_c[i] == 0) {
                continue;
            } else {
                return false;
            }
        }
        if(pattern_c[i] % tab_c[i] != 0) {
            return false;
        }

        if(ratio == -1) {
            ratio = pattern_c[i] / tab_c[i];
            continue;
        }

        if(pattern_c[i] / tab_c[i] != ratio) {
            return false;
        }
    }

    return true;
}

int find_pos = 0;
int find_i = 0;

bool find() {
    if(find_pos > 3) {
        return false;
    }

    while(true) {
        if(find_pos == 0) {
            if(find_i >= m) {
                break;
            }
        } else
        if(find_pos == 1) {
            if(find_i >= m) {
                break;
            }
            if(find_i + 1 >= n) {
                break;
            }
        } else
        if(find_pos == 2) {
            if(find_i >= n) {
                break;
            }
            if(find_i + 1 >= m) {
                break;
            }
        } else {
            if(find_i >= n) {
                break;
            }
        }

        char a, b;
        switch (find_pos)
        {
        case 0:
            a = tab[0][find_i];
            b = tab[1][find_i];
            break;
        case 1:
            a = tab[0][find_i];
            b = tab[find_i+1][0];
            break;
        case 2:
            a = tab[find_i][0];
            b = tab[0][find_i+1];
            break;
        case 3:
            a = tab[find_i][0];
            b = tab[find_i][1];
            break;
        }

        if(a != b) {
            break;
        }

        pattern[pattern_n++] = a;
        pattern_c[a-'a']++;

        find_i++;

        if(verifyc()) {
            return true;
        }
    }

    find_pos++;
    find_i = 0;
    pattern_n = 0;
    for(int i=0; i<26; ++i) {
        pattern_c[i] = 0;
    }

    return find();
}

char spec_d;

// special one-line finder
bool spec_find() {
    while(true) {
        if(spec_d == 0) {
            if(find_i >= m) {
                return false;
            }
        } else {
            if(find_i >= n) {
                return false;
            }
        }

        char a;
        switch (spec_d)
        {
        case 0:
            a = tab[0][find_i];
            break;
        case 1:
            a = tab[find_i][0];
            break;
        }

        pattern[pattern_n++] = a;
        pattern_c[a-'a']++;

        find_i++;

        if(verifyc()) {
            return true;
        }
    }
}

set<int> ans;

bool single = true;
char prevchar = '\0';

int main() {
    // --- load data ---
    scanf("%d%d", &n, &m);

    char a;
    for(int i=0; i<n; ++i) {
        scanf("\n");
        for(int j=0; j<m; ++j) {
            scanf("%c", &a);
            tab[i][j] = a;
            tab_c[a-'a']++;
            if(prevchar != '\0' && prevchar != a) {
                single = false;
            } else {
                prevchar = a;
            }
        }
    }

    tab_gcd();

    // for(int i=0; i<n; ++i) {
    //     printf("%s\n", tab[i]);
    // }

    // puts("DEBUG - Write pattern:");
    // scanf("\n%s", pattern);

    // printf("%s\n", pattern);

    // check();

    // printf("gcd: %d\n", chain_lengths_gcd);

    // --- find pattern ---


    if(single) {
        
        for(int i=1; i<=max(n, m); ++i) {
            if(n%i == 0 || m%i == 0) {
                ans.insert(i);
            }
        }

        printf("%d\n", ans.size());
        for(int v: ans) {
            printf("%d ", v);
        }

        return 0;
    }

    bool (*findfunc)() = find;

    if(n==1) {
        spec_d = 0;
        findfunc = spec_find;
    }

    if(m==1) {
        spec_d = 1;
        findfunc = spec_find;
    }

    while(findfunc()) {
        // pattern[pattern_n] = '\0';
        // printf("%s %d\n", pattern, pattern_n);
        if(exp_check() || check()) {
            ans.insert(pattern_n);
            // puts("YES");
            // break;
        }
    }

    // --- print results ---

    printf("%d\n", ans.size());
    for(int v: ans) {
        printf("%d ", v);
    }

    // if(pattern_n == 0) {
    //     puts("0\n");
    //     return 0;
    // }

    // // printf("%d %d\n", chain_lengths_gcd, pattern_n);

    // chain_lengths_gcd *= pattern_n;
    // for(int i=pattern_n; i <= chain_lengths_gcd; i+=pattern_n) {
    //     if(chain_lengths_gcd % i == 0) {
    //         ans[ans_n++] = i;
    //     }
    // }

    // printf("%d\n", ans_n);
    // for(int i=0; i<ans_n; ++i) {
    //     printf("%d ", ans[i]);
    // }
    // puts("");

    return 0;
}