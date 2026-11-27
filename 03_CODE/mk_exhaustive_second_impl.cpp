// exhaustive search: is there a choice leaving <=B survivors? dynamic prime ordering, pair-viability pruning
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
int K,B,N,W; vector<int> P;
vector<vector<vector<u64>>> M; // M[qi][r][w]
long long nodes=0; bool found=false; vector<pair<int,int>> choice; // (q,r1,r2) record
vector<array<int,3>> sol;
struct Node{};
int pc(const vector<u64>&a){int s=0;for(u64 x:a)s+=__builtin_popcountll(x);return s;}
void dfs(const vector<u64>&S,int sz,u64 rem,vector<array<int,3>>&cur){
  if(found)return; nodes++;
  if(rem==0){ if(sz<=B){found=true;sol=cur;} return;}
  int nq=P.size();
  static thread_local int dummy;
  // counts
  vector<vector<int>> c(nq);
  int T=0; vector<int> t(nq,0);
  for(int qi=0;qi<nq;qi++) if(rem>>qi&1){
    int q=P[qi]; c[qi].assign(q,0);
    for(int r=0;r<q;r++){int s=0;for(int w=0;w<W;w++)s+=__builtin_popcountll(S[w]&M[qi][r][w]);c[qi][r]=s;}
    vector<int> d=c[qi]; sort(d.rbegin(),d.rend());
    t[qi]= q==2? d[0] : d[0]+d[1]; T+=t[qi];
  }
  if(sz-T>B)return;
  int best=-1; long long bv=1e18;
  for(int qi=0;qi<nq;qi++) if(rem>>qi&1){
    int q=P[qi]; int thr=sz-B-(T-t[qi]); long long cnt=0;
    if(q==2){ for(int r=0;r<2;r++) if(c[qi][r]>=thr)cnt++; }
    else for(int a=0;a<q;a++)for(int b=a+1;b<q;b++) if(c[qi][a]+c[qi][b]>=thr)cnt++;
    if(cnt==0)return;
    if(cnt<bv){bv=cnt;best=qi;}
  }
  int qi=best,q=P[qi]; int thr=sz-B-(T-t[qi]);
  vector<array<int,3>> cand;
  if(q==2){for(int r=0;r<2;r++) if(c[qi][r]>=thr)cand.push_back({c[qi][r],r,-1});}
  else for(int a=0;a<q;a++)for(int b=a+1;b<q;b++) if(c[qi][a]+c[qi][b]>=thr)cand.push_back({c[qi][a]+c[qi][b],a,b});
  sort(cand.rbegin(),cand.rend());
  for(auto&cd:cand){
    vector<u64> S2(S);
    for(int w=0;w<W;w++){S2[w]&=~M[qi][cd[1]][w]; if(cd[2]>=0)S2[w]&=~M[qi][cd[2]][w];}
    cur.push_back({q,cd[1],cd[2]});
    dfs(S2,sz-cd[0],rem&~(1ULL<<qi),cur);
    cur.pop_back(); if(found)return;
  }
}
int main(int argc,char**argv){
  K=atoi(argv[1]);B=atoi(argv[2]);
  for(int p=2;(int)P.size()<K;p++){bool ok=1;for(int d=2;d*d<=p;d++)if(p%d==0)ok=0;if(ok)P.push_back(p);}
  N=P.back()*P.back();W=(N+1+63)/64;
  M.resize(K);
  for(int qi=0;qi<K;qi++){int q=P[qi];M[qi].assign(q,vector<u64>(W,0));for(int n=1;n<=N;n++)M[qi][n%q][n>>6]|=1ULL<<(n&63);}
  vector<u64> S(W,0);for(int n=1;n<=N;n++)S[n>>6]|=1ULL<<(n&63);
  // root: prime 3 with reflection symmetry n->N+1-n : class r -> (N+1-r) mod 3; keep canonical pairs only
  int qi3=1; // P[1]==3
  auto refl=[&](int r){return ((N+1-r)%3+3)%3;};
  u64 rem=((1ULL<<K)-1)&~(1ULL<<qi3);
  for(int a=0;a<3&&!found;a++)for(int b=a+1;b<3&&!found;b++){
    int ra=refl(a),rb=refl(b); if(ra>rb)swap(ra,rb);
    if(make_pair(ra,rb)<make_pair(a,b))continue; // non-canonical
    vector<u64> S2(S);for(int w=0;w<W;w++)S2[w]&=~M[qi3][a][w]&~M[qi3][b][w];
    vector<array<int,3>> cur={{3,a,b}};
    dfs(S2,pc(S2),rem,cur);
  }
  printf("k=%d B=%d N=%d : %s nodes=%lld\n",K,B,N,found?"FOUND":"NONE",nodes);
  if(found){int sv=0;for(auto&s:sol)printf(" q%d:{%d,%d}",s[0],s[1],s[2]);puts("");}
}
