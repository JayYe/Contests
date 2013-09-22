#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
const double inf = 1e50;
const int N = 1010;
int vis[N];
double g[N][N];
double D[N];
int n;
int pre[N];
int head[N];
int nxt[N*2];
int pnt[N*2];
int E;
double s[N][N];
void add(int a,int b)
{   
     s[a][b] = s[b][a] = inf;//把树边去除,留下来的都是非树边
     pnt[E] = b;
     nxt[E] = head[a];
     head[a] = E++;
}
double tot_w;
void MST()
{
    for(int i = 0; i < n; i++) vis[i]=false,D[i]=inf,pre[i]=-1;
    D[0] = 0;
    for(int step = 0; step < n; step++) {
        int best = -1;
        for(int i = 0; i < n; i++) if(!vis[i])if(best==-1||D[i]<D[best]) best = i;
        vis[best] = true;
        tot_w += D[best];
        if(pre[best] != -1) add(pre[best],best), add(best,pre[best]);
        for(int i = 0; i < n; i++) if(!vis[i]) {
            if(g[best][i] < D[i]) 
                D[i] = g[best][i],pre[i]=best;
        }
    }
}
double x[N],y[N];   
double opt[N][N];
double dis(int i,int j) 
{
    return sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
}
bool in[N][N];
void dfs(int now,int u,int f)
{
     for(int i = head[u]; ~i; i = nxt[i]) if(pnt[i]-f){
         dfs(now,pnt[i],u);
         s[now][u] = std::min(s[now][u],s[now][pnt[i]]);
     }
}
int stk[N];
int top;
void go(int u,int f)
{
    int now = top;
    stk[++top] = u;
    for(int i = head[u]; ~i; i = nxt[i]) if(pnt[i]-f) {
        in[pnt[i]][u] = in[u][pnt[i]] = true;
        go(pnt[i],u);
    }
    if(f!=-1) {
        opt[u][f] = opt[f][u] = inf;
        for(int i = now+1; i <= top; i++) opt[u][f] = std::min(opt[u][f],s[stk[i]][f]);
        opt[f][u] = opt[u][f];
    }
}

double get_val()
{


    double  ret(0),sign(1);
    int flag=0;
    double tmp=0.1;
    char c;
    while((c=getchar())==' '||c=='\n'||c=='\r');
    if(c=='-')
        sign=-1;
    else
        ret=c-'0';
    while((c=getchar())!=' '&&c!='\n'&&c!='\r')
    {


        if(c=='.')
        {


            flag=1;
            continue;
        }
        if(!flag)
            ret=ret*10+c-'0';
        else 
        {


            ret+=(c-'0')*tmp;
            tmp*=0.1;
        }
    }
    return ret*sign;
}
void init(int k)
{
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            s[i][j] = s[j][i] = g[i][j] = g[j][i] = dis(i,j);
        }
    }
    tot_w = 0;
    E = 0;
    std::fill(head,head+n,-1)  ;
    MST();
    memset(in,false,sizeof(in));
    for(int i = 0; i < n; i++) dfs(i,i,-1);
    top = 0;
    go(0,-1);
    double ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) if(in[i][j]&&i&&j){
            ans = std::max(ans,opt[i][j]-g[i][j]) ;
        }
    }
    printf("%.2f\n",(tot_w+ans)*k);
}
int main()
{
    int t,k;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&k);
        for(int i = 0; i < n; i++) x[i]=get_val(),y[i]=get_val();//scanf("%lf%lf",&x[i],&y[i]);
        init(k);
    }
    return 0;
}
