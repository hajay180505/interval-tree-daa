#include "avl.h"
#include "avl.cpp"
#include <utility>
using namespace std;

int main(){

    avl tree(make_pair(4,5));
    pair<int,int> p(1,2);
    for(int i=2;i<10;i++)
        tree.insert(p);
    print(tree.root);

    for(int i=10;i>1;i--){
        tree.remove(p);
        print(tree.root);
    }
    return 0;

}
