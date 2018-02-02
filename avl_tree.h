#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct node {
    int value;
    int height;
    node * parent;
    node * left;
    node * right;
};

int height(node * root){
    if(root == nullptr) return 0;
    else return root -> height;
}

int getbalance(node * root){
    if(root == nullptr) return 0;
    else return height(root -> left) - height(root -> right);
}

node  * newnode(int value){
    node * ans;
    ans = new node;
    ans -> value = value;
    ans -> height = 1;
    ans -> parent = nullptr;
    ans -> left = nullptr;
    ans -> right = nullptr;
    return ans;
}

node * rotateR(node * root){
    if(root -> left == nullptr) return root;
    node * x = root -> left;
    root -> left = x -> right;
    x -> right = root;
    root -> height = max(height(root -> left), height(root -> right)) + 1;
    x -> height = max(height(x -> left), height(x -> right)) + 1;
    x -> parent = root -> parent;
    root-> parent = x;
    if(root -> left != nullptr) root -> left -> parent = root;
    return x;
}

node * rotateL(node * root){
    if(root -> right == nullptr) return root;
    node * z = root -> right;
    root -> right = z -> left;
    z -> left = root;
    root -> height = max(height(root -> left), height(root -> right)) + 1;
    z -> height = max(height(z -> left), height(z -> right)) + 1;
    z -> parent = root -> parent;
    root -> parent = z;
    if(root -> right != nullptr) root -> right -> parent = root;
    return z;
}


node * balanceup(node * up){
    if(up == nullptr) return up;
    int value;
    node * u, * t;
    value = up -> value;
    u = up;
    t = u -> parent;
    while(t != nullptr){
        if(value < t -> value) t -> left = u;
        else t -> right = u;
        u = t;
        if(getbalance(u) > 1){
            if(getbalance(u -> left) >= 0) u = rotateR(u);
            else{//left right
                u -> left = rotateL(u -> left);
                u = rotateR(u);
            }
        }
        else if(getbalance(u) < -1){
            if(getbalance(u -> right) <= 0) u = rotateL(u);
            else{//right left
                u -> right = rotateR(u -> right);
                u = rotateL(u);
            }
        }
        else u -> height = max(height(u->right), height(u-> left)) + 1;//mmm...
        t = u -> parent;
    }
    return u;
}

node * insertin(node * root, int value){
    node * noob;
    noob = newnode(value);
    if(root == nullptr) return noob;
    node *t = root, *u = root;
    while(u != nullptr){
        t = u;
        if(value == u -> value) return root;
        if(value < u -> value) u = u -> left;
        else u = u -> right;
    }
    if(value < t -> value) t -> left = noob;
    else t-> right = noob;
    noob -> parent = t;
    u = balanceup(noob);
    return u;
}


node * extremeleft(node * root){
    node * t = root;
    while(t -> left != nullptr) t = t -> left; 
    return t;
}

/* THIS THING IS DIFFICULT TO FIX...
int erasin(node * root, int value){
    node * u, * v = root, * replace, *t;
    if(root == nullptr) return 0;
    while(v != nullptr) {
        u = v;
        if(value < v -> value) v = v -> left;
        else if(value > v -> value) v = v -> right;
        else v = nullptr;
    }
    if(value != u -> value) return 0; 
    else if(u -> right == nullptr && u -> left == nullptr && u -> parent == nullptr){
        delete u;
        root = nullptr;
        return 1;
    }
    else if(u -> right == nullptr && u -> left == nullptr){
        t = u -> parent;
        if(value < t -> value) t -> left = nullptr;
        else t -> right = nullptr;
    }
    if(u -> right == nullptr){
        replace = u -> left;
        t = replace;
    }
    else if(u -> right -> left == nullptr){
        replace = u -> right;
        replace -> left = u -> left;
        t = replace;
    }
    else {
        replace = extremeleft(u -> right);
        replace -> left = u -> left;
        replace -> right = u -> right;
        t = replace -> parent;
        t -> left = nullptr;
    }
    replace -> parent = u -> parent;
    if(replace -> right != nullptr) replace -> right -> parent = replace;
    if(replace -> left != nullptr) replace -> left -> parent = replace;
    delete u;
    t = balanceup(t);
    root = t;
    return 1;
}
*/

void printnode(node * root){
    int i, j, k, l, n;
    vector<node *> queue;
    node * current;
    if(root == nullptr) return ;
    queue.push_back(root);
    while(!queue.empty()){
        while(queue.back() -> left != nullptr) queue.push_back(queue.back() -> left);
        while(!queue.empty() && queue.back() -> right == nullptr){
            for(i = 1; i < height(queue.back()); i++) cout << "  ";
            cout << queue.back() -> value << endl;
            queue.pop_back();
        }
        if(!queue.empty()) {
            current = queue.back();
            for(i = 1; i < height(current); i++) cout << "  ";
            cout << current -> value << endl;
            queue.pop_back();
            queue.push_back(current -> right);
        }
    }
    return ;
}

void printnrec(node * root){
    int i;
    if(root != nullptr){
        printnrec(root -> left);
        if(root-> right != nullptr) cout << endl;
        for(i = 1; i < height(root); i++) cout << "  ";
        cout << root -> value;
        if(root-> right != nullptr) cout << endl;
        printnrec(root -> right);
    }
}
