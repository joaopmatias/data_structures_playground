nclude <cmath>
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

tree *rotate_l(tree *root){ /* REMOVE POINTERS!!! */
    tree * t;
    int r, s, u;
    t = root -> right;
    root -> right = t ->left;
    t -> left = root;
    t->balance = r;
    root->balance = s;
    if(r >= 0){/* re check computations */
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
    if(r >= 0){
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




tree *ins_tree(int n, tree *root, tree *parents){
    /* go forward, then backwards */
    int i = -1;
    (root -> weight)++;
    tree *temp = root, leaf;
    
    leaf.node = n;
    leaf.weight = 1;
    leaf.balance = 0;
    leaf.left = nullptr;
    leaf.right = nullptr;
    
    while(temp != nullptr){
        i++;
        parents[i] = *temp;
        (temp -> weight)++;
        
        if(n <= temp -> node){
            temp = temp -> left;
        }
        else{
            temp = temp -> right;
        }
    }
    
    if(n < parents[i].node){
        parents[i].left = &leaf; 
        parents[i].balance++;
        /* count more larger terms */
    }
    else{
        parents[i].right = &leaf;
        parents[i].balance--;
    }
    
    while(i > 0){ /* update index i-1. recall that height of i just got larger */
        if(parents[i].node <= parents[i-1].node){
            if(parents[i - 1].balance == -1){/* do nothing */
                parents[i - 1].balance = 0;
                i = 0;
            }
            else{
                if(parents[i - 1].balance == 0){/* do nothing, but height still gets larger */
                    parents[i - 1].balance = 1;
                }
                else{
                    if(parents[i].balance == 1){/* rotate right*/
                        parents[i - 1] = *rotate_r( &parents[i - 1]);
                    }/* THIS IS BAD use pointer from grandparents !!! */
                    else{ /* rotate left on child, and then right on parent */
                        parents[i - 1] = *rotate_lr( &parents[i - 1]);
                    }
                }
            }
        }
        else{
            if(parents[i - 1].balance == 1){
                parents[i - 1].balance = 0;
                i = 0;
            }
            else{
                if(parents[i - 1].balance == 0){
                    parents[i - 1].balance = -1;
                }
                else{
                    if(parents[i].balance == -1){ /* rotate left*/
                        parents[i - 1] = *rotate_l( &parents[i - 1]);
                    }
                    else{ /*rotate right on child, and then left on parent */
                        parents[i - 1] = *rotate_rl( &parents[i - 1]);
                    }
                }
            }
        }
        i--;
    }
    return parents;
}

tree *rm_tree(int n, tree *root, tree *parents){ /* remove the smallest  */
    int i = 0;
    parents[0] = *root;
    (root -> weight)--;
    tree *temp = root;
    
    while(temp -> node != n){
 
        
        
        
    }
    
    
    return parents;
}
