#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <memory>

using namespace std;

pair<int,int> BestDeal(const vector<int>& v){
    int max_diff = 0;
    int max_seen = 0;
    int count = v.size() - 1;
    int max_ind = -1;
    int min_ind = -1;

    for(auto it = v.rbegin(); it != v.rend();++it){
        if(*it > max_seen) { // we seen a bigger number
            max_seen = *it;
            max_ind = count;
        }else{
            int diff = max_seen - *it;
            if(diff > max_diff) {
                max_diff = diff;
                min_ind = count;
            }
        }
        --count;
    }
    return {min_ind,max_ind};
}

#include <iterator>
string Parse(string& s, char delimit){

    // special case where there is delimiter at the beginning of the string
    int flag_start = s[0] == delimit ? 1 : 0;
    int flag_end = s[s.size()-1] == delimit ? 1 : 0;

    for(auto it = s.begin(); it < s.end();){
        if(*it == delimit) { // if find delimiter
            // erase the delimiter unless it is non consecutive
            if(!(it != s.begin() && it+1 != s.end() 
                && *(it-1) != delimit &&  *(it+1) != delimit)){
                it = s.erase(it);
            }
            else{
                ++it;
            }
        }else{
            ++it;
        }
    }

    // check sepcail case
    //if(flag_start) s.insert(0,std::string(1,delimit)); 
    if(flag_start) s.insert(0,1,delimit); 
    if(flag_end) s += delimit; 

    return s;
}


int main(){
    string s = "...hello.....  world.. there.is.you..!.";
    cout << s << endl;
    auto result = Parse(s,'.');
    cout << s << endl;

    //auto result = Parse(s,'.');
    //cout << result  << endl;


    /*
    vector<int> v{2,5,6,3,10,1};
    vector<int> v2{4,3,2,1};
    
    auto result = BestDeal(v);
    auto result2 = BestDeal(v2);
    cout << result2.first <<" " <<result2.second<< endl;
    //cout << result2 << endl;
    */

    return 0;
}


