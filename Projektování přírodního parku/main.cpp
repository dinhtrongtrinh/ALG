#include <iostream>
#include <vector>

using namespace std;
int max_tree = 0; 
int checking_num_prefix_sum(int x1, int y1, int x2, int y2, vector<vector<int>>& prefix_sum){
    if(x1 == 0 && y1 == 0){
        return prefix_sum[x2][y2];
    }
    else if (x1 == 0){
        return prefix_sum[x2][y2] - prefix_sum[x2][y1-1];
    }
    else if (y1 == 0){
        return prefix_sum[x2][y2] - prefix_sum[x1-1][y2];
    }
    else{
        return prefix_sum[x2][y2] - prefix_sum[x1-1][y2] - prefix_sum[x2][y1-1] + prefix_sum[x1-1][y1-1];
    }
}
int checking_tree(vector<vector<int>>& park, int N, int K, int L, int S){
    vector<vector<int>> prefix_sum_tree(N, vector<int>(N));
    vector<vector<int>> prefix_sum_S(N, vector<int>(N));
    // 0,0 initialization
    if (park[0][0] == 1) {
        prefix_sum_tree[0][0] = 1;
        prefix_sum_S[0][0] = 0;
    } else if (park[0][0] == 2) {
        prefix_sum_tree[0][0] = 0;
        prefix_sum_S[0][0] = 1;
    } else {
        prefix_sum_tree[0][0] = 0;
        prefix_sum_S[0][0] = 0;
    }
    
    // first column
    for(int i = 1; i < N; i++){
        if(park[0][i] == 1){
            prefix_sum_tree[0][i] = prefix_sum_tree[0][i-1] + 1;
            prefix_sum_S[0][i] = prefix_sum_S[0][i-1];
        }
        else if (park[0][i] == 2){
            prefix_sum_S[0][i] = prefix_sum_S[0][i-1] + 1;
            prefix_sum_tree[0][i] = prefix_sum_tree[0][i-1];
        }
        else{
            prefix_sum_tree[0][i] = prefix_sum_tree[0][i-1];
            prefix_sum_S[0][i] = prefix_sum_S[0][i-1];
        }
    }
    // the rest of the matrix
    for(int i = 1; i < N; i++){
        for(int j = 0; j < N; j++){
            if(j == 0){
                if(park[i][j] == 1){
                    prefix_sum_tree[i][j] = prefix_sum_tree[i-1][j] + 1;
                    prefix_sum_S[i][j] = prefix_sum_S[i-1][j];
                }
                else if (park[i][j] == 2){
                    prefix_sum_S[i][j] = prefix_sum_S[i-1][j] + 1;
                    prefix_sum_tree[i][j] = prefix_sum_tree[i-1][j];
                }
                else{
                    prefix_sum_tree[i][j] = prefix_sum_tree[i-1][j];
                    prefix_sum_S[i][j] = prefix_sum_S[i-1][j];
                }
            }
            else{
                if(park[i][j] == 1){
                    prefix_sum_tree[i][j] = prefix_sum_tree[i-1][j] + prefix_sum_tree[i][j-1] - prefix_sum_tree[i-1][j-1] + 1;
                    prefix_sum_S[i][j] = prefix_sum_S[i-1][j] + prefix_sum_S[i][j-1] - prefix_sum_S[i-1][j-1];
                }
                else if (park[i][j] == 2){
                    prefix_sum_S[i][j] = prefix_sum_S[i-1][j] + prefix_sum_S[i][j-1] - prefix_sum_S[i-1][j-1] + 1;
                    prefix_sum_tree[i][j] = prefix_sum_tree[i-1][j] + prefix_sum_tree[i][j-1] - prefix_sum_tree[i-1][j-1];
                }
                else{
                    prefix_sum_tree[i][j] = prefix_sum_tree[i-1][j] + prefix_sum_tree[i][j-1] - prefix_sum_tree[i-1][j-1];
                    prefix_sum_S[i][j] = prefix_sum_S[i-1][j] + prefix_sum_S[i][j-1] - prefix_sum_S[i-1][j-1];
                }
            }

        }
    }
    // checking all K x K center submatrices
    int size_end = N - K;
    for(int i = 0 ; i <= size_end; i++){
        for(int j = 0; j <= size_end; j++){
            int x1 = i;
            int y1 = j;
            int x2 = i + K;
            int y2 = j + K;
            int num_S = checking_num_prefix_sum(x1 + L, y1 + L, x2 - L - 1, y2 - L - 1, prefix_sum_S);
            if(num_S >= S){
                int num_tree = checking_num_prefix_sum(x1, y1, x2 - 1 , y2 - 1, prefix_sum_tree);
                if(num_tree > max_tree){
                    max_tree = num_tree;
                }
            }
        }
    }
    /*
    // print park
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << park[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    // print the prefix sum matrix
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << prefix_sum_tree[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << prefix_sum_S[i][j] << " ";
        }
        cout << endl;
    }
    */

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
