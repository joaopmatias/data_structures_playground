#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/* create a balanced binary tree implementation */

/* tree is part of an array. each node uses two entries in the array, one for size, and another for the label */

struct tree {
    int node;
    int weight;
    int balance;
    tree *left;
    tree *right;
};

tree *rotate_l(tree *root){ /*  */
    tree * t;
    int r, s, u;
    t = root -> right;
    root -> right = t ->left;
    t -> left = root;
    t->balance = r;
    root->balance = s;
    if(r >= 0){/* re check computations. check update of balance in */
        root -> balance = s + 1;
        if(s + 1 > 0){
            t -> balance = r + s + 2;
        }
        else{
            t -> balance = r + 1;
        }
    }
    else{
        root -> balance = s - r + 1;
        if(s - r + 1 > 0){
            t -> balance = s + 2;
        }
        else{
            t -> balance = r + 1;
        }
    }
    r = 0;
    s = 0;
    u = 0;
    if(root -> left != nullptr){
        r = root -> left -> weight;
    }
    if(root -> right != nullptr){
        s = root -> right -> weight;
    }
    if(t -> right != nullptr){
        u = t -> right -> weight;
    }
    root -> weight = r + s + 1;
    t -> weight = r + s + u + 2;
    return t;
}

tree *rotate_r(tree *root){
    tree *t;
    int r, s, u;
    t = root -> left;
    root -> left = t -> right;
    t -> right = root;
    t->balance = r;
    root->balance = s;
    if(r >= 0){ /* you may have to update the balance in ins. done */
        root->balance = s - r - 1;
        if(s - r - 1 > 0){
            t->balance = r - 1;
        }
        else{
            t->balance = s - 2;
        }
    }
    else{
        root->balance = s - 1;
        if(s - 1 > 0){
            t->balance = r - 1;
        }
        else{
            t->balance = s + r - 2;
        }
        
    }
    r = 0;
    s = 0;
    u = 0;
    if(root -> left != nullptr){
        r = root -> left -> weight;
    }
    if(root -> right != nullptr){
        s = root -> right -> weight;
    }
    if(t -> left != nullptr){
        u = t -> left -> weight;
    }
    root -> weight = r + s + 1;
    t -> weight = r + s + u + 2;
    return t;
}

tree *rotate_lr(tree *root){
    root -> left = rotate_l(root -> left);
    return rotate_r(root);
}

tree *rotate_rl(tree *root){
    root -> right = rotate_r(root -> right);
    return rotate_l(root);
}




tree *ins_tree(int n, tree *root, tree **parents, int * count_larger){
    /* go forward, then backwards */
    int i = -1;
    tree *temp = root, *leaf;
    
    leaf = new tree;
    leaf->node = n;
    leaf->weight = 1;
    leaf->balance = 0;
    leaf->left = nullptr;
    leaf->right = nullptr;
    
    count_larger = 0;
    while(temp != nullptr){
        i++;
        (temp -> weight)++;
        parents[i] = temp;
        
        if(n < temp -> node){/* update balance. good */
            count_larger++;
            if(temp -> right != nullptr){
                count_larger += temp -> right -> weight;
            }
            (temp -> balance)++;
            temp = temp -> left; /* count here. done */
            
        }
        else{
            (temp -> balance)--;
            temp = temp -> right;
        }
    }
    
    if(n < parents[i]->node){
        parents[i]->left = leaf; /* leaf might get destroyed after return. Allocate*/
        (parents[i]->balance)++;
        /* count more larger terms. Nope */
    }
    else{
        parents[i]->right = leaf;
        (parents[i]->balance)--;
    }
    
    while(i > 0){ /* update index i-1. recall that height of i just got larger */
        if(parents[i]->node <= parents[i-1]->node){
            if(parents[i - 1]->balance == 0){/* do nothing */
                i = -1;
            }
            else{
                if(parents[i - 1]->balance == 2){/* do nothing, but height still gets larger */
                    if(parents[i]->balance == 1){/* rotate right*/
                        parents[i - 1] = rotate_r( parents[i - 1]);
                    }/* THIS IS BAD use pointer from grandparents !!! */
                    else{ /* rotate left on child, and then right on parent */
                        parents[i - 1] = rotate_lr( parents[i - 1]);
                    }
                }
            }
        }
        else{
            if(parents[i - 1]->balance == 0){
                i = -1;
            }
            else{
                if(parents[i - 1]->balance == -2){
                    if(parents[i]->balance == -1){ /* rotate left*/
                        parents[i - 1] = rotate_l( parents[i - 1]);
                    }
                    else{ /*rotate right on child, and then left on parent */
                        parents[i - 1] = rotate_rl( parents[i - 1]);
                    }
                }
            }
        }
        i--;
    }
    return *parents;
}

