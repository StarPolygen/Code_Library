#include <iostream>
using namespace std;
int main()
{
    int T;
    cin>> T;
    while(T--)
    {
        int n, res = 0, cnt = 0;
        cin>> n;
        for(int i=0; i<n; i++)
        {
            int w;
            cin>> w;
            res ^= w;
            if(w == 1) cnt++;
        }
        if(res && cnt != n) cout<< "John" <<endl;
        else if(!res && cnt == n) cout<< "John" <<endl;
        else cout<< "Brother" <<endl;


    }

    return 0;
}
