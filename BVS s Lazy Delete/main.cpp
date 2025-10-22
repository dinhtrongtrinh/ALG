#include <bits/stdc++.h>
using namespace std;

bool debug_print = false;  // zapni / vypni debug výpisy

int compact_count = 0;
int depth = 0;  // celková hloubka stromu

struct Node {
    int depth;   // hranová vzdálenost od kořene
    int data;
    Node* left;
    Node* right;
    
    Node(int value, int d) {
        depth = d;
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

unordered_set<int> delited_values;
unordered_map<int,int> value_and_depth; 
int total_node = 0;
int deleted_node = 0;
int non_deleted_node = 0;
int max_depth = 0;
int deleted_sum = 0;
int non_deleted_sum = 0;

bool is_compact(int max_depth){
    int itis = 0;
    int isnot = 0;
    for (auto val : value_and_depth) {
        if (delited_values.count(val.first)) {
            itis += max_depth - val.second;   
        } else {
            isnot += max_depth - val.second;  
        }
    }
    return itis > isnot;
}

vector<int> DFS(vector<int>& list_of_keys, Node* root) {
    if (!root) return list_of_keys;
    if (!delited_values.count(root->data))
        list_of_keys.push_back(root->data);
    list_of_keys = DFS(list_of_keys, root->left);
    list_of_keys = DFS(list_of_keys, root->right);
    return list_of_keys;
}

int getDepth(Node* root) {
    if (root == nullptr) {
        return -1;
    }
    int leftDepth = getDepth(root->left);
    int rightDepth = getDepth(root->right);
    return max(leftDepth, rightDepth) + 1;
}

Node* buildBalancedBST(vector<int> arr, int depth) {
    Node* root = new Node(arr[0], depth);
    value_and_depth[arr[0]] = depth;
    total_node = arr.size();
    non_deleted_node = arr.size();
    deleted_node = 0;
    non_deleted_sum = 0;
    deleted_sum = 0;
    max_depth = depth;

    for(int i = 1; i < arr.size(); i++){
        Node* curr = root;
        while (true) {
            if (arr[i] < curr->data) {
                if (!curr->left) {
                    curr->left = new Node(arr[i], curr->depth + 1);
                    value_and_depth[arr[i]] = curr->depth + 1;
                    if(curr->depth + 1 > max_depth){
                        max_depth = curr->depth + 1;
                    }
                    non_deleted_sum += value_and_depth[arr[i]];
                    break;
                }
                curr = curr->left;
            } else if (arr[i] > curr->data) {
                if (!curr->right) {
                    curr->right = new Node(arr[i], curr->depth + 1);
                    value_and_depth[arr[i]] = curr->depth + 1;
                    if(curr->depth + 1 > max_depth){
                        max_depth = curr->depth + 1;
                    }
                    non_deleted_sum += value_and_depth[arr[i]];
                    break;
                }
                curr = curr->right;
            }
            else{
                break;
            }
        }
    }
    return root;
}

Node* batch_deletion(Node* root, int& max_depth){
    vector<int> list_of_keys;
    list_of_keys = DFS(list_of_keys, root);
    value_and_depth.clear();
    delited_values.clear();
    Node* return_root = buildBalancedBST(list_of_keys, 0);
    return return_root;
}

void printTree(Node* root, int space = 0, int indent = 5) {
    if (!debug_print || !root) return;

    printTree(root->right, space + indent, indent);

    int height = max_depth - root->depth;  // výška podle definice
    cout << setw(space) << "" 
         << root->data << "(h=" << height << endl;

    printTree(root->left, space + indent, indent);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int num_operations;
    cin >> num_operations;
    string operation;
    int value;
    cin >> operation >> value;

    Node* root = new Node(value, 0);
    value_and_depth[value] = 0;
    total_node++;
    non_deleted_node++;

    for(int i = 1; i < num_operations; i++){
        string operation;
        int value;
        cin >> operation >> value;
        bool changed = false;

        if (operation == "ins") {
            if (!root) {
                root = new Node (value, 0);
                value_and_depth[value] = 0;
            } else {
                Node* curr = root;
                while (true) {
                    if (value < curr->data) {
                        if (!curr->left) {
                            curr->left = new Node(value, curr->depth + 1);
                            value_and_depth[value] = curr->depth + 1;
                            if(curr->depth + 1 > max_depth){
                                max_depth = curr->depth + 1;
                            }
                            total_node++;
                            non_deleted_node++;
                            non_deleted_sum += value_and_depth[value];
                            changed = true;
                            break;
                        }
                        curr = curr->left;
                    } else if (value > curr->data) {
                        if (!curr->right) {
                            curr->right = new Node(value, curr->depth + 1);
                            value_and_depth[value] = curr->depth + 1;
                            if(curr->depth + 1 > max_depth){
                                max_depth = curr->depth + 1;
                            }
                            total_node++;
                            non_deleted_node++;
                            non_deleted_sum += value_and_depth[value];
                            changed = true;
                            break;
                        }
                        curr = curr->right;
                    } else {
                        if (delited_values.count(value)) {
                            delited_values.erase(value); 
                            non_deleted_node++; deleted_node--;
                            non_deleted_sum += value_and_depth[value];
                            deleted_sum -= value_and_depth[value];
                            changed = true;
                        }
                        break;
                    }
                }
            }
        }
        else { // delete
            if (delited_values.count(value)) {
                continue;
            } 
            delited_values.insert(value);
            non_deleted_node--;
            deleted_node++;
            deleted_sum += value_and_depth[value];
            non_deleted_sum -= value_and_depth[value];
            changed = true;
        }

        bool compact;
        int Sdel = (deleted_node * max_depth) - deleted_sum;
        int Sund = (non_deleted_node * max_depth) - non_deleted_sum;
        if (debug_print) {
            cout << "Operation: " << operation << " " << value << endl;
            cout << "Deleted values: ";
            for (auto val : delited_values) {
                cout << val << " ";
            }
            cout << endl;
            cout << "Total nodes: " << total_node << ", Deleted: " << deleted_node << ", Non-deleted: " << non_deleted_node << endl;
            cout << "Max depth: " << max_depth << endl;
            cout << "Deleted sum depths: " << deleted_sum << ", Non-deleted sum depths: " << non_deleted_sum << endl;
            cout << "Sdel: " << Sdel << ", Sund: " << Sund << endl;
            cout << "Tree structure:\n";
            printTree(root);
        }

        if(Sdel > Sund && changed){
            root = batch_deletion(root, max_depth);
            compact_count++;
            if (debug_print)
                cout << "COMPACTED\n";
        }
        if (debug_print)
            cout << "\n\n------------------\n\n";
    }

    depth = getDepth(root);
    cout << compact_count << " " << depth << endl;

    return 0;
}
