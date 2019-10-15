
// ================================================================================
// container
// seq container
//------------------------------------------------------------------------
//methods
c.push_back(); //not valid for forward list and array
c.emplace_back();
//temp object being created and then put into the container
c.push_back(SalesData("name","date"));
//object being created within the container directly
c.emplace_back("name","date");

c.push_front(); //not valid for vector or string
c.emplace_front();

//emplace pass the arg to the constructor to construct the object
//insteand of copy the object
c.emplace(iter,"hansome",1);

//insert supported by vector, deque, list and string
c.insert(iter,v) //insert v before the iterator iter
c.insert(iter,n,v)//insert n elements with value v before iterator iter
c.insert(iter,begin,end) //insert before iterator iter , with iterator.begin() til iterator.end()
c.insert(iter,{1,2,3})

//------------------------------------------------------------------------
//accessing element
c.back() //reference to last element in c,undefined if c empty
c.front() //first 
c[n] //nth , if n is out of index range, would not throw an exception
c.at(n) //if index n is outof range will throw an exception

//------------------------------------------------------------------------
//erase element
//not valid for forward list
c.pop_back() //return void, remove last element in c , undefined if c is empty
//not valid for string and vector
c.pop_front() 
//remove the element denoted by the iterator iter, reunter an iterator
//to the elelemnt after the one being deleted,undefined if iter is end of iter
c.erase(iter) 
c.erease(begin,end) //erase range from iteartor being to end, returns an iterator to the element after the last one was deleted
c.clear() //remove all element and return void

//------------------------------------------------------------------------
//containter adaptor:makes a container acts like stack, queue or priority que
//two constructors
#include <queue> 
#include <stack> 
#include <deque>

A a; //create an empty object
A a(c); //create from a container
//arry and forward_list can not be used as adaptor since all adpators need modify the container
//get access to the last element
-stack:any of the remaining container
-queue:list or deque but not vector(since can not push_front)
#include <deque>
 
int main()
{
    // Create a deque containing integers
    std::deque<int> d = {7, 5, 16, 8};
 
    // Add an integer to the beginning and end of the deque
    d.push_front(13);
    d.push_back(25);
    auto f = d.front();
    d.pop_front();
    auto b = d.back();
    d.pop_back();

    // Iterate and print values of deque
    for(int n : d) {
        std::cout << n << '\n';
    }
}




-priority_queue: only vector or a deque, require random access//pop();front();back();top();push()
stack<int> intStack;//pop();push();emplace(args);top()


//------------------------------------------------------------------------
//additianal string operation
string s(cp,n); //copy the first n char in the array that cp points to 
string s(s2,pos2); //copy from s2 start at pos2
string s(s2,pos2,len2); //copy from s2 start at pos2 len2 chars,regardless of len2 copy max:s2.size() - pos2

//substring
s.substr(pos,n) //return a string cotains n char from s ,start at pos(0 default),n(default to the end of the string)
string s("hello world");
string s2 = s.substr(0,5); //s2 = hello
string s2 = s.substr(6); //s3 = world
string s2 = s.substr(6,11);//s3 = world
string s2 = s.substr(12); //out of range exception

//operation to modify string
s.insert(pos,args); //insert chars specified by args, pos can be index or iterator
s.erease(pos, len); //remove len chars start at pos,if len is omitted remove chars from pos to end
s.append(args); // append to the end of the string and return a reference to s
s.replace(range,args); //remove char in range and replaced with args, range can be (index, len) or (iter1,iter2)

//string search find will return string::npos if not find
s.find(args); //args can be a substring, return the index of the first occurance
s.rfind(args); //find the last occurance
s.find_first_of(args); //find the first occurance of any char in args
s.find_last_of(args); //find the last occurance of any char in args
s.find_first_not_of(args); //find the first occurance of not of any char in args
s.find_last_not_of(args); //find the last occurance of not of any char in args

//string comp
s1.compare(s2);
s1.compare(pos1,n1,s2); //comp pos1 n1 char from s1 to s2
s1.compare(pos1,n1,s2,pos2,n2); //comp pos1 n1 char from s1 to pos2 to n2 from s2
s1.compare(cp);//cp:null terminated array
s1.compare(pos1,n1,cp);
s1.compare(pos1,n1,cp,n2);

