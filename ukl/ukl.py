import sys

N, M = map(int, input().split())
N -= 1

if N == 1:
    print(1)
    sys.exit()

prev_sum_n = 1
tab_n = [prev_sum_n,] + [0,]*(N-1)

prev_sum_w = 1
tab_wt = [0,]*N
tab_w = [prev_sum_w,] + [0,]*(N-1)

for i in range(1, N-1):
    tab_n[i] = prev_sum_n %M + (N-i)*tab_n[i-1] %M + 1
    prev_sum_n += tab_n[i]

    tab_wt[i] = prev_sum_w %M + (N-i)*(N+i+1)//2*tab_n[i-1] %M + (N-i)*tab_wt[i-1] %M
    tab_w[i] = (tab_wt[i] + (i+1)*tab_n[i] %M) %M
    prev_sum_w += tab_w[i]

#print(tab_n, prev_sum_n)
#print(tab_w, prev_sum_w)

Sn = prev_sum_n + 1
Sw = prev_sum_w

res = (N+1)*N**2//2*Sn + (N+1)*Sw

print(res%M)