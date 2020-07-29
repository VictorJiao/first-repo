//Don't now
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int,int> pII;
inline char gc()
{
    static char now[1<<16],*S,*T;
    if(S==T) {T=(S=now)+fread(now,1,1<<16,stdin); if(S==T) return EOF;}
    return *S++;
}
inline int read()
{
    int x=0; char ch=gc();
    while(ch<'0'||'9'<ch) ch=gc();
    while('0'<=ch&&ch<='9') x=x*10+ch-'0',ch=gc();
    return x;
}
const int N=100+10;
int n,r[2][N];
vector<pII> tmp;
int m,head,nxt[N]; vector<int> rnk[N];
inline int cnt01(int x)
{
    if(x==101) return 2;
    return (r[0][x]>0)+(r[1][x]>0);
}
void show()
{
    for(int k=head;k;k=nxt[k])
    {
        printf("%5d ",rnk[k][0]);
        for(int i=1;i<rnk[k].size();i++)
            printf("%d%c",rnk[k][i],(i==rnk[k].size()-1)?'\n':' ');
    }
}
int main()
{
    freopen("bit.in","r",stdin);
    n=read();
    for(int i=1,t=1,t1=1;i<=n;i++)
    {
        while(true)
        {
            int x=0; char ch=gc();
            while(ch<'0'||'9'<ch) ch=gc();
            while('0'<=ch&&ch<='9') x=x*10+ch-'0',ch=gc();
            r[0][x]=t; t1++;
            if(ch=='\n'||ch==EOF) break;
        }
        t=t1;
    }
    n=read();
    for(int i=1,t=1,t1=1;i<=n;i++)
    {
        while(true)
        {
            int x=0; char ch=gc();
            while(ch<'0'||'9'<ch) ch=gc();
            while('0'<=ch&&ch<='9') x=x*10+ch-'0',ch=gc();
            r[1][x]=t; t1++;
            if(ch=='\n'||ch==EOF) break;
        }
        t=t1;
    }
    //for(int i=1;i<=100;i++) if(r[0][i]+r[1][i]) printf("Doc.%3d (%d,%d)\n",i,r[0][i],r[1][i]);
    for(int i=1;i<=100;i++) if(cnt01(i)==2) tmp.push_back(pII{r[0][i]+r[1][i],i});
    if(tmp.empty())
    {
        for(int i=1;i<=100;i++) if(cnt01(i)==1) tmp.push_back(pII{r[0][i]+r[1][i],i});
        sort(tmp.begin(),tmp.end());
        m=0,head=1;
        for(int i=0;i<tmp.size();i++)
        {
            int v=tmp[i].first,id=tmp[i].second;
            if(v!=tmp[i-1].first) nxt[m]=++m,rnk[m].push_back(v);
            rnk[m].push_back(id);
        }
        for(int k=head;k;k=nxt[k])
        for(int i=1;i<rnk[k].size();i++)
            printf("%d%c",rnk[k][i],(i==rnk[k].size()-1)?'\n':' ');
        return 0;
    }
    r[0][101]=r[1][101]=0; tmp.push_back(pII{r[0][101]+r[1][101],101});
    r[0][102]=r[1][102]=n; tmp.push_back(pII{r[0][102]+r[1][102],102});
    sort(tmp.begin(),tmp.end());
    m=1,head=1;
    rnk[m].push_back(tmp[0].first);
    rnk[m].push_back(tmp[0].second);
    for(int i=1;i<tmp.size();i++)
    {
        int v=tmp[i].first,id=tmp[i].second;
        if(v!=tmp[i-1].first) nxt[m]=m+1,m++,rnk[m].push_back(v);
        rnk[m].push_back(id);
    }
    for(int id=1;id<=100;id++)
    {
        if(cnt01(id)!=1) continue;
        int c=(r[1][id]>0);
        //使用规则2-1
        int rAno=0;
        for(int i=1;i<=100;i++)
        {
            if(cnt01(i)<2||r[c][i]!=r[c][id]) continue;
            if(!rAno) rAno=r[c^1][i];
            else if(rAno!=r[c^1][i]) {rAno=-1; break;}
        }
        if(rAno==-1) continue;
        if(rAno)
        {
            for(int k=head;k;k=nxt[k])
                if(rnk[k][0]==r[c][id]+rAno) {rnk[k].push_back(id); break;}
            continue;
        }
        //使用规则2-2
        int rPre=0,rNxt=n+n;
        for(int i=1;i<=100;i++)
        {
            if(cnt01(i)<2||r[c][i]==0) continue;
            if(r[c][i]<r[c][id]) rPre=max(rPre,r[0][i]+r[1][i]);
            if(r[c][i]>r[c][id]) rNxt=min(rNxt,r[0][i]+r[1][i]);
        }
        if(rPre>=rNxt) continue;
        for(int k=head;k;k=nxt[k])
        {
            if(rnk[k][0]!=rPre) continue;
            if(rnk[nxt[k]][0]<0)
            {
                while(rnk[nxt[k]][0]<0&&rnk[nxt[k]][0]>-r[c][id]) k=nxt[k];
                if(rnk[nxt[k]][0]==-r[c][id]) {rnk[nxt[k]].push_back(id); break;}
            }
            m++; nxt[m]=nxt[k],nxt[k]=m;
            rnk[m].push_back(-r[c][id]);
            rnk[m].push_back(id); break;
        }
        continue;
    }
    for(int k=nxt[head];nxt[k];k=nxt[k])
        for(int i=1;i<rnk[k].size();i++)
        {
            printf("%d",rnk[k][i]);
            if(i<rnk[k].size()-1) putchar(' ');
            else if(nxt[nxt[k]]) putchar('\n');
        }
    return 0;
}