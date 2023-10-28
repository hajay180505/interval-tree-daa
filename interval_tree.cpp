#include <vector>
#include "interval_tree.h"
#include <iostream>
#include <queue>
#include <limits.h>
#include <array>
#define int_pair pair<int, int>

using namespace std;
//node functions
int node::height(){
        if(!this) return 0;
        return 1+ max(this->left->height() , this->right->height());
}

int node::balanceFactor(){
        return ( (this->left->height()) - (this->right->height()) );
}

//interval_tree functions
interval_tree::interval_tree(){
        cout<<"CALL insertRoot!!";
        count = 0;
}

interval_tree::interval_tree(int_pair elt){
        node* n = createNode(elt);
        root = n;
        count=1;
}

void interval_tree::insertRoot(int_pair elt){
        node* n = createNode(elt);
        root = n;
	
        count++;

}

node* interval_tree::createNode(int_pair elt){
        node* n = new node;
        if(!n) {
                cout<<"No memory allocted!"<<endl;
                return nullptr;
        }
        n->data = elt;
        n -> max_right = 0;
        n->left = nullptr;
        n->right = nullptr;
        n->parent = nullptr;
        return n;
}

void interval_tree::insert(int_pair elt){
        vector<node*> path;
        ptr = root;
        node* prev = ptr;
        node* _n = createNode(elt);
        while(ptr){
                path.push_back(ptr);
                ptr -> max_right = max(ptr -> max_right, elt.second);
                if(elt > ptr->data){
                        prev = ptr;
                        ptr = ptr->right;
                }
                else{
                        prev = ptr;
                        ptr = ptr->left;
                }
        }
        if(elt > prev->data){
                prev->right = _n;
                prev->right->parent = prev;
        }
        else{
                prev->left = _n;
                prev->left->parent = prev;
        }


        node* n = checkImbalance(path);
        if(n) balance(n);

        path.push_back(_n);
        updateMaxRight(path);
        path.pop_back();
}

node* interval_tree::checkImbalance(const vector<node*>& path){
        node* A = nullptr;
        for(auto it=path.rbegin() ; it!=path.rend() ;  it++){
                int bf = (*it)->balanceFactor();
                if(bf<-1 or bf>1){
                        A = *it;
                        break;
                }
        }
        return A;
}

void interval_tree::balance(node* A){
        if(!A) return;
        node* p = A->parent;
        node* u = nullptr;
        if(A->balanceFactor()==-2){
                //R type
                int currBf = A->right->balanceFactor();
                if(currBf == -1 or currBf == 0) //RR
                        u = RR(A);
                else //RL
                        u = RL(A);

        }
        else{
                int currBf = A->left->balanceFactor();
                //L type
                if(currBf == 1 or currBf == 0) //LL
                        u = LL(A);
                else //LR
                        u = LR(A);
        }
        if(!p){
                root = u;
                root->parent = nullptr;
        }
        else if(p->left == A){
                p->left = u;
                u->parent = p;
        }
        else{
                p->right = u;
                u->parent = p;
        }
}

void interval_tree::updateMaxRight(vector<node*>& path) {
    for (int i = path.size() - 1; i >= 0; i--) {
        node* node = path[i];
	//cout << "node =" << node << endl;
        int leftMaxRight = node->left ? node->left->max_right : -1;
        int rightMaxRight = node->right ? node->right->max_right : -1;
        //cout<<"LMS = "<< leftMaxRight << " ; RMS = " << rightMaxRight << " ; DS = "<<node->data.second << endl;
	
	node->max_right = max(node->data.second, max(leftMaxRight, rightMaxRight));
    }
}

void interval_tree::remove(int_pair elt) {
    vector<node*> path;
    ptr = root;
    while (ptr) {
        path.push_back(ptr);
        if (elt > ptr->data) {
            ptr = ptr->right;
        } else if (elt < ptr->data) {
            ptr = ptr->left;
        } else {
            break;
        }
    }

    if (!ptr) {
        cout << "Element not found! So, not deleted." << endl;
        return;
    }

    node* p = ptr->parent;

    if (!ptr->left && !ptr->right) {
        // Case 1: Node has no children
        if (p) {
            if (p->left == ptr) {
                p->left = nullptr;
            } else {
                p->right = nullptr;
            }
        } else {
            // The removed node is the root
            root = nullptr;
        }
        delete ptr;
    } else if (!ptr->left || !ptr->right) {
        // Case 2: Node has one child
        node* child = (ptr->left) ? ptr->left : ptr->right;
        if (p) {
            if (p->left == ptr) {
                p->left = child;
            } else {
                p->right = child;
            }
            child->parent = p;
        } else {
            // The removed node is the root
            root = child;
            root->parent = nullptr;
        }
        delete ptr;
    } else {
        // Case 3: Node has two children
        node* successor = inorder_successor(ptr);
        ptr->data = successor->data;
        // Remove the successor node
        if (successor->parent->left == successor) {
            successor->parent->left = successor->right;
        } else {
            successor->parent->right = successor->right;
        }
        if (successor->right) {
            successor->right->parent = successor->parent;
        }
        delete successor;
    }

    // Update max_right values and balance the tree if necessary
    node* u = checkImbalance(path);
    if (u) {
        balance(u);
    }
    updateMaxRight(path);
}

//rotations

