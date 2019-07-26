//模拟  LRU的过程
//使用unordered_map将string映射到list中的迭代器，list中存储（string，int）的pair
#define ll long long
#include<string>
#include<vector>
#include<regex>
#include<algorithm>
#include<random>
#include<map>
#include<array>
#include<set>
#include<deque>
#include<iomanip>
#include<sstream>
#include<stack>
#include<iostream>
#include<limits>
#include<bitset>
#include<list>
#include<queue>
#include<memory.h>
#include<unordered_map>
#include<functional>
using namespace std;
struct ioss {
#define endl '\n'
    static const int LEN = 20000000;
    char obuf[LEN], *oh = obuf;
    std::streambuf *fb;
    ioss()
    {
        ios::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        fb = cout.rdbuf();
    }
    inline char gc() {
 
        static char buf[LEN], *s, *t, buf2[LEN];
        return (s == t) && (t = (s = buf) + fread(buf, 1, LEN, stdin)), s == t ? -1 : *s++;
    }
    inline ioss & operator >> (long long&x) {
        static char ch, sgn, *p;
        ch = gc(), sgn = 0;
        for (; !isdigit(ch); ch = gc()) { if (ch == -1)return *this; sgn |= ch == '-'; }
        for (x = 0; isdigit(ch); ch = gc())x = x * 10 + (ch^'0');
        sgn && (x = -x); return *this;
    }
    inline ioss & operator >> (int &x) {
        static char ch, sgn, *p;
        ch = gc(), sgn = 0;
        for (; !isdigit(ch); ch = gc()) { if (ch == -1)return *this; sgn |= ch == '-'; }
        for (x = 0; isdigit(ch); ch = gc())x = x * 10 + (ch^'0');
        sgn && (x = -x); return *this;
    }
    inline ioss & operator >> (char&x)
    {
        static char ch;
        for (; !isalpha(ch); ch = gc())
        {
            if (ch == -1)return *this;
        }
        x = ch;
        return *this;
    }
    inline ioss & operator >> (string &x)
    {
        static char ch, *p, buf2[LEN];
        for (; !isalpha(ch) && !isdigit(ch); ch = gc())
            if (ch == -1)return *this;
        p = buf2;
        for (; isalpha(ch)|| isdigit(ch); ch = gc())
            *p = ch, p++;
        *p = '\0';
        x = buf2;
        return *this;
    }
    inline ioss & operator <<(string &c)
    {
        for (auto &p : c)
            this->operator<<(p);
        return *this;
    }
    inline ioss & operator <<(const char *c)
    {
        while (*c != '\0')
        {
            this->operator<<(*c);
            c++;
        }
        return *this;
    }
    inline ioss & operator <<(const char &c) {
        oh == obuf + LEN ? (fb->sputn(obuf, LEN), oh = obuf) : 0;
        *oh++ = c;
        return *this;
    }
    inline ioss & operator <<(int x) {
        static int buf[30], cnt;
        if (x < 0)
            this->operator<<('-'),x=-x;
        if (x == 0)
            this->operator<<('0');
        for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 | 48;
        while (cnt) this->operator<<((char)buf[cnt--]);
        return *this;
    }
    inline ioss & operator <<(long long x) {
        static int buf[30], cnt;
        if (x < 0)
            this->operator<<('-'), x = -x;
        if (x == 0)
            this->operator<<('0');
        for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 | 48;
        while (cnt) this->operator<<((char)buf[cnt--]);
        return *this;
    }
    ~ioss()
    {
        fb->sputn(obuf, oh - obuf);
    }
} io; 
list<pair<string, int>> p;
unordered_map<string, list<pair<string, int>>::iterator> p2;

int main()
{
    int Q, M, T, opt, v, listSize;
    io>> T;
    while (T--)
    {
        io >> Q >> M;
        p.clear();
        p2.clear();
        listSize = 0;
        string s;
        for (int i = 1; i <= Q; i++)
        {
            io >> opt >> s >> v;
            if (opt == 0)
            { //查询
                if (p2.find(s) == p2.end())
                { //没找到
                    if (listSize == M)
                    { //满，需要在map中删除元素，并删除链表头
                        p2.erase(p.front().first);
                        p.pop_front();
                    }
                    else
                    { //未满
                        listSize++;
                    }
                    //放到链表尾
                    p.push_back(make_pair(s, v));
                    //Iterator放入mp
                    auto it = p.end();
                    it--;
                    p2[s] = it;
                    io<<v<<"\n";
                }
                else
                { //找到 删除链表相应元素，添加到链表尾，并将map中s对应的iterator更新
                    int kk = p2[s]->second;
                    io << kk << '\n';
                    p.erase(p2[s]);
                    p.push_back(make_pair(s, kk));
                    auto c = p.end();
                    c--;
                    p2[s] = c;
                }
            }
            else
            {
                if (p2.find(s) == p2.end())
                {
                    io<< "Invalid\n";
                    continue;
                }
                auto tmp = p2[s];
                if (v == 0)
                {
                    io << tmp->second << '\n';
                }
                else if (v == -1)
                {
                    if (tmp == p.begin())
                        io<< "Invalid\n";
                    else{
                        tmp--;
                        io<< tmp->second << '\n';
                    }
                       
                }
                else
                {
                    tmp++;
                    if (tmp == p.end())
                        io<< "Invalid\n";
                    else
                        io<< tmp->second << '\n';
                }
            }
        }
    }

    return 0;
}