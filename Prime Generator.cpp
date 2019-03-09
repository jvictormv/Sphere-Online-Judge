#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin>>n;
    for(int i=1; i<=n; i++)
    {
        int a,b;
        cin>>a;
        cin>>b;

        if(a==1)
        {
            if(b==1) continue;
            else a++;
        }

        bool isprime;
        for(int j=a; j<=b; j++)
        {
            isprime = true;
            for(int k=2; k<=sqrt(j); k++)
            {
                if(j%k==0)
                {
                    isprime=false;
                    break;
                }
            }
            if(isprime) cout<<j<<endl;
        }
        cout<<endl;
    }
}