//------------------------------------------------------------------------
// slice(indx_start,indx_end, step)
#include <valarray>
std::valarray<int> foo (12);
for (int i=0; i<12; ++i) foo[i]=i;
foo[slice(1,3,1)];// return a slice of the object



//------------------------------------------------------------------------
// **********************************************************************
//------------------------------------------------------------------------
// associated container
//Associate container:differ in 3 ways
#include <map>
#include <set>
/*-set or map
-unique or multiple keys(multi)
-store elements in order or not(unordered)
*/

//define a associated container
map<string, string> authors = {{"erik","sophie"},
                               {"james","tom"},
                               {"jerry","amy"}};

//init a set
set<int> iset(ivec.cbegin(), ivec.cend());//init from a vector of int
multiset<int> miset(ivec.cbegin(),ivec.cend()); //can have repeatition

//key will be sorted in the ordered container
//for ordered container , key type must define a way to compare uinsg < bydefault
//else need to pass a functin pointer as well as function constructor into the container
class Erik {
    public:
        explicit erik()= default;
        Erik(int i):num_(i){};
        int get() const {return num_;};
    private:
        int num_;
        //friend bool operator<(const erik& rhs, const erik& lhs){ return rhs.num_ < lhs.num_; };
};

bool CompErik(const Erik& rhs,const Erik& lhs){
    return rhs.get() < lhs.get();
}

std::ostream& operator<<(std::ostream& ostr,  const set<Erik,decltype(&CompErik)> set2){
    for (auto &i : set2)
        ostr << " " << i.get();
    return ostr;
}

int main() {
    set<erik,decltype(&CompErik)> set2(&CompErik); //pass a function pointer of the comp function
    set2={Erik(100),Erik(3),Erik(2)}; //the set will be ordered according to the comp func
    cout << set2 <<'\n';
    set2.insert(Erik(1)); //after insert new element , set will still be ordered
    cout << set2 <<'\n';
}

//pair
#include <utility>
//pair will call the defualt constructor to init its member if not specified
pair<string,string> author{"erik","james"};
make_pair(v1,v2); //return a pair init from v1 and v2, type inferred from v1 and v2
p.first;p.second //return 1 and 2 memeber of pair
p1< p2;//dict order ,compare first ,if first equal compare second

//operation on Associate Containers
set<string>::value_type v1; //string for set same for key_type
set<string>::key_type v1; //same as above
map<string,int>::value_type v1; //pair of <const string,int>
map<string,int>::key_type v1; //string
map<string,int>::mapped_type v1; //int

//iterators for associated container
//when dereference an iter will get refer to the value_type of the container
auto map_it = word_count.begin();
cout< <map_it->first;
map_it->first = "new one"//error since key is const
++map_it->second = "new one"//okay we can change values

//sets iterator is read only since it is key_type and is const


//algorithm since, the first element in the associated container is constant
//generic algorithm that require write to the element would not workd like reorder
//generic ablgorithm would work for 


//adding elements
//since map and set has unique key ,if duplicate key has been
//inserted will have no effect
//set
vector<int> ivec ={2,3,4,5,6,8};
set<int> set2;
set2.insert(ivec.cbegin(),ivec.cend());
set2.insert({1,2,3,4});

//map:need to insert a pair
word_count.insert({word,1}); //easiest:will not override existing key 
word_count.insert(make_pair({word,1}));
word_cout.emplace(key,value);//will only insert key value pair if key does not exists
word_count[key] = value; //will create key value pair if key does not exits else will override existing one
word_count[key]; //if key exits will return its value but if key does not exits , will create default value for this key

//for single value insertion for unique map and set
//insert() emplace() will return pair{iter,bool}
//bool indicate whether insertion successful, not such key exits will be true, else false
//iter will points to the elements inserted or existing elements
auto ret = word_count.insert({word,1});
if(!ret.second) //if world already in the map
    ++(ret.first->second); //iter points to the location contains that key increments counts

while (cin << word) //if key not exists insert with value 0 else , increase existing key count
    ++word_count.insert({word,1}).first->second; //word_count[word]++

//add elements in multisets or multimaps
//since key does not have to be unique insert will always insert new elements
multimap<string, string> authors;
authors.insert({"erik","Man and Sea"});
authors.insert({"erik","Universe and power"});

//erase elements
int num = c.erease(k); //erease all the keys and its values return number of keys removed
//p must be an iterator as in c but not c.end(), erease the the element at the iterator
//return the iterator after the ereased elelemnt
auto iter = c.erease(p); 

