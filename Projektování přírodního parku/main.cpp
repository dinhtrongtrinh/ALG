#include <iostream>
#include <vector>

using namespace std;




int main (){
    int N, K, L, S;

    cin >> N >> K >> L >> S;
    vector<vector<int>> park(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        vector<int> row(N);
        for (int j = 0; j < N; j++) {
            int x;
            cin >> x;
            row.push_back(x);
        }
        park.push_back(row);
    }
    //for debug print
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << park[i][j] << " ";
        }
        cout << endl;
    }
    

    return 0;
}
