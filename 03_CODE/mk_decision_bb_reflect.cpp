// bb4: faster decision B&B. Same bound as bb3, static buffers, reflection symmetry (n -> N+1-n, preserves window) at root only.
// usage: bb4 K B [lo hi]   (root option index range, for chunking). env NOSYM=1 disables reflection. prints per-root-option result.
#include <bits/stdc++.h>
using namespace std;
int K,N,B; vector<int> P; long long nodes; bool found;
int chq[32][2]; 
static int buf[32][2048]; static int cntb[32][64];
int depthDone[32]; // unused
bool doneP[32];
int rootLo=0,rootHi=1<<30,rootIdx; bool useSym=true; int rootPrime;
int bestSz;
bool rec(int d,int s){
    nodes++;
    int*S=buf[d];
    int bi=-1,bsum=-1,total=0; int top[32]; int any=0;
    for(int i=0;i<K;i++) if(!doneP[i]){
        any=1; int q=P[i]; int*c=cntb[i]; // reuse per-prime array; recomputed at each node (we only need current node's)
        for(int r=0;r<q;r++)c[r]=0;
        for(int j=0;j<s;j++)c[S[j]%q]++;
        int m1=0,m2=0; for(int r=0;r<q;r++){int v=c[r]; if(v>m1){m2=m1;m1=v;} else if(v>m2)m2=v;}
        top[i]=(q==2)?m1:m1+m2; total+=top[i];
        if(top[i]>bsum){bsum=top[i];bi=i;}
    }
    if(s<=B){found=true; bestSz=s; return true;}
    if(!any) return false;
    if(s-total>B) return false;
    int i=bi,q=P[i]; int rest=total-top[i]; int need=s-rest-B;
    // copy counts since deeper recursion overwrites cntb
    int c[64]; for(int r=0;r<q;r++)c[r]=cntb[i][r];
    vector<array<int,3>> opts;
    if(q==2){ for(int r=0;r<2;r++) if(c[r]>=need) opts.push_back({c[r],r,-1}); }
    else for(int a=0;a<q;a++)for(int b=a+1;b<q;b++) if(c[a]+c[b]>=need) opts.push_back({c[a]+c[b],a,b});
    sort(opts.begin(),opts.end(),[](const array<int,3>&x,const array<int,3>&y){ if(x[0]!=y[0])return x[0]>y[0]; if(x[1]!=y[1])return x[1]<y[1]; return x[2]<y[2];});
    doneP[i]=1;
    bool res=false; int oi=0;
    for(auto&o:opts){
        if(d==0){ int idx=oi++; if(idx<rootLo||idx>=rootHi) continue; rootIdx=idx;
            if(useSym){ // canonical under reflection n->N+1-n
                int a=((N+1-o[1])%q+q)%q, b=(q==2)?-1:((N+1-o[2])%q+q)%q; if(q>2&&a>b)swap(a,b);
                if(make_pair(a,b)<make_pair(o[1],o[2])) continue; }
        }
        chq[i][0]=o[1];chq[i][1]=o[2];
        int*T=buf[d+1]; int t=0; for(int j=0;j<s;j++){int r=S[j]%q; if(r!=o[1]&&r!=o[2])T[t++]=S[j];}
        if(rec(d+1,t)){res=true;break;}
        if(d==0){ fprintf(stderr,"root opt %d/%zu done nodes=%lld\n",rootIdx,opts.size(),nodes); }
    }
    doneP[i]=0; return res;
}
int main(int argc,char**argv){
    K=atoi(argv[1]); B=atoi(argv[2]); if(argc>4){rootLo=atoi(argv[3]);rootHi=atoi(argv[4]);} if(getenv("NOSYM"))useSym=false;
    for(int n=2;(int)P.size()<K;n++){bool ok=1;for(int p:P)if(n%p==0)ok=0;if(ok)P.push_back(n);}
    N=P.back()*P.back();
    for(int j=0;j<N;j++)buf[0][j]=j+1;
    memset(doneP,0,sizeof doneP); nodes=0;found=false;
    auto t0=chrono::steady_clock::now();
    bool r=rec(0,N);
    double dt=chrono::duration<double>(chrono::steady_clock::now()-t0).count();
    printf("k=%d B=%d range=[%d,%d) feasible=%d nodes=%lld time=%.1fs\n",K,B,rootLo,rootHi,(int)r,nodes,dt);
    if(r){ // witness: fill unchosen primes by exhaustive? just report; chq valid for chosen primes only
        printf("partial witness (chosen primes only), survivors<=B at leaf=%d\n",bestSz);
    }
}
