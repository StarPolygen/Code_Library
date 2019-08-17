#CRT 高精度
#裸题 因此使用py
def exgcd(m, n):
    if n == 0:
        x = 1
        y = 0
        return m, x, y
    a1 = b = 1
    a = b1 = 0
    c = m
    d = n
    q = c//d
    r = c % d
    while r:
        c = d
        d = r
        t = a1
        a1 = a
        a = t-q*a
        t = b1
        b1 = b
        b = t-q*b
        q = c//d
        r = c % d
    x = a
    y = b
    return d, x, y
 
 
def CRT(m, r, n):
    if n == 0:
        return 0
    M = m[0]
    R = r[0]
    for i in range(1, n):
        d, x, y = exgcd(M, m[i])
        if (r[i] - R) % d != 0:
            return - 1
        x = (r[i] - R) // d * x % (m[i] // d)
        R += x * M
        M = M // d * m[i]
        R %= M
    return R if R >= 0 else R + M
 
 
mo = []
ri = []
n, m = map(int, input().split())
for i in range(n):
    tmp1, tmp2 = map(int, input().split())
    mo.append(tmp1)
    ri.append(tmp2)
ans = CRT(mo, ri, n)
if ans == -1:
    print("he was definitely lying")
elif ans > m:
    print("he was probably lying")
else:
    print(ans)