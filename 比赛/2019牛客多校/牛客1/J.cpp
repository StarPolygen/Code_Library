//python 
//Author by zxy
import sys
while True:
    line = sys.stdin.readline()
    if not line:
        break
    x, a, y, b = map(int, line.split())
    l = x*b
    r = y*a
    if l == r:
        print('=')
    elif l < r:
        print('<')
    else:
        print('>')