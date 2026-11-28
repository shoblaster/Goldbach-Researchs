# Elementary facts about the covering model, h2(k) and M_k

Status: **PROVED (elementary), almost certainly known or folklore.** Nothing here proves H (h2(k) < p_k^2 - p_k for all k >= 3), Conjecture 4 or Goldbach's conjecture. Novelty is not claimed. Each fact is also checked by computer in `03_CODE/h2_mk_elementary_facts_check.py`.

## Setup
Let q_1 = 2, q_2 = 3, q_3 = 5, ... be the primes and k >= 1. A **choice** c picks one residue class c_2 mod 2 and a set c_q of exactly two classes mod each odd prime q <= p_k (classes may be 0). An integer n is **covered** by c if n mod q lies in c_q for some q <= p_k, and **survives** otherwise. For a window W = {a+1, ..., a+L} let s(c, W) be the number of survivors, and
M_k(L, a) = min over choices c of s(c, {a+1..a+L}).
The repository's quantity is M_k = M_k(p_k^2, 0).

**Definition used for h2.** We take h2(k) = 1 + max{ L : some choice covers {1..L} }. This matches the published table (OEIS A288815 / Ziller-Morack) for k = 1..4 by exhaustive search here (checked: 2, 6, 18, 30) and for k = 1..5 by an independent verifier; for k >= 3 the source states h2(k) = 6*A072753(k) + 6. We rely on that identification and do not re-derive it.

## Fact 1 (translation invariance)
M_k(L, a) does not depend on a. *Proof.* Map a choice c to c - a (subtract a from every class modulo each prime). This is a bijection on choices. n mod q is in c_q iff (n - a) mod q is in c_q - a, so n survives c iff n - a survives c - a. Hence survivors of c in {a+1..a+L} correspond one to one to survivors of c - a in {1..L}, and the minima agree. QED. (Checked exhaustively for k = 3, 4 and several shifts.)

Consequence: "the longest coverable window" does not depend on where the window starts, so h2(k) is also 1 + the longest coverable window anywhere.

## Fact 2 (superadditivity)
M_k(L1 + L2) >= M_k(L1) + M_k(L2). *Proof.* For any fixed choice c the survivors in a window split into those in its first L1 positions and its last L2 positions, so s(c) = s1(c) + s2(c) >= M_k(L1) + M_k(L2), using Fact 1 for the second part. Minimising over c preserves the inequality. QED.

## Fact 3 (a counting lower bound for M_k)
M_k(L) >= floor(L / h2(k)). *Proof.* No choice covers a window of length h2(k) (by definition of h2 and Fact 1), so M_k(h2(k)) >= 1. By Fact 2 applied floor(L/h2) times, M_k(L) >= floor(L/h2(k)) * 1. QED. (For k = 3..14 this gives 1, far below the computed M_k = 2, 2, 3, 2, 4, 4, 5, 10, 8, 13, 16, 14; checked.)

## Fact 4 (monotonicity in k)
h2(k) <= h2(k+1), and for fixed L, M_{k+1}(L) <= M_k(L). *Proof.* Take a choice for k that covers {1..L}; give it any two classes modulo p_{k+1}. Covered integers stay covered, so it still covers {1..L}. Hence the longest coverable window does not shrink, and survivors for k+1 are at most those for k. QED. (Checked on the table, k = 1..21.) Note this does not make M_k = M_k(p_k^2) monotone, because the window grows with k; the data are not monotone.

## Fact 5 (h2 dominates the classical Jacobsthal function)
h2(k) >= h(k), where h(k) = 1 + the length of the longest run of consecutive integers each divisible by some prime <= p_k. *Proof.* For such a run, for each prime pick the single class that covers the run elements it divides, and add an arbitrary second class for odd primes. This choice covers the run. QED. (Checked for k = 1..8: h = 2, 4, 6, 10, 14, 22, 26, 34 versus h2 = 2, 6, 18, 30, 66, 150, 192, 258.)

## Fact 6 (what H says in this language)
H (h2(k) < p_k^2 - p_k) is equivalent to M_k(p_k^2 - p_k - 1) >= 1: some integer must survive in every window of that length, whatever choice is made. The weaker statement h2(k) <= p_k^2 is equivalent to M_k >= 1. The computed values satisfy M_k >= 2 for k = 3..14 and h2(k) < p_k^2 - p_k for k = 3..21 (margins p_k^2 - p_k - h2(k) for k = 3..14: 2, 12, 44, 6, 80, 84, 140, 362, 360, 624, 746, 762; the tightest is k = 3 and k = 6).

## Limits
Facts 1 to 5 are bookkeeping about a covering problem. They do not bound h2(k) from above, which is where H lives. The best published unconditional upper bound for the classical function is Iwaniec's O((k log k)^2) with an unknown constant, and a standard dimension-2 sieve heuristically gives an exponent near 4.27 for the two-class problem, not 2 (the second figure is an inference by a literature screen, not a theorem). So H is open and out of reach of these methods.
