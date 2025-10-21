#include <bits/stdc++.h>
using namespace std;

struct Node {
    int height;
    int data;
    Node* left;
    Node* right;
    
    Node(int value, int h) {
        height = h;
        data = value;
        left = nullptr;
        right = nullptr;
    }
};
int compact_count = 0;
set<int> delited_values;
map<int,int> value_and_height; 

bool is_compact(Node* root, int itis, int isnot){
    //dfs checking
    if(!root){
        return true;
    }
    return true;
}



int main(){
    int num_operations;
    cin >> num_operations;
    string operation;
    int value;
    cin >> operation >> value;
    Node* root = new Node(value, 0);
    
    
    for(int i = 1; i < num_operations; i++){
        string operation;
        int value;

        cin >> operation >> value;
        if(operation == "ins"){
            while(root != nullptr){
                if(value < root->data){
                    //insert left
                    if(root->left == nullptr){
                        root->left = new Node(value, root->height + 1);
                        value_and_height[value] = root->height + 1;
                        break;
                    }
                    else{
                        root = root->left;
                    }

                }
                else{
                    //insert right
                    if(root->right == nullptr){
                        root->right = new Node(value, root->height + 1);
                        value_and_height[value] = root->height + 1;
                        break;
                    }
                    else{
                        root = root->right;
                    }
                }
            }
        }
        //del operation
        else{
            delited_values.insert(value);
        }
        //compact evaluation
        bool compact;
        if(delited_values.find(value) != delited_values.end()){
            compact = is_compact(root, 1, 0);
        }
        else{
            compact = is_compact(root, 0, 1);
        }
        if(compact){
            //make whole tree again
            compact_count++;
        }
    }



    return 0;
}