//subscribe(not for set since there is no value associated with the key
//subscribtion is meaningless,) no subscribtion for multiset/multimap
word_count["Anna"] =1;//if Anna does not exits will create Anna and assign value 1
word_count.at("Anna"); //check if given key exits , if not throw out of range exception
word_count["Anna"]++;//return a lvalue

set<int> iset = {0,1,2,3,4,5};
iset.count(1); //return 1
iset.count(11); //return 0

//if want to find an element without side effect can use find
//multip map/set will have the same repeated key adjacent to each other
//lower_bound()/upper_bound only for ordered container
auto iter = word_count.find("ammy");//return iterator to the first element equal to the key
size_t freq = c.count;
auto iter = c.lower_bound(k); //return iterator of first element that is the not less than k( >=k) 
auto iter = c.upper_bound(k); //return iterator of first element that is greater than k( >k)
auto p = c.equal_range(k); //reutns a pair of iterators denoteing elements with key k

//find all the books for a particular author
string search_item("Ellen");
auto num = authors.count("Ellen");
auto iter = authors.find("Ellen");
while(num--)
    cout<<(iter++)->second<<endl;

//another way to do same thing using iterator
//lower_bound() returns the first element equal to the k
//upper_bound() returns the one elment past the last occurance of k 
//if k not exists then lower_bound() == upper_bound()
for(auto beg = authors.lower_bound(search_item),
        end = authors.upper_bound(search_item);
        beg != end;++beg)
    cout<< beg->second<<endl;

//use equal_range()
//will return a pair of iterator with first ocurrance and one poast last 
//ocurrance of the key
for(auto pos = authors.equal_range(search_item);
        pos.first != pos.second;++pos.first) 
    cout<<pos.first->second <<endl;

//------------------------------------------------------------------------
//unordered associated container




// ================================================================================
// algorithm
#include <algorithm>


// find max element in stl container
static bool abs_compare(int a, int b){
    return (std::abs(a) < std::abs(b));
}
 
int main(){
    std::vector<int> v{ 3, 1, -14, 1, 5, 9 }; 
    auto result = std::max_element(v.begin(), v.end());
    result = std::max_element(v.begin(), v.end(), abs_compare);
}


// accumulate
/* iter_start, iter_end, init_value , binary operation function object
   The binary operator takes the current accumulation value a (initialized to init)
   and the value of the current element b.
*/
int product = std::accumulate(v.begin(), v.end(), 1, my_function);
int product = std::accumulate(v.begin(), v.end(), 1, my_class()); // define operator() in class



// lower_bound
/* lower_bound(iter_start, iter_end, value, comp)
   iterators defining the partially-ordered range to examine
   value to compare and the binary compare function
   Returns: Iterator pointing to the first element that is not less 
   than value, or last if no such element is found for lower_bound
   upper_bound returns iter to the first element that is greater
*/
std::vector<int> data = { 1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6 };
auto lower = std::lower_bound(data.begin(), data.end(), 4);
auto upper = std::upper_bound(data.begin(), data.end(), 4);


/* distance
   requries at least an input iterator return the number of increament
   from the start to the end iter
*/
// next
/* takes a forward iterator and ,advance the iterator by the given value
 */
auto midpoint = std::next(v.begin(), std::distance(v.begin(), v.end()) / 2);
std::advance(it, n); // will advance iterater passed in by n times


// copy
// Returns : Output iterator to the element in the destination range,
//           one past the last element copied.
std::copy(to_vector.begin(), to_vector.end(),
              std::ostream_iterator<int>(std::cout, " "));

std::copy(from_vector.begin(), from_vector.end(),
          std::back_inserter(to_vector));

// will only copy element that the predicate evaluate to true
OutputIt copy_if(InputIt first, InputIt last, 
                 OutputIt d_first, UnaryPredicate pred)


// for_each(iter_start, iter_end,my_function)
// will call function on each of the elemnt within the range
void displayAsInstruction(int number) {}
    if (number > 0)
        std::cout << '+' << number << '\n';
    else if (number == 0)
        std::cout << "nop" << '\n';
    else if (number < 0)
        std::cout << number << '\n';
}

// better than a long for loop
std::for_each(begin(numbers), end(numbers), displayAsInstruction);

// use a class for accumulator result 
class S {
public:
    static int total_;
    
