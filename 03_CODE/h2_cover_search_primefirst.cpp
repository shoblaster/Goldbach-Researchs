// Second, structurally different exact search for the paired-Jacobsthal covering problem (same model as h2_cover_search.cpp).
// Method B ("prime-first"): process the primes in DESCENDING order; at each prime enumerate the PAIR of nonzero residues
// (r1,r2), r1<r2, sorted by current gain, with a tight sum-of-best-gains bound on the primes still to come.
// It branches on primes, not on the lowest uncovered position, so it does not share the tree of method A.
// Build: g++ -std=c++17 -O3 -march=native h2_cover_search_primefirst.cpp -o h2_pf   Run: ./h2_pf K L
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
static const int NW = 4;
struct M { u64 w[NW]; };
static int K, L, NP, NWU; static vector<int> P; static vector<vector<M>> cls; static long long nodes = 0;
static vector<array<int,2>> pick;
static inline int pcm(const M& a){int c=0;for(int i=0;i<NWU;i++)c+=__builtin_popcountll(a.w[i]);return c;}
static inline int pcand(const M& a,const M& b){int c=0;for(int i=0;i<NWU;i++)c+=__builtin_popcountll(a.w[i]&b.w[i]);return c;}
static int top2(int i,const M& unc){int b1=0,b2=0;for(int r=1;r<P[i];r++){int g=pcand(unc,cls[i][r]);if(g>b1){b2=b1;b1=g;}else if(g>b2)b2=g;}return b1+b2;}
static bool dfs(int idx,const M& unc){
  nodes++; int total=pcm(unc);
  if(!total) return true;
  if(idx==NP) return false;
  int rest=0; for(int i=idx+1;i<NP;i++) rest+=top2(i,unc);
  int p=P[idx]; vector<pair<int,int>> g; for(int r=1;r<p;r++) g.push_back({pcand(unc,cls[idx][r]),r});
  sort(g.begin(),g.end(),[](auto&a,auto&b){return a.first>b.first;});
  if(g[0].first+(g.size()>1?g[1].first:0)+rest<total) return false;
  for(size_t a=0;a<g.size();a++){
    if(2*g[a].first+rest<total) break;
    for(size_t b=a+1;b<g.size();b++){
      if(g[a].first+g[b].first+rest<total) break;
      M nu; for(int j=0;j<NWU;j++) nu.w[j]=unc.w[j]&~(cls[idx][g[a].second].w[j]|cls[idx][g[b].second].w[j]);
      pick[idx]={g[a].second,g[b].second};
      if(dfs(idx+1,nu)) return true;
    }
  }
  return false;
}
int main(int argc,char**argv){
  K=atoi(argv[1]);L=atoi(argv[2]);
  int all[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73};
  if(K<3||K>21){fprintf(stderr,"K must be in 3..21\n");return 2;}
  for(int i=K-1;i>=2;i--) P.push_back(all[i]);            // descending
  NP=P.size();NWU=(L+63)/64;cls.resize(NP);pick.assign(NP,{0,0});
  for(int i=0;i<NP;i++){cls[i].assign(P[i],M());for(int r=0;r<P[i];r++)for(int j=0;j<NW;j++)cls[i][r].w[j]=0;
    for(int n=1;n<=L;n++) if(n%P[i]) cls[i][n%P[i]].w[(n-1)>>6]|=1ULL<<((n-1)&63);}
  M unc;for(int j=0;j<NW;j++)unc.w[j]=0;for(int n=1;n<=L;n++)unc.w[(n-1)>>6]|=1ULL<<((n-1)&63);
  bool ok=dfs(0,unc);
  bool direct=false;
  if(ok){direct=true;for(int q=1;q<=L&&direct;q++){bool c=false;for(int i=0;i<NP;i++){int r=q%P[i];if(r&&(r==pick[i][0]||r==pick[i][1]))c=true;}direct=c;}}
  printf("method B k %d L %d %s nodes %lld witness_direct_check %s\n",K,L,ok?"FEASIBLE":"INFEASIBLE",nodes,ok?(direct?"True":"False"):"n/a");
}
