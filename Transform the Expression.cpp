#include <iostream>
#include <string>

using namespace std;

string RPNTransform(string str)
{
    if(str.length() <= 1) return str;
    if(str[0]=='(')
    {
        int start = 1;
        int idx = 1;
        string leftoperand = "";
        while(start!=0)
        {
            if(str[idx]=='(') start++;
            if(str[idx]==')') start--;
            if(start!=0) leftoperand += str[idx];
            idx++;
        }
        if(idx==str.length()) return RPNTransform(leftoperand);
        return RPNTransform(leftoperand) + RPNTransform(str.substr(idx+1,str.length()-1)) + str[idx];
    }
    return str[0] + RPNTransform(str.substr(2,str.length()-1)) + str[1];
}

int main()
{
    int n;
    cin>>n;

    for(int i=0; i<n;i++)
    {
        string str;
        cin>>str;
        cout<<RPNTransform(str)<<endl;
    }

}
