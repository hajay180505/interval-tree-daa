#include "interval_tree.h"
#include <iostream>
#include <utility>
#include <array>
using namespace std;




int main(){

    interval_tree tree(make_pair(0,6));

    array<pair<int,int>,6> ints = {
        make_pair(5, 9), make_pair(7, 8),
        make_pair(9,12), make_pair(11, 13), 
        make_pair(6, 20), make_pair(18,22)
    };


    for (auto x : ints){
	//cout<<"Inserting "<< x<<endl;
        tree.insert(x);
    	//print(tree.root);
	//cout<<endl;
    }

    print(tree.root);
    	
    tree.remove(make_pair(9,12));
    print(tree.root);

    tree.remove(make_pair(5,9));
    print(tree.root);

    tree.remove(make_pair(6,20));
    print(tree.root);

    tree.remove(make_pair(0,6));
    print(tree.root);

    array<pair<int,int>,5> intervals = {
        make_pair(5,11),
        make_pair(4,8),
        make_pair(17,19),
        make_pair(15,18),
        make_pair(21,23)
    };

    interval_tree it;
    it.insertRoot( make_pair(7,10));

    for (auto x : intervals){
    	it.insert(x);
    }

    cout<<"New :"<<endl;

    print(it.root);

    cout<<"20,22 : " << it.getOverlap(make_pair(20,22)).value_or(make_pair(0,0)) << endl;

    cout<<"24,25 : " << it.getOverlap(make_pair(24,25)).value_or(make_pair(0,0)) << endl;

    cout<<"Inserting 24,24"<<endl;
    it.insert(make_pair(24,24));

    cout<<"24,25 : " << it.getOverlap(make_pair(24,25)).value_or(make_pair(0,0)) << endl;

    cout<<"5,9 : " << it.getOverlap(make_pair(5,9)).value_or(make_pair(0,0)) << endl;

    cout<<"16,17 : " << it.getOverlap(make_pair(16,17)).value_or(make_pair(0,0)) << endl;

    cout<<"Deleting 15,18"<<endl;
    it.remove(make_pair(15,18));

    cout<<"16,17 : " << it.getOverlap(make_pair(16,17)).value_or(make_pair(0,0)) << endl;

    cout<<"0,3 : " << it.getOverlap(make_pair(0,3)).value_or(make_pair(0,0)) << endl;
      

}
