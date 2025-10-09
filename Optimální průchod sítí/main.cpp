#include <bits/stdc++.h>
using namespace std;
int N, H , E;
int S, C, K, M;

set<int> noisy_nodes;
vector<vector<int>> nodes;






int main(){
    cin >> N >> H >> E;
    cin >> S >> C >> K >> M;

    for(int i = 0; i < H; i++){
        int a; cin >> a;
        noisy_nodes.insert(a);
    }
    for(int i = 0; i < E; i++){
        int a, b; cin >> a >> b;
        nodes[a].push_back(b);
        nodes[b].push_back(a);
    }
    return 0;
}