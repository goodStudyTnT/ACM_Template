//inplace_merge(first,mid,last,compare)归并排序
注意:[first,mid]和[mid,last)都要呈升序和降序
例子
//找出所有区间和小于t的区间个数
//cf#510D

#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
long long a[maxn];
long long ans;
long long t;
void solve(int l,int r)
{
    if(r-l<=1)return;
    int m=l+r>>1;
    solve(l,m);
    solve(m,r);
    int j=m;
    for(int i=l;i<m;i++)
    {
        while(j<r&&a[j]-a[i]<t)j++;
        ans+=0LL+j-m;
    }
    inplace_merge(a+l,a+m,a+r);
}
int main()
{
    int n;
    scanf("%d %lld",&n,&t);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]),a[i]+=a[i-1];
    solve(0,n+1);
    printf("%lld\n",ans);
    return 0;
}
/*****************************************/
Vector assign(n,m)将n个m放进vector里面
/*****************************************/
//枚举子集
枚举i的非空子集j 
for(int j=i;j;j=(j-1)&i)
求1的个数
cout<<__builtin_popcount(i)<<endl;
求前缀0的个数
cout<<__builtin_clz(i)<<endl;
求后缀0的个数
cout<<__builtin_ctz(i)<<endl;
