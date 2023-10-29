#pragma once
#include <vector>
#include <string>
#include <optional>
#include <utility>

struct node{
        std::pair<int,int> data;
        std::vector<std::string> people ;
        int max_right;
        node* left, * right, *parent;

        int height();
        int balanceFactor();
        node();
        node(std::pair<int,int>);
        node(std::pair<int,int>, std::vector<std::string>);
};


class interval_tree{

        private:
                bool overlap(std::pair<int,int>,std::pair<int,int>);
                std::optional<node*> searchQuery(node*,std::pair<int,int> );
                void searchAllQuery(node*, std::pair<int,int> , std::vector<node*>&);


        public:
                node* ptr;
                node* root;
                int count;

                interval_tree();
                interval_tree(std::pair<int,int> );
                interval_tree(std::pair<int,int> elt, std::vector<std::string>);

                node* createNode(std::pair<int,int>);
                node* createNode(std::pair<int,int>, std::vector<std::string>);

                void insertRoot(std::pair<int,int> );
                void insertRoot(std::pair<int,int> elt,std::vector<std::string>);

                void insert(std::pair<int,int> );
                void insert(std::pair<int,int> , std::vector<std::string>);


                node* checkImbalance(const std::vector<node*>&);
                void balance(node*);
                void remove(std::pair<int,int> );

                node* LL(node*);
                node* LR(node*);
                node* RL(node*);
                node* RR(node*);

                std::optional <node*> getOverlap(std::pair<int,int>);
                std::vector<node*> getAllOverlaps(std::pair<int,int>);
                void updateMaxRight(std::vector<node*>& ) ;
                std::vector<std::string> freePeople(std::pair<int,int>,std::vector<std::string>);


};
//traversals

void inorder(node*);
void preorder(node*);
void postorder(node*);
std::vector<node*> levelorder(node*);
node* inorder_successor(node*);

//printing tree

void print(const std::string& , node* , bool );
void print(node* );

//overloads for <<

std::ostream& operator<< (std::ostream& , std::pair<int,int> );
std::ostream& operator<< (std::ostream&  , node* );
std::ostream& operator<< (std::ostream&, std::optional<node*>);
std::ostream& operator<< (std::ostream& , std::vector<node*>);
