
?
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
78
79
80
81
82
83
84
85
86
87
88
89
90
91
92
93
94
95
96
	
#include <bits/stdc++.h>
using namespace std;
using ull = unsigned int;  // 64bit unsigned integer
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int N, M, A, B;
    cin >> N >> M >> A >> B;
 
    vector<ull> adj(N, 0);
    vector<char> deg(N, 0);
 
    // Načtení hran
    for (int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;
        --u; --v;
        adj[u] |= (1ULL << v);
        adj[v] |= (1ULL << u);
        deg[u]++; deg[v]++;
    }
 
    int K = A + B;
    ull bestScore = 0;
 
    // ---- Předvýpočet horní možné hranice ----
    // Spočítáme maximální možné "zlepšení" (přidání) pro případ,
    // že by všechny A vrcholy měly nejvyšší stupeň v grafu.
    // vector<char> deg_sorted = deg;
    // sort(deg_sorted.begin(), deg_sorted.end(), greater<int>());
 
    // ull max_possible_add = 0;
    // for (char i = 0; i < min(A, N); ++i)
    //     max_possible_add += deg_sorted[i];
 
    // ---- Inicializace kombinací ----
    ull limit = ((1ULL << N) - 1ULL);
    ull comb = ((1ULL << K) - 1ULL);
 
    // ---- Iterace přes všechny kombinace ----
    while (comb <= limit) {
        ull baseline = 0;
        vector<char> deltas; deltas.reserve(K);
 
        // --- Spočítáme baseline ---
        ull s = comb;
        while (s) {
            int v = __builtin_ctzll(s);
            s &= s - 1;
 
            int in_deg = __builtin_popcountll(adj[v] & comb);
            int out_deg = deg[v] - in_deg;
 
            baseline += out_deg;
            deltas.push_back(in_deg - out_deg);
        }
 
        // 💡 Tvoje myšlenka:
        // Pokud je baseline + max_possible_add <= bestScore,
        // i v nejlepším případě už nepřekonáme současné maximum.
        if (!deltas.empty()) {
            int maxDelta = *max_element(deltas.begin(), deltas.end());
            if (baseline + (long long)A * maxDelta <= bestScore)
                goto next_combination;
        }        
 
        // --- Výběr A nejlepších delt ---
        if (A > 0) {
            if ((char)deltas.size() <= A) {
                ull add = 0;
                for (char x : deltas) add += x;
                bestScore = max(bestScore, baseline + add);
            } else {
                nth_element(deltas.begin(), deltas.begin() + A, deltas.end(), greater<int>());
                ull add = 0;
                for (char i = 0; i < A; ++i) add += deltas[i];
                bestScore = max(bestScore, baseline + add);
            }
        } else {
            bestScore = max(bestScore, baseline);
        }
 
        // --- Další kombinace (Gosperův hack) ---
        next_combination:  // sem skočíme, pokud baseline byla moc malá
        if (comb == 0) break;
        ull c = comb & -comb;
        ull r = comb + c;
        if (r == 0) break;
        comb = (((r ^ comb) >> 2) / c) | r;
        if (comb > limit) break;
    }
 
    cout << bestScore << "\n";
    return 0;
}
