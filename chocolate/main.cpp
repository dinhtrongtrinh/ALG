#include <iostream>
#include <string>
#include <vector>
void readData(){
    int x, y;
    std::vector<std::vector<int>> bars;
    std::cin >> x >> y;
    for(int i = 0; i < x; ++i) {
        std::vector<int> bar(y);
        for (int j = 0; j < y; ++j) {
            std::cin >> bar[j];
        }
        bars.push_back(bar);
    }
}
int algorithm(std::vector<std::vector<int>> bars, int x, int y){
    int answer = 0;

    return answer;
}
int main(){
    int x, y;
    std::vector<int> bars;
    std::cin >> x >> y;
    for(int i = 0; i < x + y; i++){
        int temp;
        std::cin >> temp;
        bars.push_back(temp); 
        std::cout << temp << " ";
    }
    return 0; 
}