    void operator()(int a ) {
        total_ += a;
        cout << a << endl;
    }
};
int S::total_ = 0;
// S() will return the function object taht operator() defines in S
std::for_each(v.begin(), v.end(), S());
cout << S::total_ << endl; // will print out the accum sum of element in v


// tranform(iter_start , iter_end, iter_dest, my_function)
// will iterate throug the given range and apply the uniary function to each
// element and wirte to the dest iterator

// back_inserter(container)
// takes container that support push back
// returns A std::back_insert_iterator which can be used to add 
// elements to the end of the container c
char to_upper(char value) {
    return std::toupper(value);
}

std::string s = "hello word";
std::string upper;
// std::transform adds to third iterator.
std::transform(s.begin(), s.end(), std::back_inserter(upper), to_upper);


//find_if()
//third arg is a predicate which would apply to each elememnt
//will return the first elelemnts which predicates evaluate to true
//or end of iterator if not find
auto result = find_if(c.begin(), c.end(),func);

// ---------------------------------------------------------------------------
// good example of make a newline separte words file
// print out only words that are in the dictionary into a space
// separated string
#include <fstream>
#include <iterator>

string file_name = "words.txt";
std::ifstream inf(file_name, std::ifstream::in);
if(! inf){ cout << "Can not open file\n";}

std::istream_iterator<string> it_start(inf);
std::istream_iterator<string>  it_end;

set<string> dict{"good", "bad","cool"};
std::ostream_iterator<string> output{cout , " "};
copy_if(it_start,it_end, output,
       [&dict](auto x){return dict.count(x) != 0;});

// ---------------------------------------------------------------------------
using namespace std;
// lambda
//capture list is a list of local variables defined in the enclosing function
//we can ommit either or both of the return type and parameter list, but not 
//capture list and function body 
[capture list] (parameter list) -> return type {function body};
stable_sort(words.begin(),words.end(),
        [val1,val2,val3](const string& a, const string& b){return a.size() < b.size();});

//wil provide additional parameter through capture local function variables 
//will give more flexibility given find_if predicate take only one parameter
auto wc = find_if(words.begin(),words.end(),
        [sz] (const string &a){return a.size)() >= sz;});

//will operate on each of the element from the input range
//according to the callable object
//could mix implicit and explicit capture but must start with & or =
//e.g.[=,&os]
for_each(wc,words.end(),
        [](const string& s){std::cout << s << " ";});

//lambda function will infer the return type if the body of the function
//contains only return statement
transform(v1.begine(),v1.end(),v1.begine(), //OKAY can infer the return type
        [](int i) {return i < 0? -i :i;});

//lambda will return void, since return is not the only statement in the body
//but actually it will return a value ,some compile error
transform(v1.begine(),v1.end(),v1.begine(), //not okay 
        [](int i) {if(i<0) return -i; else return i;}); //

transform(v1.begine(),v1.end(),v1.begine(), //not okay 
        [](int i) -> int {if(i<0) return -i; else return i;}); //okay explicit return type


//unique:removing adjacent element
// given a sorted range 
// Returns: Forward iterator to the new end of the range
unique(beg,end);//use default == to compare element
unique(beg,end,comp);//use comp to compae element

//reverse
reverse(beg,end); //reverse in place
reverse(beg,end,dest); //make reverse copy into dest

//remove
remove_if(v1.begin(),v1.end(), //remove the even number
                [](int i){return i % 2});
remove_copy_if(v1.begin(),v1.end(),//copy even from v1 to v2
    back_inserter(v2),[](int i){return i % 2});

//replace
replace(beg,end,old_val,new_val);//replace old val with new
replace_if(beg,end,pred,new_val);//apply predit to each item if evaluate true replace with new_val
replace_copy_if(beg,end,dest,pred,new_val);//copy to another vector 


// ---------------------------------------------------------------------------
//container specific algorithm:list and forward_list
lst.merge(lst2); //merge elements from lst1 to lst2, both should be sorted
lst.merge(lst2.comp); //using comp to compare element in lst1 and lst2
lst.remove(val); //remove all occurance of val
lst.reverse();
lst.sort(); //using default < for compare
lst.sort(comp); //using comp predicate for compare
lst.unique();//call erease to remove consecutive copies of the same value
lst.unique(comp);//using comp to compare instead of ==