node* interval_tree::LL(node* A){
        node* k = new node;
        k = A->left;
        A->left = k->right;
        if(A->left) A->left->parent = A;
        k->right = A;
        if(k->right) k->right->parent = k;
        return k;
}

node* interval_tree::LR(node* A){
        A->left = RR(A->left);
        if(A->left) A->left->parent = A;
        return LL(A);
}

node* interval_tree::RL(node* A){
        A->right = LL(A->right);
        if(A->right) A->right->parent = A;
        return RR(A);
}

node* interval_tree::RR(node* A){
        node* k = new node;
        k = A->right;
        A->right = k->left;
        if(A->right) A->right->parent = A;
        k->left= A;
        if(k->left) k->left->parent = k;
        return k;

}
optional<int_pair> interval_tree::getOverlap(int_pair val){
        return searchQuery(root, val);
}

optional<int_pair> interval_tree::searchQuery(node* n, int_pair val){
        if (!n)
            return {} ;
        if (overlap(n->data, val))
            return n->data;
        else{
            int L = val.first;
            int R = val.second;
            if (R < n->data.first)
                return searchQuery(n->left, val);
            else if (L > n->data.second){
                int z = (n->left) ? (n->left->max_right) : (INT_MIN);
                if (z >= L)
                    return searchQuery(n->left, val);
                else
                    return searchQuery(n->right, val);
            }
            return {};
        }
}

vector<int_pair> interval_tree::getAllOverlaps(int_pair val){
        vector<int_pair> result;
        searchAllQuery(root,val,result);
        return result;
}

void interval_tree::searchAllQuery(node* node, int_pair val, vector<int_pair>& res){
        if (!node) 
            return ; 
        if (overlap(node->data, val))
            res.push_back(node->data);

        int L = val.first;
        int R = val.second;

        if (R < node->data.first)
            searchAllQuery(node->left, val, res);
        else if (L > node->data.second){
                int z = (node->left) ? (node->left->max_right) : (INT_MIN);
                if (z<L)
                        searchAllQuery(node->right, val, res);
        }
        else{
            searchAllQuery(node->left, val, res);
            searchAllQuery(node->right, val, res);
        }
        return;
                
}

bool interval_tree::overlap(int_pair i1, int_pair i2){
        array<int_pair,2> arr;
        if(i1.first < i2.first){
                arr[0] = i1;
                arr[1] = i2;
        }
        else if (i2.first < i1.first){
                arr[0] = i2;
                arr[1] = i1;
        }
        else{
                if(i1.second<i2.second){
                        arr[0] = i1;
                        arr[1] = i2;
                }
                else{
                        arr[0] = i2;
                        arr[1] = i1;
                }
        }

        return arr[1].first <= arr[0].second;


}


//non-member functions

std::ostream& operator<< (std::ostream& c , std::pair<int,int> p){
        c << "(" << p.first << ", " << p.second << ")";
        return c;
}

std::ostream& operator<< (std::ostream& c , node* p){
        c << p->data << " [" << p->max_right << "]";
        return c;
}

void print_pair (optional<pair<int,int>> opt){
        if(opt.has_value())
            cout << opt.value();
        else
            cout << "NULL";
}
    
void inorder(node* ptr){
        if(ptr){
                inorder(ptr->left);
                cout<<ptr->data<<" ";
                inorder(ptr->right);
        }
}

void preorder(node* ptr){
        if(ptr){
                cout<<ptr->data<<" ";
                preorder(ptr->left);
                preorder(ptr->right);
        }
}

void postorder(node* ptr){
        if(ptr){
                preorder(ptr->left);
                preorder(ptr->right);
                cout<<ptr->data<<" ";
        }
}

vector<node*> levelorder(node* rt){
        vector<node*> ans;
        queue<node*> q;
        q.push(rt);
        while(!q.empty()){
                node* curr = q.front();
                cout<<curr->data<<endl;
                ans.push_back(curr);
                q.pop();
                if(curr->left) q.push(curr->left);
                if(curr->right) q.push(curr->right);
        }
        return ans;
}

void print(const string& prefix, node* node, bool isLeft){
	if(node){
        	cout << prefix;
         	cout << (isLeft ? "├──" : "└──" );
         	cout << node<< endl;
         	print( prefix + (isLeft ? "│   " : "    "), node->left, true);
        	print( prefix + (isLeft ? "│   " : "    "), node->right, false);
     	}
}

void print(node* n){
	print("", n, false);
}

node* inorder_successor(node* u){
        if(!u) return nullptr;
        if(u->right){
                u = u->right;
                while(u->left) u = u->left;
                return u;
        }
        while(u->parent and u->parent->right == u)
                u = u->parent;
        return u->parent;
}


//void printTree(node* root, const string& prefix = "", bool isLeft = true) {
//    if (root == nullptr) {
//        return;
//    }
//
//    std::cout << prefix;
//    std::cout << (isLeft ? "├── " : "└── ");
//    std::cout << root->data << std::endl;

//    printTree(root->left, prefix + (isLeft ? "│   " : "    "), true);
//    printTree(root->right, prefix + (isLeft ? "│   " : "    "), false);
//}

//void printTreeStructure(node* root) {
//    if (root == nullptr) {
//        std::cout << "Empty tree" << std::endl;
//    } else {
//        std::cout << "Root" << std::endl;
//        printTree(root, "", false);
//    }
//}
