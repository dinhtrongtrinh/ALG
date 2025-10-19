#include <bits/stdc++.h>
using namespace std;

// N - počet uzlů
// H - počet hlučných uzlů
// E - počet hran
// S - startovní uzel myšky
// C - cílový uzel myšky
// K - startovní uzel kocoura
// M - maximální počet skoků kocoura
int N, H , E;
int S, C, K, M;

set<int> noisy_nodes;
vector<vector<int>> nodes;
vector<int> dist_cat; // vzdálenost od kocoura

// 🐈 BFS od kocoura – spočítá minimální počet kroků, aby se dostal do každého uzlu
void create_map_of_jump_cat() {
    dist_cat.assign(N, INT_MAX);
    queue<int> q;
    q.push(K);
    dist_cat[K] = 0;

    while (!q.empty()) {
        int current = q.front(); q.pop();
        for (int neighbour : nodes[current]) {
            if (dist_cat[neighbour] == INT_MAX) {
                dist_cat[neighbour] = dist_cat[current] + 1;
                q.push(neighbour);
            }
        }
    }
}

void BFS_mouse() {
    // dist[node][z] = počet kroků
    vector<vector<int>> dist(N, vector<int>(M + 1, -1));

    int start_noisy = noisy_nodes.count(S);
    if (dist_cat[S] <= start_noisy) {
        cout << "-1 -1\n"; // start je nebezpečný
        return;
    }

    queue<pair<int,int>> q;
    q.push({S, start_noisy});
    dist[S][start_noisy] = 0;

    while (!q.empty()) {
        auto [current, noisy_count] = q.front();
        q.pop();

        for (int neighbour : nodes[current]) {
            int new_noisy = noisy_count + (noisy_nodes.count(neighbour) ? 1 : 0);
            if (new_noisy > M) new_noisy = M;

            // nebezpečné – kocour může být ve stejném nebo dřívějším kroku
            if (dist_cat[neighbour] <= new_noisy) continue;

            if (dist[neighbour][new_noisy] == -1) {
                dist[neighbour][new_noisy] = dist[current][noisy_count] + 1;
                q.push({neighbour, new_noisy});
            }
        }
    }

    // najdeme nejlepší řešení pro cíl
    int best_steps = INT_MAX, best_noisy = INT_MAX;
    for (int z = 0; z <= M; z++) {
        if (dist[C][z] != -1) {
            if (dist[C][z] < best_steps ||
                (dist[C][z] == best_steps && z < best_noisy)) {
                best_steps = dist[C][z];
                best_noisy = z;
            }
        }
    }

    if (best_steps == INT_MAX)
        cout << "-1 -1\n";
    else
        cout << best_steps << " " << best_noisy << "\n";
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> H >> E;
    cin >> S >> C >> K >> M;

    for (int i = 0; i < H; i++) {
        int a; cin >> a;
        noisy_nodes.insert(a);
    }

    nodes.resize(N);
    for (int i = 0; i < E; i++) {
        int a, b; cin >> a >> b;
        nodes[a].push_back(b);
        nodes[b].push_back(a);
    }

    create_map_of_jump_cat();
    BFS_mouse();
}
