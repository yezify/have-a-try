#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;
void read(vector<int>& v) {
    char i;
    while (cin.peek() >= '0' && cin.peek()<='9')
    {
        cin >> i;
        v.push_back(i-48);
    };
    getchar();
}

void write(vector<int>& v) {
    while (v.size() != 0&&v[0] == 0)
    {
        v.erase(v.begin());
    }
    if (v.size()!=0) for (vector<int>::iterator it = v.begin(); it != v.end(); it++) printf("%d", *it);
    else printf("0");
    printf("\n");
}

int compare(vector<int>& n1, vector<int>& n2) {
    if (n1.size() > n2.size()) return 1;
    else {
        if (n1.size() < n2.size()) return 2;
        else
        {
            for (int i = 0; i< n2.size(); i++)
            {
                if(n1[i] != n2[i]) return (n1[i] > n2[i] ? 1: 2);
            }
            return 1;
        }
    }
}

void myadd(vector<int>& n1, vector<int>& n2,vector<int>& ans) {
    int cmp = compare(n1, n2) - 1;
    int len,temp=0;
    vector<int>::iterator i;
    if (cmp)
    {
        ans = n2;
        len = n1.size();
        vector<int>::iterator i = ans.end() - 1;
        for (int j=1;j<=len;j++)
        {
            *i += n1[len - j];
            if(i!=ans.begin()) i--;
        }
    }
    else
    {
        ans = n1;
        len = n2.size();
        vector<int>::iterator i = ans.end() - 1;
        for (int j = 1; j <= len; j++)
        {
            *i += n2[len - j];
            if (i != ans.begin()) i--;
        }
    }
    for (i=ans.end()-1; i>ans.begin(); i--)
    {
        *i += temp;
        if (*i > 9)
        {
            temp = *i / 10;
            *i = *i % 10;
        }
        else temp = 0;
    }
    *i += temp;
    if (*i > 9)
    {
        temp = *i / 10;
        *i = *i % 10;
    }
    else temp = 0;
    if (temp == 1) ans.insert(ans.begin(), 1);
}


void myminus (vector<int>& n1, vector<int>& n2, vector<int>& ans){
    int cmp = compare(n1, n2) - 1;
    vector<int>::iterator i;
    int len1 = n1.size(), len2 = n2.size(),temp=0;
    if (cmp) {
        ans = n2;
        for (int j=1; j <= len1; j++)
        {
            ans[len2 - j] -= n1[len1 - j];
        }
    }
    else
    {
        ans = n1;
        for (int j = 1; j <= len2; j++)
        {
            ans[len1 - j] -= n2[len2 - j];
        }
    }
    for (i = ans.end() - 1; i > ans.begin(); i--)
    {
        *i += temp;
        if (*i < 0)
        {
            temp = -1;
            *i = *i + 10;
        }
        else temp = 0;
    }
    *i += temp;
}

void mymul(vector<int>& n1, vector<int>& n2, vector<int>& ans)
{
    vector<int>::iterator i;
    int len1 = n1.size(), len2 = n2.size(),lena=len1+len2+1,temp = 0;
    vector<int> anss(len1 + len2 + 1, 0);
    for (int i = 0; i < len1; i++)
    {
        for (int j = 0; j < len2; j++)
        {
            anss[lena - i - j-1] += n1[len1 - i-1] * n2[len2 - j-1];
        }
    }
    ans = anss;
    for (i = ans.end() - 1; i > ans.begin(); i--)
    {
        *i += temp;
        if (*i > 9)
        {
            temp = *i / 10;
            *i = *i % 10;
        }
        else temp = 0;
    }
    *i += temp;
}

void mydiv(vector<int>& n1, vector<int>& n2)
{
    if (compare(n1, n2) == 2)
    {
        printf("0\n");
        write(n1);
        return;
    }
    int len1 = n1.size(), len2 = n2.size();
    vector<int> temp;
    vector<int> quotient;
    quotient.clear();
    for (int i = 0; i < len1 - len2 + 1; i++)
    {
        temp.assign(n1.begin() , n1.begin() + len2 );
        n1.erase(n1.begin() , n1.begin() + len2 );
        quotient.push_back(0);
        while (compare(temp, n2) == 1)
        {
            myminus(temp, n2, temp);
            *(quotient.end() - 1) += 1;
        }
        n1.insert(n1.begin(), temp.begin(), temp.end());
        if (n1.begin()  + 1 != n1.end()) {
            *(n1.begin()  + 1) += *(n1.begin()) * 10;
            *(n1.begin()) = 0;
            n1.erase(n1.begin());
        }
    }
    write(quotient);
    write(temp);
}

int main()
{
    vector<int> n1, n2, ans;
    read(n1);
    read(n2);
    myadd(n1, n2, ans);
    write(ans);
    if (compare(n1,n2)==2) printf("-");
    myminus(n1, n2, ans);
    write(ans);
    mymul(n1, n2,ans);
    write(ans);
    mydiv(n1, n2);
    return 0;
}
