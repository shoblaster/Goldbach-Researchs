# EXP027: position of the smaller prime in Goldbach pairs

Question: where in (0, n/2] does the smaller prime p of a Goldbach pair sit, and does that position follow the Hardy-Littlewood heuristic? This is a check of a standard heuristic, not a novelty claim.

Code: `03_CODE/pair_position_distribution.cpp`. Output: `bins.csv`, `RAW_OUTPUT.txt`.

Method: 25,000 pseudo-randomly chosen even n in [500000, 1000000] (mt19937, seed 1). For each n and each odd p <= n/2, the program adds 1 to the observed bin of x = p/n when p and n - p are both prime, and adds 1/(ln p * ln(n-p)) to the heuristic weight of the same bin. 50 bins on x in (0, 0.5].

Observed results (finite computation only):
- 120,500,304 pairs counted.
- observed / heuristic weight is flat across bins: mean 3.998, standard deviation 0.011, range 3.928 to 4.008. The lowest value is in the first bin (smallest p).
- The expected constant is 4 * C2 * mean(S) = 3.9995, where C2 = 0.66016 is the twin prime constant and mean(S) = 1/C2 is the average of the singular series over even n. The measured and expected constants agree to within 0.1%.

Meaning: after averaging over n, the position of p follows the weight 1/(ln p * ln q), as the Hardy-Littlewood heuristic predicts. The only structure in the position of p comes from this smooth weight and the local factors in n.

Method note (error caught and fixed): a first run used every 10th even n (a fixed step of 20). That makes every sampled n divisible by 5 and inflated the ratio by about 25% (4.99 instead of 4.00). The fix was random sampling. The faulty first output was not kept.

Not claimed: no theorem, no novelty. The gap distribution of Goldbach pairs follows from known two-point prime heuristics. The prior-art search for the exact statistic was not exhaustive (see the master log entry). Nothing above 10^6.
