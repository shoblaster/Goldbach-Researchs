// Bound-free exhaustive computation of omega2(k) for small k (no pruning, no bound, no solver).
// omega2(k) = max over all choices of two nonzero residues mod each prime p in {5..p_k} of the length of the covered
// prefix 1..L (position q is covered by p iff q%p is a chosen residue != 0). Enumerates every choice: prod C(p-1,2) leaves.
// Positions use bits 0..63 (valid while omega2 < 64, i.e. k <= 9). Build: g++ -std=c++17 -O3 -march=native -fopenmp h2_bruteforce_omega2.cpp -o h2_bf
// Run: ./h2_bf K   -> prints omega2 and the number of leaves enumerated (must equal prod C(p-1,2)).
#include <bits/stdc++.h>
#include <omp.h>
using namespace std; typedef unsigned long long u64; typedef unsigned __int128 u128;
static vector<int> P; static vector<vector<u64>> PM;   // PM[i] = union masks of all residue pairs for prime P[i]
static int NP;
static void rec(int i,u64 m,int&best,u64&leaves){
  if(i==NP){ int w=__builtin_ctzll(~m); if(w>best)best=w; leaves++; return; }
  for(u64 x:PM[i]) rec(i+1,m|x,best,leaves);
}
int main(int argc,char**argv){
  int K=atoi(argv[1]); int all[]={2,3,5,7,11,13,17,19,23,29};
  if(K<3||K>9){fprintf(stderr,"K must be 3..9\n");return 2;}
  for(int i=2;i<K;i++)P.push_back(all[i]); NP=P.size();
  for(int p:P){ vector<u64> cl(p,0); for(int n=1;n<=64;n++) if(n%p) cl[n%p]|=1ULL<<(n-1);
    vector<u64> v; for(int a=1;a<p;a++)for(int b=a+1;b<p;b++) v.push_back(cl[a]|cl[b]); PM.push_back(v);}
  // parallelise over the first prime's pairs
  int best=0; u64 leaves=0; auto&first=PM[0];
  #pragma omp parallel for schedule(dynamic,1) reduction(+:leaves) reduction(max:best)
  for(size_t t=0;t<first.size();t++){ int b=0; u64 lv=0; rec(1,first[t],b,lv); if(b>best)best=b; leaves+=lv; }
  u64 expect=1; for(int p:P) expect*= (u64)(p-1)*(p-2)/2;
  printf("k %d omega2 %d h2 %d leaves %llu expected %llu %s\n",K,best,6*best+6,leaves,expect,leaves==expect?"OK":"MISMATCH");
}
