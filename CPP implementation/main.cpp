#include "avl.h"
#include <iostream>
#include <utility>
#include <array>
using namespace std;


void _inorder(node* root)
{
    if (!root) return;
 
    _inorder(root->left);
 
    cout << root->data
         << " max = " << root->max_right << endl;
 
    _inorder(root->right);
}


int main(){
    array<pair<int,int>,5> ints = {
        make_pair(10, 30), make_pair(17, 19),
        make_pair(5, 20), make_pair(12, 15), make_pair(30, 40)
    };

    avl tree(make_pair(15, 20));
 
    for(auto x : ints){
        tree.insert(x);
    }

    _inorder(tree.root);
    return 0;

}

