from collections import namedtuple
from functools import partial
import sys

Movie = namedtuple('Movie', ['i', 't', 'd'])

tab = list(map(partial(map, int), map(str.split, sys.stdin.readlines()[1:])))

for i in range(len(tab)):
    tab[i] = Movie(i+1, *tab[i])

tab.sort(key=lambda x: (x.d, x.t))

longest_movie = Movie(-1, 0, 0)
sum_time = 0
used_movies = []

for m in tab:
    # print(used_movies, m)
    print(len(used_movies), m.t, m.d)

    if m.t > m.d:
        continue
    
    if sum_time + m.t <= m.d:
        used_movies.append(m)
        sum_time += m.t
        longest_movie = max(longest_movie, m, key=lambda x: (x.t, x.t-x.d))
        continue

    print('l:', longest_movie.t, longest_movie.d)

    if longest_movie.t > m.t:
        sum_time += m.t - longest_movie.t
        used_movies.remove(longest_movie)
        used_movies.append(m)
        longest_movie = max(used_movies, key=lambda x: (x.t, x.t-x.d))
    
    if longest_movie.t == m.t and (longest_movie.d - longest_movie.t) < (m.d - m.t):
        used_movies.remove(longest_movie)
        used_movies.append(m)
        longest_movie = max(used_movies, key=lambda x: (x.t, x.t-x.d))

print(len(used_movies))
s = 1
for m in used_movies:
    print(m.i, s)
    s += m.t