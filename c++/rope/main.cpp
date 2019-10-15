#include "rope.h"

#include <iostream>

using namespace std;

int main()
{
    vector<string> v{"good","job"};
    Rope r{v};

    for(auto it = r.cbegin();it != r.cend();++it){
        //*it = 'c';
        cout << *it << endl;
    }
}
