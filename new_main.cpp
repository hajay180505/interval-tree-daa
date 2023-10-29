#include <iostream>
#include "interval_tree.h"
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
        if(! tree.getOverlap(x))
            tree.insert(x);
    }

    print(tree.root);

    vector<string> names = {
        "Albert","Anthony","Alissa",
        "Bob","Benjamin","Clara",
        "Dennis","Elanor","George",
        "Jack","John","Tiffany",
        "Timothy","Kate","Mark",
    };

    interval_tree nueva(make_pair(0,6),{"John","Jack"});

    array<pair<int,int>,6> list = {
        make_pair(5, 9), make_pair(7, 8),
        make_pair(9,12), make_pair(11, 13), 
        make_pair(6, 20), make_pair(18,22)
    };

    nueva.insert(list[0], {"Albert","Kate"});
    nueva.insert(list[1], {"Robert","Benjamin"});
    nueva.insert(list[2], {"Alissa","Mark"});
    nueva.insert(list[3], {"Tiffany","Jack"});
    nueva.insert(list[4], {"Anthony","Alissa"});
    nueva.insert(list[5], {"Timothy","Kate"});

    print(nueva.root);

    cout<<"Overlaps : " <<nueva.getAllOverlaps(make_pair(3,10))<<endl;

    auto x = nueva.freePeople(make_pair(3,10),names);
    cout<<"Free people : ";
    for(auto i :x) cout<<i<< " ";
    cout<<endl;
    return 0;

}

