#include <bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};
int max_lenght = 3;

int DFS(Node* root, int prev){
    if(!root){
        return 0;
    }
    int lenght = 1;
    int left, right;
    int value = root->data;
    left = DFS(root->left, value);
    right = DFS(root->right, value);
    if((root->left && root->right)){
        if((root->left->data != value || root->right->data != value) && (left > 0 && right > 0)){
            max_lenght = max(left + right + 1, max_lenght);
        }
        if(root->left->data == value && value == prev && root->right->data == value){
            lenght = 0;
        }
        else if(root->left->data == value && value == prev && right > 0){
            
            lenght = right + 1;
        }
        else if(root->right->data == value && value == prev && left > 0){
            lenght = left + 1;
        }
        else if(root->left->data == value && value == prev && root->right->data == value){
            lenght = 0;
        }
        else{
            lenght = 1 + max(left, right);
        }
    }
    return lenght;
    
}


int DFS_start(Node* root){
    if(!root){
        return 0;
    }
    int left, right;
    int value = root->data;
    left = DFS(root->left, value);
    right = DFS(root->right, value);
    if((root->left && root->right) && (root->left->data != value || root->right->data != value)){
        if(left != 0 && right != 0){
            max_lenght = max(left + right + 1, max_lenght);
        }
    }
    return max_lenght;
}
void printTreeLevels(Node* root) {
    if (!root) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int level_size = q.size(); // kolik uzlů je na této úrovni

        for (int i = 0; i < level_size; i++) {
            Node* current = q.front();
            q.pop();

            cout << current->data << " ";

            if (current->left)
                q.push(current->left);
            if (current->right)
                q.push(current->right);
        }

        cout << endl; // konec jedné úrovně
    }
}

int main(){
    int nodes_num;
    cin >> nodes_num;
    vector<int> values(nodes_num);
    for(int i = 0; i < nodes_num; i++){
        cin >> values[i];
    }

    Node* root = new Node(values[0]);
    queue<Node*> q;
    q.push(root);
    int index = 1;

    while(!q.empty() && index < nodes_num){
        Node* current = q.front();
        q.pop();

        // Pokud je to list, tak už dál nic nevytvářej
        if (current->data == 2) continue;

        // Levé dítě (pokud máme data)
        if(index < nodes_num){
            current->left = new Node(values[index]);
            if (values[index] != 2) q.push(current->left);
            index++;
        }

        // Pravé dítě (pokud máme data)
        if(index < nodes_num){
            current->right = new Node(values[index]);
            if (values[index] != 2) q.push(current->right);
            index++;
        }
    }
    //printTreeLevels(root);

    
    int result = DFS_start(root);
    //cout << "Max length: " << max_lenght << endl;
    cout << result << endl;


    return 0;
}