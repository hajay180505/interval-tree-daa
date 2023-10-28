#pragma once
#include <vector>
#include <string>
#include <optional>
#include <utility>
// using std::experimental::optional

struct node{
        std::pair<int,int> data;
        int max_right;
        node* left, * right, *parent;
        int height();
        int balanceFactor();
};


class interval_tree{

        private:
                bool overlap(std::pair<int,int>,std::pair<int,int>);
                std::optional<std::pair<int,int>> searchQuery(node*,std::pair<int,int> );
                void searchAllQuery(node*, std::pair<int,int> , std::vector<std::pair<int,int>>&);


        public:
                node* ptr;
                node* root;
                int count;

                interval_tree();
                interval_tree(std::pair<int,int> elt);
                node* createNode(std::pair<int,int>);
                void insertRoot(std::pair<int,int> elt);
                void insert(std::pair<int,int> elt);
                node* checkImbalance(const std::vector<node*>&);
                void balance(node*);
                void remove(std::pair<int,int> elt);

                node* LL(node*);
                node* LR(node*);
                node* RL(node*);
                node* RR(node*);

                std::optional < std::pair<int,int> > getOverlap(std::pair<int,int>);
                std::vector<std::pair<int,int>> getAllOverlaps(std::pair<int,int>);
                void updateMaxRight(std::vector<node*>& path) ;

};
void inorder(node*);
void preorder(node*);
void postorder(node*);
std::vector<node*> levelorder(node*);
void print(const std::string& prefix, node* node, bool isLeft);
void print(node* );
node* inorder_successor(node*);
std::ostream& operator<< (std::ostream& , std::pair<int,int> );
//void printTree(node*, const std::string& , bool);
std::ostream& operator<< (std::ostream& c , node* p);
//void printTreeStructure(node*);
void print_pair (std::optional<std::pair<int,int>> );
