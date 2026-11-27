#include <bits/stdc++.h>
using namespace std;
int K; vector<int> P; int B; long long nodes; bool found; vector<array<int,2>> ch; vector<int> bestS;
// decide: exists choice with survivors <= B
void rec(const vector<int>&S, vector<char>&done){
    nodes++;
    int s=S.size();
    // compute counts for each remaining prime
    int bi=-1,bsum=-1,total=0; vector<vector<int>> cnt(K);
    vector<int> top(K,0);
    bool any=false;
    for(int i=0;i<K;i++) if(!done[i]){
        any=true; int q=P[i]; cnt[i].assign(q,0);
        for(int n:S) cnt[i][n%q]++;
        int m1=0,m2=0; for(int c:cnt[i]){ if(c>m1){m2=m1;m1=c;} else if(c>m2)m2=c;}
        top[i]= (q==2)? m1 : m1+m2; total+=top[i];
        if(top[i]>bsum){bsum=top[i];bi=i;}
    }
    if(!any){ if(s<=B){found=true;bestS=S;} return; }
    if(s-total>B) return;
    if(s<=B){ found=true; bestS=S; /* remaining arbitrary: fill later */
        // fill arbitrary classes
        for(int i=0;i<K;i++) if(!done[i]){ch[i]={0,(P[i]==2?0:1)};}
        return; }
    int i=bi,q=P[i]; int rest=total-top[i];
    int need=s-rest-B; // gain needed >= need
    vector<array<int,3>> opts;
    if(q==2){ for(int r=0;r<2;r++) if(cnt[i][r]>=need) opts.push_back({cnt[i][r],r,-1}); }
    else for(int a=0;a<q;a++)for(int b=a+1;b<q;b++) if(cnt[i][a]+cnt[i][b]>=need) opts.push_back({cnt[i][a]+cnt[i][b],a,b});
    sort(opts.begin(),opts.end(),[](auto&x,auto&y){return x[0]>y[0];});
    done[i]=1;
    for(auto&o:opts){
        ch[i]={o[1],o[2]};
        vector<int> T; T.reserve(s);
        for(int n:S){int r=n%q; if(r!=o[1]&&r!=o[2])T.push_back(n);}
        rec(T,done);
        if(found){ done[i]=0; return; }
    }
    done[i]=0;
}
int main(int argc,char**argv){
    K=atoi(argv[1]);
    for(int n=2;(int)P.size()<K;n++){bool ok=1;for(int p:P)if(n%p==0)ok=0;if(ok)P.push_back(n);}
    int p=P.back(),N=p*p; ch.assign(K,{-1,-1});
    for(B=(getenv("B0")?atoi(getenv("B0")):0);;B++){
        nodes=0;found=false; vector<int> S(N); iota(S.begin(),S.end(),1); vector<char> done(K,0);
        auto t0=chrono::steady_clock::now();
        rec(S,done);
        double dt=chrono::duration<double>(chrono::steady_clock::now()-t0).count();
        printf("k=%d B=%d feasible=%d nodes=%lld time=%.1fs\n",K,B,(int)found,nodes,dt);fflush(stdout);
        if(found){
            // verify directly
            vector<int> sv; for(int n=1;n<=N;n++){bool rem=0;for(int i=0;i<K;i++){int r=n%P[i]; if(r==ch[i][0]||r==ch[i][1])rem=1;} if(!rem)sv.push_back(n);}
            printf("M_%d=%d (proved: B=%d infeasible for all smaller) classes:",K,(int)sv.size(),B);
            for(int i=0;i<K;i++){printf(" %d:{%d",P[i],ch[i][0]); if(P[i]>2)printf(",%d",ch[i][1]); printf("}");}
            printf("\nsurvivors:");for(int n:sv)printf(" %d",n);printf("\n");break;
        }
    }
}
