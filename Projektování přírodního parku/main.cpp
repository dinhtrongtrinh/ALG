#include <iostream>
#include <vector>

using namespace std;
int max_tree = 0; 
/*
bool checking_for_S(vector<vector<int>>& park, int xstart, int ystart, int xend, int yend, int S){
    int sum = 0;
    for (int i = xstart; i <=  xend; i++){
        for (int j = ystart; j <=  yend; j++){
            if (park[i][j] == 2){
                sum++;
            }
        }
    }
    if (sum >= S){
        return true;
    }
    return false;
}
*/
int checking_tree( vector<vector<int>>& park, int N, int K, int L, int S){
    // checking for valid park areas
    int current_S = 0; 
    int valid_park_size_end = N - L;
    for(int i = L ; i < valid_park_size_end; i++){
        for(int j = L; j < valid_park_size_end; j++){
            
        }
    }    
    return max_tree;
}



int main (){
    int N, K, L, S;
    cin >> N >> K >> L >> S;

    vector<vector<int>> park(N, vector<int>(N)); // N x N matrix

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> park[i][j]; // directly fill the matrix
        }
    }
    int result = checking_tree(park, N, K, L, S);
    cout << result << endl;
    

    return 0;
}