/* removes node n if it exists. wait, wikipedia says something different about the construction */

/* find_min in rm, or maybe not... */

/* */




tree *rm_tree(int n, tree *root, tree **parents, int * count_smaller){ /* remove the smallest  */
    int i = -1, dep;
    tree *temp = root, *gotit;
    
    count_smaller = 0;
    while(temp != nullptr && temp -> node != n){/* search */
        i++;
        parents[i] = temp;
        
        if(n > temp -> node){
            count_smaller++;
            if(temp -> left != nullptr){
                count_smaller += temp -> left -> weight;
            }
            temp = temp -> right;
        }
        else{
            temp = temp -> left;
        }
    }
    
    if(temp == nullptr){
        return root; /* leave routine */
    }
    else{
        gotit = temp;
    }
    
    dep = i; /* depth is parent of gotit */
    while(i >= 0){ /* correct the weights above */
        (parents[i]->weight)--;
        if(n > parents[i]->node){
            (parents[i]->balance)++;
            (parents[i]->weight)--;
        }
        else{
            (parents[i]->balance)--;
            (parents[i]->weight)--;
        }
        i--;
    }
    
    i = dep;
    if(gotit->left == nullptr){
        if(i == -1){
            *parents = gotit->right;
            delete gotit;
            return *parents;
        }
        else{
            if(n <= parents[i]->node){/* left child */
                parents[i]->left = gotit->right;/* is parent of removed */
            }/* no need to update weights */
            else{
                parents[i]->right = gotit->right;
            }
            delete gotit;
        }
    }
    else{
        i++;
        parents[i] = gotit;
        (gotit->weight)--;
        (gotit->balance)--;
        temp = gotit ->left;
        while(temp != nullptr){/* search largest on left tree */
            i++;
            parents[i] = temp;
            if(n > temp -> node){
                (temp->balance)++;
                (temp->weight)--;
                count_smaller++;
                if(temp -> left != nullptr){
                    count_smaller += temp -> left -> weight;
                } /* balance is wrong if n doesn't exist :( */
                temp = temp -> right;
            }
            else{
                (temp->balance)--;
                (temp->weight)--;
                temp = temp -> left;
            }
        }
        /* i is to be removed */
        gotit->node = parents[i]->node;
        if(parents[i - 1]-> node == n){
            parents[i - 1]->left = nullptr;
        }
        else{
            parents[i - 1]->right = parents[i]->left;
        }
        delete parents[i];
        i--;
    }
    /* below is copy pasta */
    
    while(i > 0){ /* update index i-1. recall that height of i just got larger */
        if(n > parents[i-1]->node){
            if(parents[i - 1]->balance == 0){/* do nothing */
                i = -1;
            }
            else{
                if(parents[i - 1]->balance == 2){/* do nothing, but height still gets larger */
                    if(parents[i]->balance == 1){/* rotate right*/
                        parents[i - 1] = rotate_r( parents[i - 1]);
                    }/* THIS IS BAD use pointer from grandparents !!! */
                    else{ /* rotate left on child, and then right on parent */
                        parents[i - 1] = rotate_lr( parents[i - 1]);
                    }
                }
            }
        }
        else{
            if(parents[i - 1]->balance == 0){
                i = -1;
            }
            else{
                if(parents[i - 1]->balance == -2){
                    if(parents[i]->balance == -1){ /* rotate left*/
                        parents[i - 1] = rotate_l( parents[i - 1]);
                    }
                    else{ /*rotate right on child, and then left on parent */
                        parents[i - 1] = rotate_rl( parents[i - 1]);
                    }
                }
            }
        }
        i--;
    }

    return *parents;
}

