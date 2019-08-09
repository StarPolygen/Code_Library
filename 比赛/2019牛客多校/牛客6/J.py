#Author :BigBang_019 签到模拟
def reverse(x):
    """
    :type x: int
    :rtype: int
    """
    # 判断是否为个位数，是个位数则不用反转，直接返回
    if -10 < x < 10:
        return x
    # 把整数x转为字符串
    str_x = str(x)
    # 判断第一个是否为负号
    if str_x[0] != "-":
        # 不是负号则直接反转
        str_x = str_x[::-1]
        # str转为int
        x = int(str_x)
    else:
        # 是负号，则反转负号之后的字符串
        str_x = str_x[1:][::-1]
        # str转int
        x = int(str_x)
        # 加上负号
        x = -x
    # 三目运算符，判断是否溢出
    # 如果-2147483648 < x < 2147483647则返回x，否则返回0
    return x
 
 
t = int(input())
while t > 0:
    t -= 1
    a, b = map(int, input().split())
    a = reverse(a)
    b = reverse(b)
    a = a + b
    a = reverse(a)
    print(a)