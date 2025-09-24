#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K, Ldist, S;
    if (!(cin >> N >> K >> Ldist >> S)) return 0;

    // prefix arrays use (N+1) x (N+1) layout in single vector
    int M = N + 1;
    vector<int> prefForest(M * M, 0), prefRock(M * M, 0);

    // read grid values and put into prefix base (shifted by +1 in both dims)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int v; cin >> v;
            prefForest[(i+1)*M + (j+1)] = (v == 1) ? 1 : 0;
            prefRock[(i+1)*M + (j+1)]   = (v == 2) ? 1 : 0;
        }
    }

    // build 2D prefix sums
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            int idx = i*M + j;
            int top = prefForest[(i-1)*M + j];
            int left = prefForest[i*M + (j-1)];
            int diag = prefForest[(i-1)*M + (j-1)];
            prefForest[idx] += top + left - diag;

            top = prefRock[(i-1)*M + j];
            left = prefRock[i*M + (j-1)];
            diag = prefRock[(i-1)*M + (j-1)];
            prefRock[idx] += top + left - diag;
        }
    }

    auto query = [&](const vector<int>& P, int x1, int y1, int x2, int y2) -> int {
        // coordinates x1..x2, y1..y2 are 0-based grid indices (inclusive)
        // prefix stored with +1 offset
        int A = P[(x2+1)*M + (y2+1)];
        int B = P[x1*M + (y2+1)];
        int C = P[(x2+1)*M + y1];
        int D = P[x1*M + y1];
        return A - B - C + D;
    };

    int centralSize = K - 2 * Ldist; // > 0 guaranteed by zadání (2*L < K)
    int best = -1; // hledáme maximum

    for (int i = 0; i + K <= N; ++i) {
        for (int j = 0; j + K <= N; ++j) {
            int ci = i + Ldist;
            int cj = j + Ldist;
            int rx1 = ci, ry1 = cj;
            int rx2 = ci + centralSize - 1;
            int ry2 = cj + centralSize - 1;

            int rocks = query(prefRock, rx1, ry1, rx2, ry2);
            if (rocks >= S) {
                int forests = query(prefForest, i, j, i + K - 1, j + K - 1);
                if (forests > best) best = forests;
            }
        }
    }

    // dle zadání je zaručeno, že alespoň jedno umístění existuje; pro jistotu:
    if (best < 0) best = 0;
    cout << best << "\n";
    return 0;
}
