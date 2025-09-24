#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <utility>

using namespace std;
int placing_the_agent(map<pair<int,char>, set<int>>& graph, int A, int B){
    //placing optimal agents on graph
    int max_score = 0;
    // find the node with the highest degree and place all B agents there
    while(B > 0){
        pair<int,char> max_node;
        int max_node_score = 0;
        for(auto& node : graph){
            int score = node.second.size();
            if(score > max_node_score){
                max_node_score = score;
                max_node = node.first;
            }
        }
    }

    return 0;
}




int main(){
    // parsing the graph from input
    int N, M , A, B;
    cin >> N >> M >> A >> B;
    map<pair<int,char>, set<int>> graph;
    for(int i = 0; i < M; i++){
        int u, v;
        cin >> u >> v;
        pair<int,char> p = make_pair(u, 0);
        graph[p].insert(v);
        graph[p].insert(u);
    }

    return 0; 
}