lst1.splice(p,lst2);//insert all lst2 one position before p in list1, list2 will be empty
lst1.splice(p,lst2,p2);//insert element in p2 in list2 into position before p in lst1 
lst1.splice(p,lst2,b,e);//insert the range denote in list2 to the position before p in list1

//========================================================================
//IO
https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
//read file
if(auto in = std::ifstream("data.in");in) { //in here like for loop stop on condition false
    for(auto i = 0;in >> i;) { // read tokene by token 
        std::cout << i << '\n'; 
    }
}

//write file 
std::ofstream fout("data.out");
fout << i;
fout.close();

//get line
https://en.cppreference.com/w/cpp/string/basic_string/getline
//input:stream to get data, str:string to store data , dilimiter optional
getline(input, str, input.widen('\n'))

//condition state
//if iosstream fail the subsequent stream will fail
int ival;
cin >> ival; //if entry 'a' then error

//will return an iostate bits pattern 
while(cin >> word)
    //read successfully

cout <<"hello"<<endl; //endl will cause outstream buffer to flush

//when input stream is tied to an ouputstream, any attempt to read the input
//stream will cause the output stream to flush

#include <fstream>
//File input and output
//ifstream:to read from a file
//ofstream:to write to a file
//fstream:to read from or write to a file
//specific operation
fstream fstrm; //create an unbound file stream
fstream fstrm(s); //create a fstream and open the file s,the default mode depend on fstream
fstream sftrm(s,mode); //open with the mode
fstrm.open(s);
fstrm.open(s,mode);
fstrm.close(); //if the object is outof scope the file will be close when object destroyed
fstrm.is_open();

//using file stream objects
//read a file ,we define a file stream object and associate that object with the file
ifstream in(ifile); //construct the ifstream and open the file
ofstream out; //output file stream that is not bond to any file

//io stream can not be copied so need to pass in and out by reference

//file modes
ios_base::in;//input
ios_base::out;//output
ios_base::app;//append, seek to the end before any write, when turnc is not
ios_base::ate;//seek to the end immediately after open
ios_base::trunc; //truncate the file , output stream will use as default
ios_base::binary; //Do IO in binary mode 

ofstream out("file"); //default output and trucate
ofstream out("file2", ios_base::app); //output mode is implicit
ofstream out("file2", ios_base::app | ios_base::out); //output mode is explicit

#include <sstream>
//string streams
//istringstream:read a string as input stream
//ostringstream:write a string as ouputstream
//stringstring:read and write the string
sstream strm;
sstream strm(s); //strm is a sstream object that holds a copy of string s
strm.str(); //returns a copy of the string that strm holds
strm.str(s); //copy s into strm and return void

std::getline(inputstream,buff,delimitor);
// e.g.
string buff{"really,good,one"};
std::istringstream iss{buff};
string temp;
while(std::getline(iss,temp,',')) {cout << temp << endl;}

// --------------------------------------------------------------------
// example use of stringstream
istringstream iss(string s); //take a string to input stream
string temp;
while(iss >> temp ) { cout << temp << endl;}

// if want to use iterators
// can ot use iss again here since it is a one pass input iterator
// will delimit by space by default
istringstream iss2(string s); //take a string to input stream

std::istream_iterator<string> start{iss2};
std::istream_iterator<string> end;
std::ostream_iterator<string> out{cout, "--"}; // output iterator bonds to cout with delimitor

copy(start, end, out); // will iterate through the input iterator and show on the ouput with delimiter

// use of ostringstream
std::ostringstream oss;
oss << "item1" << " ";
oss << "item2" << " ";

cout << oss.str() << endl;

// use of itertor for IO stream
copy(istream_iterator<int>{cin}, istream_iterator<int>{},
        ostream_iterator<int>{cout,"---"});

// a split function example
// given a string and a string delimitor
// parse accodint to the delim and save into a vector
vector<string> Split(string s, string& delim){
    vector<string> result;
    size_t pos = 0;

    while((pos = s.find(delim)) != string::npos) {
        auto token = s.substr(0,pos);
        result.push_back(token);
        s = s.substr(pos + delim.size());
    }
    result.push_back(s);
    return result;
}

int main() {
    string buff = "really--good--one";
    string delim = "+";

    auto v = Split(buff,delim);
    std::ostream_iterator<string> oss(cout," ");
    copy(v.begin(),v.end(),oss);
}

//========================================================================








