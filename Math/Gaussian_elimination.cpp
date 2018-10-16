//高斯消元(浮点数)
#include<bits/stdc++.h>
using namespace std;
#define eps 1e-9
const int maxn=220;
double a[maxn][maxn],x[maxn];//方程的左边的矩阵和等式右边的值，求解之后x存的就是结果
int equ,var;//方程个数和未知数个数
//返回0表示无解，1表示有解
int Gauss()
{
    int i,j,k,col,max_r;
    for(k = 0,col = 0;k < equ && col < var;k++,col++)
    {
        max_r = k;
        for(i = k+1;i < equ;i++)
            if(fabs(a[i][col]) > fabs(a[max_r][col]))
                max_r = i;
        if(fabs(a[max_r][col]) < eps)return 0;
        if(k != max_r)
        {
            for(j = col;j < var;j++)
                swap(a[k][j],a[max_r][j]);
            swap(x[k],x[max_r]);
        }
        x[k]/=a[k][col];
        for(j = col+1;j < var;j++)a[k][j]/=a[k][col];
        a[k][col] = 1;
        for(int i = 0;i < equ;i++)
            if(i != k)
            {
                x[i] -=  x[k]*a[i][k];
                for(j = col+1;j < var;j++)a[i][j] -= a[k][j]*a[i][col];
                a[i][col] = 0;
            }
    }
    return 1;
}
//3.8x+4.2y=5
//2.7x+5y=7
int main()
{
    a[0][0]=3.8;
    a[0][1]=4.2;
    a[1][0]=2.7;
    a[1][1]=5;
    equ=2;
    var=2;
    x[0]=5;
    x[1]=7;
    if(Gauss()==1)
        cout<<x[0]<<’ ’≪x[1]≪endl;
}
/******************************************************/
//高斯消元法求方程组的解
//一类开关问题，对2取模的01方程组
//poj 1681 需要枚举自由变元，找解中1个数最少的
#include<iostream>
#include<algorithm>
#include<cstring>
#include<stdio.h>
using namespace std;
const int maxn=300;
//有equ个方程，var个变元。增广矩阵行数为equ，从0到equ-1;列数为var+1,从0到var
int equ,var;
int a[maxn][maxn];//增广矩阵
int x[maxn];//解集
int free_x[maxn];//用来存储自由变元(多解枚举自由变元可以使用)
int free_num;//自由变元的个数
//返回值为-1表示无解，为0是唯一解，否则返回自由变元的个数
int Gauss()
{
    int max_r,col,k;
    free_num=0;
    for(k=0,col=0;k<equ&&col<var;k++,col++)
    {
        max_r=k;
        for(int i=k+1;i<equ;i++)
        {
            if(abs(a[i][col])>abs(a[max_r][col]))
                max_r=i;
        }
        if(a[max_r][col]==0)
        {
            k--;
            free_x[free_num++]=col;
            continue;
        }
        if(max_r!=k)
            for(int j=col;j<var+1;j++)
                swap(a[k][j],a[max_r][j]);
        for(int i=k+1;i<equ;i++)
        {
            if(a[i][col]!=0)
            {
                for(int j=col;j<var+1;j++)
                    a[i][j]^=a[k][j];
            }
        }
    }
    for(int i=k;i<equ;i++)
        if(a[i][col]!=0)
            return -1;
    if(k<var)return var-k;
    for(int i=var-1;i>=0;i--)
    {
        x[i]=a[i][var];
        for(int j=i+1;j<var;j++)
            x[i]^=(a[i][j]&&x[j]);
    }
    return 0;
}
int n;
void init()
{
    memset(a,0,sizeof(a));
    memset(x,0,sizeof(x));
    equ=n*n;
    var=n*n;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
    {
        int t=i*n+j;
        a[t][t]=1;
        if(i>0)a[(i-1)*n+j][t]=1;
        if(i<n-1)a[(i+1)*n+j][t]=1;
        if(j>0)a[i*n+j-1][t]=1;
        if(j<n-1)a[i*n+j+1][t]=1;
    }
}
void solve()
{
    int t=Gauss();
    if(t==-1)
        puts("inf");
    else if(t==0)
    {
        int ans=0;
        for(int i=0;i<n*n;i++)
            ans+=x[i];
        printf("%d\n",ans);
    }
    else
    {
        int ans=0x3f3f3f3f;
        int tot=(1<<t);
        for(int i=0;i<tot;i++)//枚举自由元
        {
            int cnt=0;
            for(int j=0;j<t;j++)
            {
                if(i&(1<<j))
                {
                     x[free_x[j]]=1;
                     cnt++;
                }
                else x[free_x[j]]=0;
            }
            for(int j=var-t-1;j>=0;j--)//自由变元放在最后var-t到var-1行，下面自由元已经枚举完后再计算上面的。
            {                          //写法比较奇怪，必须这样写。
                int idx;
                for(idx=j;idx<var;idx++)
                    if(a[j][idx])
                        break;
                x[idx]=a[j][var];
                for(int l=idx+1;l<var;l++)
                    if(a[j][l])
                        x[idx]^=x[l];
                cnt+=x[idx];
            }
            ans=min(ans,cnt);
        }
        printf("%d\n",ans);
    }
}
char str[30][30];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        init();
        for(int i=0;i<n;i++)
        {
            scanf("%s",str[i]);
            for(int j=0;j<n;j++)
            {
                if(str[i][j]=='y')
                    a[i*n+j][n*n]=0;
                else
                    a[i*n+j][n*n]=1;
            }
        }
        solve();
    }
    return 0;
}
/**************************************************/
//解同余方程组
//poj 2947 
//求解对mod取模的方程组

