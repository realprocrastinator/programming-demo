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

// Your code here
struct Bid {
    uint64_t id = 0; 
    uint64_t price = 0;
    uint64_t qty = 0; 
    uint64_t time = 0; 
};

struct CompS{
    bool operator()(const Bid& a, const Bid& b){
        return a.time < b.time;
    }
};

struct CompQ{
    bool operator()(const Bid& a, const Bid& b){
        if(a.price == b.price) return a.time > b.time; // check here
        return a.price < b.price;
    }
};

class Auction{
    public:
        Auction(uint64_t total):total_sell_{total}{}
       
        // take the bids according to the priority of price-time
        void TakeBid(const Bid& b){
            //cout << b.qty << " " << total_sell_ << endl;
            if(total_sell_ >= b.qty) {// fully excuited the bid
                total_sell_ -= b.qty;
                full_.insert(b);
                //cout << "full" << endl;
            }else if(total_sell_ == 0){
                none_.insert(b);
            }else if(total_sell_ < b.qty){
                total_sell_ = 0; // excute the rest of total sell
                partial_.insert(b);
            }
        }
    
        friend ostream& operator<<(ostream& os,const Auction& A){
            if(!A.full_.empty()) {
                os << "FULLEXECUTION" << endl;
                for(auto it = A.full_.begin();it!= A.full_.end();++it){
                    os << (*it).id << endl;
                }
            }
          
            if(!A.partial_.empty()) {
                os << "PARTIALEXECUTION" << endl;
                for(auto it = A.partial_.begin();it!= A.partial_.end();++it){
                    os << (*it).id << endl;
                }
            }

            if(!A.none_.empty()){
                os << "NOEXECUTION" << endl;
                for(auto it = A.none_.begin();it!= A.none_.end();++it){
                    os << (*it).id << endl;
                }
            }
           
           return os; 
        }
    
    private:
        uint64_t total_sell_;
        set<Bid,CompS> full_;
        set<Bid,CompS> partial_;
        set<Bid,CompS> none_;
};


std::vector<std::string> split(const std::string& line, const char delimiter = ',') 
{
    std::vector<std::string> result;
    auto current_begin = line.begin();
    auto iter = line.begin();
    while (iter != line.end()) 
    {
        if (*iter == delimiter) 
        {
            result.emplace_back(current_begin, iter);
            ++iter;
            current_begin = iter;
        } 
        else 
        {
            ++iter;
        }
    }
    
    if (current_begin != iter) 
    {
        result.emplace_back(current_begin, iter);
    }
    
    return result;
};

int main() 
{
    // Parsing has been provided. Feel free to modify this function.
    uint64_t item_count;
    uint64_t bid_count;
 
    cin >> item_count;
    cin >> bid_count;
    
    
    // -------------------------
    // make a priority que of the bids
    priority_queue<Bid,vector<Bid>,CompQ> pq;
 
    for (size_t i = 0; i < bid_count; ++i)
    {
        string bid_str;
        cin >> bid_str;
        auto bid_str_vec = split(bid_str);
        
        uint64_t bid_id = stoll(bid_str_vec[0]);
        uint64_t bid_price = stoll(bid_str_vec[1]);
        uint64_t bid_quantity = stoll(bid_str_vec[2]);
        uint64_t bid_receive_time = stoll(bid_str_vec[3]);
        
        Bid b;
        b.id = bid_id;
        b.price = bid_price;
        b.qty = bid_quantity;
        b.time = bid_receive_time;
    
        // Call your code here
        pq.push(b);

    }
    
    // Call your code here
    Auction A{item_count}; // init the auction with total sell
    
    while(!pq.empty()){
        auto b = pq.top();
        pq.pop();
        A.TakeBid(b);
    }
    
    cout << A;
    return 0;
}
