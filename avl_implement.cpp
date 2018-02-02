#include "avl_tree.h"

using namespace std;

int main(){
    node * root, * hi;
    root = newnode(0);
    root = insertin(root, 6);
    root = insertin(root, 3);
    root = insertin(root, 9);
    root = insertin(root, 1);
    root = insertin(root, 8);
    root = insertin(root, 5);
    root = insertin(root, 4);
    root = insertin(root, 6);
    root = insertin(root, 3);
    root = insertin(root, 9);
    root = insertin(root, 1);
    root = insertin(root, 8);
    root = insertin(root, 5);
    root = insertin(root, 4);
    printnode(root);
    erasin(root, 4);
    printnode(root);
    erasin(root, 4);
    printnode(root);
    hi = root -> right -> right;
    cout << endl << hi -> value;
    deletetree(root);
    cout << endl << hi -> value;
    cout << endl;
    return 0;
}