#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstring>
using namespace std;
const int mod=7;
const int maxn=400;
int a[maxn][maxn];
int x[maxn];//解集
inline int gcd(int a,int b)
{
    while(b!=0)
    {
        int t=b;
        b=a%b;
        a=t;
    }
    return a;
}
inline int lcm(int a,int b)
{
    return a/gcd(a,b)*b;
}
long long inv(long long a,long long m)
{
    if(a==1)return 1;
    return inv(m%a,m)*(m-m/a)%m;
}
int Gauss(int equ,int var)
{
    int max_r,col,k;
    for(k=0,col=0;k<equ&&col<var;k++,col++)
    {
        max_r=k;
        for(int i=k+1;i<equ;i++)
            if(abs(a[i][col])>abs(a[max_r][col]))
                max_r=i;
        if(a[max_r][col]==0)
        {
            k--;
            continue;
        }
        if(max_r!=k)
            for(int j=col;j<var+1;j++)
                swap(a[k][j],a[max_r][j]);
        for(int i=k+1;i<equ;i++)
        {
            if(a[i][col]!=0)
            {
                int LCM=lcm(abs(a[i][col]),abs(a[k][col]));
                int ta=LCM/abs(a[i][col]);
                int tb=LCM/abs(a[k][col]);
                if(a[i][col]*a[k][col]<0)tb=-tb;
                for(int j=col;j<var+1;j++)
                    a[i][j]=((a[i][j]*ta-a[k][j]*tb)%mod+mod)%mod;
            }
        }
    }
    for(int i=k;i<equ;i++)
        if(a[i][col]!=0)
            return -1;//无解
    if(k<var)return var-k;//多解
    for(int i=var-1;i>=0;i--)
    {
        int temp=a[i][var];
        for(int j=i+1;j<var;j++)
        {
            if(a[i][j]!=0)
            {
                temp-=a[i][j]*x[j];
                temp=(temp%mod+mod)%mod;
            }
        }
        x[i]=(temp*inv(a[i][i],mod))%mod;
    }
    return 0;
}
int change(char s[])
{
    if(s[0]=='M')return 1;
    if(s[0]=='T'&&s[1]=='U')return 2;
    if(s[0]=='W')return 3;
    if(s[0]=='T')return 4;
    if(s[0]=='F')return 5;
    if(s[0]=='S'&&s[1]=='A')return 6;
    return 7;
}
int main()
{
    int n,m;
    while(~scanf("%d %d",&n,&m))
    {
        if(n==0&&m==0)break;
        memset(a,0,sizeof(a));
        char str1[10],str2[10];
        int k;
        for(int i=0;i<m;i++)
        {
            scanf("%d%s%s",&k,str1,str2);
            //cout<<((change(str2)-change(str1)+1)%mod+mod)%mod<<endl;
            a[i][n]=((change(str2)-change(str1)+1)%mod+mod)%mod;
            int t;
            while(k--)
            {
                scanf("%d",&t);
                t--;
                a[i][t]++;
                a[i][t]%=mod;
            }
        }
        int ans=Gauss(m,n);

        if(ans==0)
        {
            for(int i=0;i<n;i++)
                if(x[i]<=2)
                    x[i]+=7;
            for(int i=0;i<n-1;i++)printf("%d ",x[i]);
            printf("%d\n",x[n-1]);
        }
        else if(ans==-1)printf("Inconsistent data.\n");
        else puts("Multiple solutions.");
    }
    return 0;
}
/***********************************************************/
//解一般方程
#include<stdio.h>
#include<algorithm>
#include<iostream>
#include<string.h>
#include<math.h>
using namespace std;
const int MAXN=50;
int a[MAXN][MAXN];//增广矩阵
int x[MAXN];//解集
bool free_x[MAXN];//标记是否是不确定的变元
inline int gcd(int a,int b)
{
    int t;
    while(b!=0)
    {
        t=b;
        b=a%b;
        a=t;
    }
    return a;
}
inline int lcm(int a,int b)
{
    return a/gcd(a,b)*b;//先除后乘防溢出
}
// 高斯消元法解方程组(Gauss-Jordan elimination).(-2表示有浮点数解，但无整数解，
//-1表示无解，0表示唯一解，大于0表示无穷解，并返回自由变元的个数)
//有equ个方程，var个变元。增广矩阵行数为equ,分别为0到equ-1,列数为var+1,分别为0到var.
int Gauss(int equ,int var)
{
    int i,j,k;
    int max_r;// 当前这列绝对值最大的行.
    int col;//当前处理的列
    int ta,tb;
    int LCM;
    int temp;
    int free_x_num;
    int free_index;
    for(int i=0;i<=var;i++)
    {
        x[i]=0;
        free_x[i]=true;
    }
    //转换为阶梯阵.
    col=0; // 当前处理的列
    for(k = 0;k < equ && col < var;k++,col++)
    {// 枚举当前处理的行.
// 找到该col列元素绝对值最大的那行与第k行交换.(为了在除法时减小误差)
        max_r=k;
        for(i=k+1;i<equ;i++)
        {
            if(abs(a[i][col])>abs(a[max_r][col])) max_r=i;
        }
        if(max_r!=k)
        {// 与第k行交换.
            for(j=k;j<var+1;j++) swap(a[k][j],a[max_r][j]);
        }
        if(a[k][col]==0)
        {// 说明该col列第k行以下全是0了，则处理当前行的下一列.
            k--;
            continue;
        }
        for(i=k+1;i<equ;i++)
        {// 枚举要删去的行.
            if(a[i][col]!=0)
            {
                LCM = lcm(abs(a[i][col]),abs(a[k][col]));
                ta = LCM/abs(a[i][col]);
                tb = LCM/abs(a[k][col]);
                if(a[i][col]*a[k][col]<0)tb=-tb;//异号的情况是相加
                for(j=col;j<var+1;j++)
                {
                    a[i][j] = a[i][j]*ta-a[k][j]*tb;
                }
            }
        }
    }
  //  Debug();
    // 1. 无解的情况: 化简的增广阵中存在(0, 0, ..., a)这样的行(a != 0).
    for (i = k; i < equ; i++)
    { // 对于无穷解来说，如果要判断哪些是自由变元，那么初等行变换中的交换就会影响，则要记录交换.
        if (a[i][col] != 0) return -1;
    }
    // 2. 无穷解的情况: 在var * (var + 1)的增广阵中出现(0, 0, ..., 0)这样的行，即说明没有形成严格的上三角阵.
    // 且出现的行数即为自由变元的个数.
    if (k < var)
    {
        // 首先，自由变元有var - k个，即不确定的变元至少有var - k个.
        for (i = k - 1; i >= 0; i--)
        {
            // 第i行一定不会是(0, 0, ..., 0)的情况，因为这样的行是在第k行到第equ行.
            // 同样，第i行一定不会是(0, 0, ..., a), a != 0的情况，这样的无解的.
            free_x_num = 0; // 用于判断该行中的不确定的变元的个数，如果超过1个，则无法求解，它们仍然为不确定的变元.
            for (j = 0; j < var; j++)
            {
                if (a[i][j] != 0 && free_x[j]) free_x_num++, free_index = j;
            }
            if (free_x_num > 1) continue; // 无法求解出确定的变元.
            // 说明就只有一个不确定的变元free_index，那么可以求解出该变元，且该变元是确定的.
            temp = a[i][var];
            for (j = 0; j < var; j++)
            {
                if (a[i][j] != 0 && j != free_index) temp -= a[i][j] * x[j];
            }
            x[free_index] = temp / a[i][free_index]; // 求出该变元.
            free_x[free_index] = 0; // 该变元是确定的.
        }
        return var - k; // 自由变元有var - k个.
    }
    // 3. 唯一解的情况: 在var * (var + 1)的增广阵中形成严格的上三角阵.
    // 计算出Xn-1, Xn-2 ... X0.
    for (i = var - 1; i >= 0; i--)
    {
        temp = a[i][var];
        for (j = i + 1; j < var; j++)
        {
            if (a[i][j] != 0) temp -= a[i][j] * x[j];
        }
        if (temp % a[i][i] != 0) return -2; // 说明有浮点数解，但无整数解.
        x[i] = temp / a[i][i];
    }
    return 0;
}
int main(void)
{
    int i, j;
    int equ,var;
    while (scanf("%d %d", &equ, &var) != EOF)
    {
        memset(a, 0, sizeof(a));
        for (i = 0; i < equ; i++)
        {
            for (j = 0; j < var + 1; j++)
            {
                scanf("%d", &a[i][j]);
            }
        }
//        Debug();
        int free_num = Gauss(equ,var);
        if (free_num == -1) printf("无解!\n");
   else if (free_num == -2) printf("有浮点数解，无整数解!\n");
        else if (free_num > 0)
        {
            printf("无穷多解! 自由变元个数为%d\n", free_num);
            for (i = 0; i < var; i++)
            {
                if (free_x[i]) printf("x%d 是不确定的\n", i + 1);
                else printf("x%d: %d\n", i + 1, x[i]);
            }
        }
        else
        {
            for (i = 0; i < var; i++)
            {
                printf("x%d: %d\n", i + 1, x[i]);
            }
        }
        printf("\n");
    }
    return 0;
}
