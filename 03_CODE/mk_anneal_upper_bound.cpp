#include <bits/stdc++.h>
using namespace std;
int main(int argc,char**argv){
  int K=atoi(argv[1]); double secs=atof(argv[2]); unsigned seed=argc>3?atoi(argv[3]):1;
  vector<int>P; for(int n=2;(int)P.size()<K;n++){bool ok=1;for(int p:P)if(n%p==0)ok=0;if(ok)P.push_back(n);}
  int N=P.back()*P.back(); mt19937_64 rng(seed);
  vector<array<int,2>> c(K); vector<int> cov(N+1,0); int surv=N; int best=N; vector<array<int,2>> bc;
  auto apply=[&](int i,int cls,int d){int q=P[i];int st=cls==0?q:cls;for(int n=st;n<=N;n+=q){ if(d>0){if(cov[n]++==0)surv--;} else {if(--cov[n]==0)surv++;}}};
  auto start=chrono::steady_clock::now();
  while(chrono::duration<double>(chrono::steady_clock::now()-start).count()<secs){
    // restart
    fill(cov.begin(),cov.end(),0); surv=N;
    for(int i=0;i<K;i++){int q=P[i]; c[i][0]=rng()%q; if(q==2)c[i][1]=-1; else{do c[i][1]=rng()%q;while(c[i][1]==c[i][0]);}
      apply(i,c[i][0],1); if(q>2)apply(i,c[i][1],1);}
    double T0=3.0,T1=0.15; long iters=40000;
    for(long it=0;it<iters;it++){
      double T=T0*pow(T1/T0,(double)it/iters);
      int i=rng()%K,q=P[i]; int w=(q>2)?rng()%2:0; int nc;
      do nc=rng()%q; while(nc==c[i][0]||(q>2&&nc==c[i][1]));
      int old=c[i][w]; int before=surv;
      apply(i,old,-1); apply(i,nc,1);
      int d=surv-before;
      if(d<=0|| (double)(rng()%1000000)/1e6<exp(-d/T)) c[i][w]=nc; else {apply(i,nc,-1);apply(i,old,1);}
      if(surv<best){best=surv;bc=c;fprintf(stderr,"best %d\n",best);}
    }
  }
  // recompute directly
  vector<int> sv; for(int n=1;n<=N;n++){bool r=0;for(int i=0;i<K;i++){int m=n%P[i];if(m==bc[i][0]||m==bc[i][1])r=1;} if(!r)sv.push_back(n);}
  printf("k=%d best=%d direct=%zu classes:",K,best,sv.size());
  for(int i=0;i<K;i++){printf(" %d:{%d",P[i],bc[i][0]);if(P[i]>2)printf(",%d",bc[i][1]);printf("}");}
  printf("\nsurvivors:");for(int n:sv)printf(" %d",n);printf("\n");
}
