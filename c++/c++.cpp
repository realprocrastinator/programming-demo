//=================================================================
//Debugging
//GDB Debugging 
https://www.youtube.com/watch?v=J7L2x1ATOgk

//c++ cheat sheet
https://github.com/mortennobel/cpp-cheatsheet
//=================================================================
//header guard
https://www.learncpp.com/cpp-tutorial/header-guards/

//scope:
https://www.geeksforgeeks.org/scope-of-variables-in-c/

// constructor call another constructor
https://hownot2code.com/2016/06/09/how-to-properly-call-one-constructor-from-another/

//=================================================================
//top  & bottom constant
//top-level const to indicate that the pointer itself is a const
//When a pointer can point to a const object, we refer to that const as a low level const.
int i = 0;
int *const p1 = &i; // we can't change the value of p1; const is top-level
const int ci = 42; // we cannot change ci; const is top-level
const int *p2 = &ci; // we can change p2; const is low-level
const int *const p3 = p2; // right most const is top-level, left-most is not
const int &r = ci; // const in reference type is always low-level


//=================================================================
//bazel build works
//One build file per folder
//Multiple rules for each build file
//Each build rule would have
//Name
//list of sources
//list of headers
//list of dependencies
//Refer to build rule by //path/to/dir:<name> // refers to the root of the project

//lib can only have one source and one header file
//can not run by itselfs and is depend on other code
cc_library(
 name = "hello_world",
 srcs = ["hello_world.cpp"],
 hdrs = ["hello_world.h"],
 deps = []
)

cc_library(
 name = "printer",
 srcs = ["printer.cpp"]
 hdrs = ["printer.h"],
 deps = [
 // If it's declared within the same build
 // file, we can skip the directory
 ":hello_world"
 ]
)

//source must have main function, no header , can not be tested
cc_binary(
 name = "main"
 srcs = ["main.cpp"],
 deps = [
 "//path/to:hello_world"
 ]

//symetic different to cc_binary, run as test
cc_test(
    name = "factorial_test",
    srcs = ["factorial_test.cpp"],
    deps = [
        ":factorial_lib",
        "//:catch",
    ],
)

//cavet for bazel 
//run bazel in a different dir if need to refer to other files in other dir need
//to specify in the data

//clion only needs the rules when you sync the project
//bazel->sync->sync project

//========================================================================
//containter
//seq containter

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
A a; //create an empty object
A a(c); //create from a container
//arry and forward_list can not be used as adaptor since all adpators need modify the container
//get access to the last element
-stack:any of the remaining container
-queue:list or deque but not vector(since can not push_front)
-priority_queue: only vector or a deque, require random access//pop();front();back();top();push()
stack<int> intStack;//pop();push();emplace(args);top()


//------------------------------------------------------------------------
//additianal string operation
string s(cp,n); //copy the first n char in the array that cp points to 
string s(s2,pos2); //copy from s2 start at pos2
string s(s2,pos2,len2); //copy from s2 start at pos2 len2 chars,regardless of len2 copy max:s2.size() - pos2

//substring
s.substring(pos,n) //return a string cotains n char from s ,start at pos(0 default),n(default to the end of the string)
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
//Associate container:differ in 3 ways
#include <map>
#include <set>
/*-set or map
-unique or multiple keys(multi)
-store elements in order or not(unordered)*/

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
cout<<map_it->first;
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
        pos.first != post.second;++pos.first) 
    cout<<pos.first->second <<endl;

//------------------------------------------------------------------------
//unordered associated container

//========================================================================
//algorithm
//passing a function to an Algorithm
//predicates: take one arg or two args apply on the elements as condition
//elements type should be able to convert to predicates parameters types
bool isShorter(const string& s1, const string& s2){
    return s1.size() < s2.size();
}
stable_sort(words.begin(),words.end(),isShorter); //stable sort will keep original order if equal

//find_if()
//third arg is a predicate which would apply to each elememnt
//will return the first elelemnts which predicates evaluate to true
//or end of iterator if not find
auto result = find_if(c.begin(), c.end(),func);


//lambda
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


//copy
//copy take 3 args:inputer iterator start,input iterator end,output iterator for the copy
//will iterate the input iterator and output interator at the same time deference read and then write
//copy(in_iter.begin(),in_iter.end(),out.begin()) //for out could specify where want to insert
//if want to append to the end of the out_iter, do not use out.end(), since deference it would
//result in undefined behavior
//inserter will return a inserter iterator that allows insertion into the container
//same for back_inserter
//returns An iterator to the end of the destination range where elements have been copied.
std::copy (std::istream_iterator<std::string>(f) ,{},std::inserter(lexicon,lexicon.end()));
if(f.bad()){
    Error("I/O error while reading");
}
/*note if there is reference points to the begining of the out_iter, after copy, since inserter would 
 * inster at the end of the out_iter and results in deallocation and reallocation of the space for 
 * the whole containiner and this would results in the initial out_iter.begin() reference is invalid
 * Different iterator has different time when the itearator is invalidated.
 * Depends of the iterator,i.e. if vector it will be always be invalidated , but for linked list
 * it is always validated
 */

//--------------------------------------------------------------------------
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
ofstream::in;//input
ofstream::out;//output
ofstream::app;//append, seek to the end before any write, when turnc is not
ofstream::ate;//seek to the end immediately after open
ofstream::trunc; //truncate the file , output stream will use as default
ofstream::binary; //Do IO in binary mode 

ofstream out("file"); //default output and trucate
ofstream out("file2", ofstream::app); //output mode is implicit
ofstream out("file2", ofstream::app | ofstream::out); //output mode is explicit

#include <sstream>
//string streams
//istringstream:read a string as input stream
//ostringstream:write a string as ouputstream
//stringstring:read and write the string
sstream strm;
sstream strm(s); //strm is a sstream object that holds a copy of string s
strm.str(); //returns a copy of the string that strm holds
strm.str(s); //copy s into strm and return void






//========================================================================

//-------------------------------------------------------------------------------------------
//type convertion explicit
double pi = 3.14;
int p =(int) pi; //standard c type casting
//e.g. pointer points to 4 bytes cast to content with only 1 byte, 
//when dereferencing will interperate it wrong 
int p = static_cast<int>(pi);//stricker type convertion control 

//iterate through the arrays
std::array<int,3> ages{18,19,20};
//option 1
for(int i = 0; i < ages.size();i++) {
    std::cout << ages[i] << '\n';
}
//option 2
for(auto it = ages.begin(); it != age.end();++it) {
    *it; //iterator as if a pointer , when need to get access to the content dereference
}
//option 3
for (const auto& age:ages) {
    age;
}
// make iterator constat aka can not change the element through the iterator
for(auto it = ages.cbegin(); it != age.cend();++it) {
    (*it)++; //error
}
//reverse iteration
for(auto it = ages.rbegin(); it != age.rend();++it) {
    *it;
}

//different way to random access vector
vector<int> num {1,2,3};
num.at(0); // slower but safer(will do the boundary check)
num[1];
num.capacity();//its capacity before reallocation and expand

//Associate container
std::map<std::string, double> m;
std::pair<std::string, double> p1 {"bat",1.3};

//different way of insertion key value
m.insert(p1);
m.insert({"cat",10.7});
m.emplace("cat",10.5); //will not replace the existing key value pair
m["cat"] = 10.5; //could replace the existing key value pair

//get access 
m["cat"]; //will not through expection when the key does not exits return default type value
if(auto it = m.find("cat") ; m.end()){
    *it = "dog";//element exits and can get access
}

//check if element exists
//return an interator , if is the end then this item does not exits in the container
//else it will return the iteratro that points to that element
auto it = m.find("bat");


//=================================================================
//wk2
//iterator 
//the algorithm just need to be implemented once for the generic opration independant of the
//underlining containter, and the iterator will proivde the API for the algorithm for different containers

int sum = std::accumulate(v.begin(),v.end(),0);
int product = std::accumulate(v.begin(),v.end(),1,std::multiplies<int>());

//not very good choice
auto midpoint = v.begin() + (v.size()/2) //for randome iterator ,since linked list does not have .size()
//std::next will return a iterator that start with the the interator and advance specified steps 
//std::distance returns The number of increments needed to go from first to last
auto midpoint = std::next(v.begin(),std::distance(v.begin(),v.end())/2)//assume container has size
//could sum up element tll midway
int sum = std::accumulated(v.begin(),midpoint, 0);

//general algorithm applied upon different underlining data structures
//e.g. linked list binary search vs vector
std::vector<int> sortV {1,2,3};
std::lower_bound(sortedV.begin(),sortV.end(),5);//do a binary search and return the first value >= the arg

std::list<int> sortL{1,2,3};
std::lower_bound(sortedL.begin(),sortL.end(),5);
//--------------------------------------------------------------------
//contianter mentod reference
http://www.cplusplus.com/reference/stl/
//--------------------------------------------------------------------
//difference between iterators
forward iterator: multi pass iterator meaning it can be dereferenced multiple times

//input iterator
//https://stackoverflow.com/questions/54467575/input-iterator-can-be-read-repeatedly-while-output-iterator-can-only-be-written
value = *inputIt;
value = *inputIt; // OK: input iterator could be dereferenced many times
copyIt = inputIt;
++inputIt;
value = *copyIt;  // Not OK:once input iterator has been incremented all previous copies of iterator will be invalid

//output iterator could only be dereference once
*outputIt = value;//like cout<<value
++outputIt;
*outputIt = value; // OK
*outputIt = value; // Not OK:intuitivley would override the previous written value to std out, but would not

//istream:lke receiver
//They are constructed from a basic_istream object, to which they become associated
int main{
    std::ifstream in{"data.in"};

    std::istream_iterator<int> begin(in);//
    std::istream_iterator<int> end;     //create an end iterator
    std::cout << *begin++ <<std::endl; //read first int ,++ is not requried but compatible with forward iterator
    begin++;//second int
    std::cout << *begin++ <<std::endl; //read third int

    while(begin ! = end){ //keeps printing unti reach the end of the input iterator
        std::cout << *begin++ <<std::endl; //read third int
    }
}

//ostream:like sender
int main {
    std::vector<int> v{1,2,3,4,5};
    std::ostream_iterator<int> os(std::cout, " "); //takes 2 args:iterator,delimitor
    for(const auto& i: v){
        *os = i;//or *os++ = i , I/O stream iterator will incremented automatically after dereferenced
    }
}


//demo of the istream_iterator copy
//istream_iterator will store previous value you read from the stream before any increments as well
//as reference to the input stream(when increament will increament the referenced bing
//inputstream)
http://coliru.stacked-crooked.com/a/3c69009b1c059566

#include <iostream>
#include <iterator>

int main() {
    auto orig = std::istream_iterator<int>(std::cin);
    int a = *orig;  // a = 1

    auto copy = orig; // make a copy
    ++copy; // look at the next value

    int b = *orig;  // b = 1, still, since we haven't incremented it, but
    int c = *copy;  // c = 2, now! (since copy has moved on)

    ++orig;  // orig gets the next value in the stream
    // (note that the '2' has already been read, and no longer exists in the stream)

    int d = *orig;  // d = 3, since that's the next value in the input
    int e = *copy;  // c = 2, still, since we haven't incremented copy
    
    ++copy;         
    int f = *copy;  //f = 4, since 3 has been dereference by orig
    ++orig;         
    int g = *orig;  //g = 5 not 4 ,since 4 has been dereferrenced by copy
    
    std::cout << "a = " << a << "\n"
              << "b = " << b << "\n"
              << "c = " << c << "\n"
              << "d = " << d << "\n"
              << "e = " << e << "\n"
              << "f = " << f << "\n"
              << "g = " << g << "\n";
}




//--------------------------------------------------------------------
//lambda function

//output stream could not be copied
void PrintList(const std::vector<int>& nums,
 std::ostream& os) {
 auto printer = [=] (int value) { os << value << '\n' //erorr
 std::for_each(nums.begin(), nums.end(), printer);
}

//no error but will only operate on the copy of the map
std::map<std::string, int> m;
auto emplace = [=] (const auto& key, const auto& value) { m.emplace(key, value)};
emplace("hello", 5);//m would no change ,only its copy inside the lambda would change 

//Lambda captures - By Value [=] get access to everything
//safe but ,potentially slow, does not work for non-copyable types (eg. ostream, unique pointer)
std::for_each(vec.begin(), vec.end(),[=] (int item) { item += n; });}


//Lambda captures - By reference [&] all outside the scope
auto GetGenerator() {
 int upto = 0;
 return [&] () { return upto++; }
}
// What happens here?
auto fn = GetGenerator(); //no longer valid since the function returned reference to the stack not valid
std::cout << fn() << fn() << '\n';


//--------------------------------------------------------------------
//Catch2 testing
https://github.com/catchorg/Catch2/blob/master/docs/assertions.md#exceptions
SCENARIO("context of this test") {
    GIVEN("a particular test, condition init") {
        //iniit some var here

        /*need to satisfy the condtion in the test*/
        REQUIRE(/*a boolean here for a test case*/);
        REQUIRE(/*a boolean here for a test case*/);

        WHEN("label the code that you run") {
            //run some code here

            THEN("the expectation from the code being tested below") {
                REQUIRE(/*boolean*/);
                REQUIRE(/*boolean*/);
                REQUIRE_THROWS_WITH( expression, string or string matcher ) //given expression , follow by exptected exception string
            }
        }

        WHEN("label the code that you run") {
            //run some code here

            THEN("the expectation from the code being tested below") {
                REQUIRE(/*boolean*/);
                REQUIRE(/*boolean*/);

                AND_THEN("coniniuting on the previous test"){
                    //some code
                    REQUIRE(/*boolean*/);
                }
            }
        }
    }
}


//=================================================================
//wk3
//object constructor could be overloaded
std::vector<int> v11; // will call the 0 arg default constructor
std::vector<int> v51{5, 2}; // Initialiser-list constructor {5, 2}
std::vector<int> v52(5, 2); // Count + value constructor (5 * 2 => {2, 2, 2, 2, 2})
std::vector<int> v52(iter.begin(),iter.end()); //take begin and end iterator  

//same for basic types But the default constructor has to be manually called
//reseason we do not init the var is that we only need to when close to actually use it
int n; // not constructed (memory contains previous value)
int n2{}; // Default constructor (memory contains 0)
int n3{5};
int n5 = 5.5;  // Not so nice. No error cast into int and pass in as arg
int n4{5.5}; //gives error since no constructor match this type

//Noexcept:exceptions are recoverable excpet the critical ones, noexcept tells the complier do
//not try to recover , but fail when there is an exception
//Use noexcept to guarantee that callers needn't worry about exceptionhandling
//construct a destructor , usually by default
class MyClass {
    ~MyClass() noexcept;
}

MyClass::~MyClass() noexcept {
 // Definition here
}

//incomplete types since the definition is recurrsive and size not determined
struct Node {
 int data;
 // Node is incomplete - this is invalid
 // This would also make no sense. What is sizeof(Node)
 Node next;
};
//OK
struct Node {
 int data;
 Node* next;
};

//class access
class Foo {
    public:
     // Members accessible by everyone
     Foo();
    protected:
     // Members accessible by members, friends, and subclasses
     // Will discuss this when we do advanced OOP in future weeks.
    private:
     // Accessible only by members and friends
     void PrivateMemberFunction();
     int private_data_member_;
    public:
     // May define multiple sections of the same name
};

//struct vs class
/*A class and a struct in C++ are almost exactly the same
The only difference is that:
-All members of a struct are public by default
-All members of a class are private by default */


//friends
/*
A class may declare friend functions or classes
Those functions / classes are non-member functions that may access
private parts of the class */

//class scope
Anything declared inside the class needs to be accessed through the scope
of the class

void Foo::MemberFunction() {
 Foo::Age age;
}

//constructor
/*Unless we define our own constructors the compile will declare a default constructor
This is known as the synthesized default constructor
-it is generated for a class only if it declares no constructors:e.g. in the case of class B below
-Cannot be generated when any data members are missing default constructors:e.g. read file class, does not hvae defualt constructor
-its incorrect if some member of built-in types has no in class initialiser;e.g. int j below
*/
class A {
 int a_; //no in-class initialiser
};

class C {
 int i{0}; // in-class initialiser
 int j; // Untouched memory, the default constructor will not init j, since all basic
        //type has to be init manually
 A a;
 // This stops default constructor
 // from being synthesized.
 B b; //since b has specified its constructor and need to init explicitly according to its constructor
};

class B {
 B(int b): b_{b} {}
 int b_;
};

//initialiser list
https://www.learncpp.com/cpp-tutorial/8-5a-constructor-member-initializer-lists/
//the initialiser list has be in the order of the var beling declared within the class
class NoDefault {
    NoDefault(int i);
}
class B {
    // Constructs s_ with value "Hello world"
    B(int& i): s_{"Hello world"}, const_{5}, no_default{i}, ref_{i} {}
    // Doesn't work - constructed in order of member declaration.
    B(int& i): s_{"Hello world"}, const_{5}, ref_{i}, no_default{ref_} {}
    B(int& i) {
    // Constructs s_ with an empty string, then reassigns it to "Hello world"
    // Extra work done (but may be optimised out).
    s_ = "Hello world"; //call the default the constructor first and then assign new value
    // Fails to compile
    const_string_ = "Goodbye world"; //it has already be initialised to empty string can not modify
    ref_ = i; //ref always needs to be initialised
    // This is fine, but it can't construct it initially.
    no_default_ = NoDefault{1};
    }
    std::string s_;
    // All of these will break compilation if you attempt to put them in the body.
    const int const_;
    NoDefault no_default_;
    int& ref_;
};

//static is global defined with this class


//Delegate constructor
/*If the name of the class itself appears as class-or-identifier in the member initializer list, 
 * then the list must consist of that one member initializer only; 
 * such constructor is known as the delegating constructor, 
 * and the constructor selected by the only member of the initializer list is the target constructor
 */
class Foo {
public:
  Foo(char x, int y) {}
  Foo(int y) : Foo('a', y) {} // Foo(int) delegates to Foo(char,int)
};
//--------------------------------------------------------------------
//c++ talk
https://www.youtube.com/watch?v=JfmTagWcqoE
https://www.youtube.com/watch?v=xnqTKD8uD64&t=1h03m44s
//move, copy,lvalue, rvalue,const member function
//rvalue vs lvalue
https://www.youtube.com/watch?v=UTUdhjzws5g
https://www.fluentcpp.com/2018/02/06/understanding-lvalues-rvalues-and-their-references/

rvalue:
-temp value(could be stored in the register) ,does not have address
-value that you can not assign to, you can read it but not write to it
-any value that is not lvalue
lvalue:(has containers, that contains value)
-value that has identifiable address that stroes in the memory, like variables
-value that can appear on the lhs of the assignment
summary:
every c++ expression yield either a rvalue or lvalue
if the expression has an identifiable address, it is a lvalue ,else rvalue


//explicit constructor
//https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean
// single parameter constructor, can be used as an implicit conversion
e.g.:
class Foo
{
public:
  // single parameter constructor, can be used as an implicit conversion
  Foo (int foo) : m_foo (foo){}
  int GetFoo () { return m_foo; }

private:
  int m_foo;
};

void DoBar (Foo foo)
{
  int i = foo.GetFoo ();
}

//get a type int as arg ,but should be of type Foo, and Foo constructor
//param match as int ,so the compiler will implicitly call the Foo
//constructor with the parameter int , with the explicit decoration 
//infront of the function would prevent the compiler to do the implicit
//type convertion
int main ()
{
  DoBar (42); 
}


//friends

//swap implementation


//move vs copy assignment
/*
when copy a pointer could be potentially problematice for example
when multile copies of pointer points to the same thing would leads
to multiple free, if one of the pointer is out of the scope and the
space that it points to will be freed, but same will happend when other
pointers are out of scope which would lead to double free.
move assignment would be the choice since it will copy the content of the pointer
and then leave the original pointer in the valid but undefined state for later destroy
*/
//move implementation:cast a lvalue into rvalue
T&& move(T& value) {
 return static_cast<T&&>(value);
}

std::move(obj); //creates just an rvalue reference,obj not changed
//since now rhs is a rvlaue reference , and might call move
//assignment constructor and obj
//obj will be in a valid but undefined state and later will be destroyed once out
//of scope , so good for pointer move
auto obj2 = std::move(obj); //possibly change the content of objct

//move vs copy assignment 
https://www.quora.com/What-is-the-difference-between-copy-constructor-and-move-constructor

//by passing the rvalue reference the compiler would know that this is 
//a move operation and will just move the allocated space of this rvalue to the
//assinged var to avoid double allocate space and then copy, since we do not 
//care about the original value since it is a rvalue and we could take advantage of its
//preallocated space and move to the new var that stores its info
IntArray& IntArray::operator= (IntArray&& orig) noexcept {
    delete[] values_;
    values_ = orig.values_;
    size_ = orig.size_;
    orig.values_ = nullptr;
    orig.size_ =0;
    return *this;
}


//copy assignment
//usually if class has swap method then it will be used
//for copy assignment using copy and swap, faster
v2 = v1;//construct a temp object that with v1 , then swap temp with v2,
        //once temp out of scope ,it will take v2's value with it safely


+++// move will not allocate anyspace?
//move constructor move assignment constructor
//move constructor takes a rvalue reference and copy constructor 
//takes a lvalue reference, so if a class has both rvalue and lvalue
//constructor it will call the corresponding constructor depend on the parameter
StrVec v1, v2;
v1 = v2; //copy assignment constructor since v2 is a lvalue
StrVec getVec(istream &);
//since rhs is a rvalue , we do no care about the temp result, so 
//there is no need to copy so as to preserve the state of the copy from object
//move will be sufficient as to get the content and then destroy the move from temp object
v2 = getVec(cin); //move assignment constructor , since rhs is rvalue


//const memeber function
//function would not change the state of the class ,read only
+++//would be able to change other class memebers?

int funct_name const (..){};

//friend,how to define friend
//friend class and method are needed since , some times we would like
//some classes to get access the private memember of the class
//for example the test class

//--------------------------------------------------------------------
//wk3 tute
std::istringstream // turn a string into an input stream
std::ostringstream //turn a string into an output stream
/* input and output stream like cin will parese the stream by white space and return
 * the token one by one each time dereference it until reach then end of the stream
 */
std:istream     //is the base class of all input stream,would be used for generalisatioin

std::vector<string> temp;
//copy takes 3 args:start of iter copy from , end of iter copy from, iterator where to insert from, 
//function to evaluate each element and only copy the element if it is being evaluated to true
std::copy_if(vec.start(),vec.end(),std::back_inserter(temp),[&](const auto& w) {return if(dict.find(w) != dict.end());})

//sort the vector by the length of the input string
std:vector<string> vec {"apple","cheers","babba"};
std::sort(vec.begin(),vec.end(),[](auto const& w1,auto const& w2){return w1.size() > w2.size();});
//=================================================================
//Mememry and smart pointer
#include <memory>

//----------------------------------------------------------------------
//shared pointer
//like emplace ,make_shared will take the argument and pass to construtors
//to construct an object,if not passed value then value is default initialised
shared_ptr<int> p3 = make_shared<int>(42);//allocate space and init with value return a shared pointer
shared_ptr<string> p4 = make_shared<string(10,'9');//'9999999999'
shared_ptr<int> p5 = make_shared<int>();//inti the 0

//when shared pointer is copied ,the object referenced count will increase
auto q(p4);
auto r = make_shared<int>(42);
//r now points to what q points to which is different than what it points to before
//object r original points to reference decrease , object that r currently points to
//reference count gets increased
r = q;

//common operations
shared_ptr<T> sp; //null init a smart pointer if(sp) true points to somthing
unique_ptr<T> up;
*sp;// dereference to the object it points to
sp->mem;//access member of the objet it points to
sp.get(); //return the pointer in p
swap(p,q);//swap the pointer in p and q
sp.unique(); //return 0 or 1 whether it is the unique pointer that points to the object
sp.use_count();

//other ways to define and change shared_ptr
shared_ptr<T> p(u); //p takes ownership from unique_ptr u,make u null
shared_ptr<T> p(p2,d); //p is a copy of shared_ptr p2, p will use callable 
                       //object d in place of delte to free p2
                       
/*if p is the only pointer points to its object reset will free this
 * object  and make p null
*/
p.reset(); //if p is not the unique shared pointer , then reference count decrease
p.reset(q);//q is raw pointer, make p points to q and use free to free q
p.reset(q,d); //use d instead of free to free q 

//----------------------------------------------------------------------
//using new and delete for dynamically allocated mememory
//is usually more error prone and class default constructor and destructor
//can not mannage that like smart pointers
int *pi = new int;//allocate space for int and init with undefined value return a pointer
int *p = new int();//same as above

//init a dynamically allocaetd object
int *p = new int(1024);
vector<int> *p = new vector<int>{1,2,3,3,4,5};
string *p = new string(10,'9');

//const objects
const int *pci = new int(1024); //dynamically allocated const object must initialised

//memory allocation exceptions
int *p1 = new int; //if allocation fails throws std::bad_alloc
int *p1 = new (nothrow) int; //if allocation fials return a null pointer
//delete a memory that was not allocated by new or delete the same pointer more than
//once is undefined
delete p; //p must points to a dynamically allocated object or be null
p = nullptr // invalidate the pointer

//use uninitialised pointer is problematic , because the address that
//ges allocated to the pointer will contains some bits and there is 
//no way to tell if these bits are valid address or not so would result
//in undefined behavior
//so do not define a pointer until the object that it needs to points to
//needs to be binded otherwise init to Null so that we know it has not been init

//----------------------------------------------------------------------
//unique pointer:takes the ownership of the object it points to
//which is only pointer points to the object, when destroyed
unique_ptr<double> p1 = std::make_unique(99.0);
unique_ptr<double> p2(new string("strange"));
unique_ptr<double> p3(p1);//no copy construtors for unique_ptr
p1 = p2; 

//unique_ptr operations
unique_ptr<T> u1; // u1 points to type T using delete to free its pointer
unique_ptr<T,D> u2; //using callable object D to free its pointer
u = nullptr; //delete the object u points make u null
u.release(); //handover the control of the pointer u had, return the pointer and make u null
u.reset(); //dlete the object to which u oints
u.reset(q); //make u points to what raw pointer q points to and delte what u previously points to
u.reset(nullptr); //delete the object u points to and set u to nullptr

//transform ownership
unique_ptr<string> p2(p1.release()); //p1 release the ownership becomes null
unique_ptr<string> p3(new string("erik"));
//p3 release its pointer and becomes null
p2.reset(p3.release());// reset deletes the memeory p2 previously points to

//whenever we release a smart pointer we need to pass onto another one
p2.release(); //WRONG, p2 will get lost and not freed

//unique pointer can not be copied or assigned 
//but can be done if it is about to be destroyed
unique_ptr<int> clone(int p){
    //complier would know that r is about to be destroyed
    unique_ptr<int> r(new int(p));
    return r;
}

//------------------------------------------------------------------------------------------
//weak pointer:points to an object that is mannaged by a shared_ptr
//binding a weak pointer to a shared_ptr does not change the reference count
auto p = make_shared<int>(42);
weak_ptr<int> wp(p); //ref count in p is not changed

//we could not directly use weak pointer to access the object
//we need to use lock() to check if the underlining object
//still exits , if yes will return a shared_ptr to that object else nullptr
if(shared_ptr<int> np = wp.lock()){
    //np can be used inside
}

//operations on make_shared
weak_ptr<T> w;//null weak pointer w can points to type T object
//points the same object shared_ptr sp points and T must be able to converte to its type 
weak_ptr<T> w(sp); 
w = sp;
w.reset(); //make w null
w.use_count(); //the number of shared_ptr that share with w
w.expired(); //return true if use_count is 0 else flase
w.lock(); //if expired is true , return a null shared_ptr,else shared_ptr to that object


//------------------------------------------------------------------------------------------
//Dynamic Arrays:can allocate an array of objects return a pointer to the first element
int *p = new int[42]; //allocate an array of 42 ints uninitialised
int *p = new int[10](); //allocate and iniit to 0
string *p = new string[10]; //10 emepty string
string *p = new string[10](); // same as above
//if more initialiser than allocation would fail,no space allocated
//if less initialiser than elements,remaining elelments value initialised
int *p = new int[5]{1,2,3,4,5};

//allocate 0 size array is legal
char arr[0]; //error can not define a 0 length array
char *cp = new char[0];//okay but cp can not be dereferenced

//free:[] tells the compiler that the pointer points the first element of the array
delete p; //delete the object p points to
delete [] pa;//pa must point to a dynamically allocated array or be null

//use unique pointer for dynamic array
unique_ptr<T[]> u;
unique_ptr<T[]> u(p); //u points to the dynamically allocated array to which raw pointer p points, p must convertable to T*
unique_ptr<int[]> up(new int[10]); //<int[]> inidate points to an array of this type
unique_ptr<int[]> up = make_unique<int[]>(10) //<int[]> inidate points to an array of this type
up.reset(); // automatically use delete [] to destroy its pointer

//accessing elements using [] since it now points to an array
for(size_t i = 0;i != 10;++i)
    up[i] = i;

//no direct support for dynamic array for shared_ptr
//need to define our own lamda as deleter
shared_ptr<int> sp(new int[10], [](int *p) {delete [] p;});

//shared_ptr does not have subscriber operator and do not support pointer arithmatic
//for access elements
for(size_t i = 0;i != 10;++i)
    *(sp.get() + i) = i;


//=================================================================
//Template
template <typename T> //template parameter list
T min(T a, T b){ //template type parameter
    return a < b ? a:b;
}

//type and nontype paramaeters
//unknow type with no value
//known type with unknow value
//for each different type array as well as different size array
//will instantiate differetn function for each since array size needs
//to be known at compile time
template <typename T,int size>
T findmin(const std::array<T,size> a){
    
}

//class template
template <typename T>
class Stack {
    public:
        friend std::ostream& operator<<(std::ostream& os, const Stack& s) {
            for (const auto& i : s.stack_) os << i << " ";
            return os;
        }

        void push(T&);
        void pop();
        T& top();
        const T& top() const;
    private:
         vector<T> stack_;
};


//if function defined outside the class need to specify the 
//template as its scope 
template <typename T>
void Stack<T>::push(const T &item) {
    stack_.push_back(item);
}

/*inclusion compilation mode need to include the implementation of the template in
the template.h file
template in .cpp file would not able to compile since it is the drection
to instantiate an instance of this template,without instantiate itself is 
not able to compile so need to be includes where instantiations is needed
so that it is able to compile at the compile time
*/


//Each template instantiation has it's own set of static members

//Each stack instantiation has one unique instantiation of the friend
template <typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& s) {
  std::cout << "My top item is " << s.stack_.back() << \n";
}

template <typename T, typename CONT = std::vector<T>>

//------------------------------------------------------------------------------------------
// type fowarding

/* forward<T> is &&T: forward returns an rvalue reference to 
 * that explicit argument type
 */
template <typename F, typename T1, typename T2>
void flip(F f, T1&& t1, T2&& t2){
   /*when pass in flip2(f,i,42)  
    * T1 will be of int& , so int& && t1, t1 collapse into int& t1
    * T2 will be of int&&, so int&& && t2, t2 collapse into int&& t2 
    * forward t1 and t2 will preserve the type it passed in through flip
    */
    f(std::forward<T2>(t2),std::forward<T1>(t1)); 
}

/*when pass in flip2(f,i,42) 
 * T1 will be of int& , so int& && t1, t1 collapse into int& t1
 * T2 will be of int&&, so int&& && t2, t2 collapse into int&& t2 
 */
template <typename F, typename T1, typename T2>
void flip2(F f, T1&& t1, T2&& t2){
    f(t2,t1); // now t2 is a lvalue reference variable can not bind to rvalue reference in f paramater
}

int i = 99;
flip(f,i,42);

//=================================================================
//-why friend definition insdied the class
//-why no function specialisation
// rvalue xvalue, pvalue
// type traits

//=================================================================
// polymorphism
// vtable
https://pabloariasal.github.io/2017/06/10/understanding-virtual-tables/


//------------------------------------------------------------------------------------------
/*  By now it should also be clear why it is always a good idea to make destructors 
 *  of base classes virtual. Since derived classes are often handled via base class references,
 *  declaring a non-virtual destructor will be dispatched statically, 
 *  obfuscating the destructor of the derived class
 */
#include <iostream>

class Base {
public:
  ~Base(){
    std::cout << "Destroying base" << std::endl;
  }
};

class Derived : public Base {
public:
  Derived(int number) {
    some_resource_ = new int(number);
  }

  ~Derived() {
  std::cout << "Destroying derived" << std::endl;
  delete some_resource_;
  }

private:
  int* some_resource_;
};

int main()
  Base* p = new Derived(5);
  delete p;
}

//------------------------------------------------------------------------------------------
// static type and dynamic type
// pointer to the base class and dervied class object
https://gradestack.com/Programming-in-C-/Binding-Polymorphisms-/Pointer-To-Base-and/21206-4330-52995-study-wtw
// why pointers needs to have type
https://stackoverflow.com/questions/44345148/why-do-you-have-to-specify-a-type-for-pointers

int main() {
  BaseClass base_class;
  SubClass subclass;
  BaseClass sub_copy{subclass};
  // The following could all be replaced with pointers
  // and have the same effect.
  const BaseClass& base_to_base{base_class};
  const BaseClass& base_to_sub{subclass}; // sub class is a Base class
  // Fails to compile
  const SubClass& sub_to_base{base_class}; // base_class can not be a SubClass
  const SubClass& sub_to_sub{subclass};
  // Fails to compile (even though it refers to at a sub);
  const SubClass& sub_to_base_to_sub{base_to_sub}; // at compile time does not know base_to_sub type
}

SubClass sub;
BaseClass* p = &sub; // p will points to Baseclass instead of sub class
// will only get acees to the BaseClass memebr instead of that of the subclass
// even the address was the sub class object address, since the static type of the 
// pointer is the Base class 
cout<< "deference and find sub num : "<< p->num <<'\n'; 

// down casting
// it is alwasys safe to do upcasting since a subclass is a base class
// if subclass upcasting , it just lose information about the subclass
// but base class that it inherited from is still valid
// we tell the compiler that p actually poinst to the subclass
// so now dp can get access the subclass memebers
auto dp = static_cast<SubClass*>(p); // down cast the pointer to Base Class to the subclass
cout<< "deference and find sub num : "<< dp->sub_num <<'\n'; 

// another down casting example
// static type is faster but when the casting type is invalid it will
// not through exception and behavior is undefined
// so if not sure about the type that is casting can use dynamic
// casting so that compiler can decide for you at run time
Dog dog;
Cat cat;
Animal& animal_dog{dog};
Animal& animal_cat{cat};
// Attempt to down-cast with references.
Dog& dog_ref{static_cast<Dog&>(animal_dog)};
Dog& dog_ref{dynamic_cast<Dog&>(animal_dog)};
// Undefined behaviour (incorrect static cast).
Dog& dog_ref{static_cast<Dog&>(animal_cat)};
// Throws exception
Dog& dog_ref{dynamic_cast<Dog&>(animal_cat)};

// returns null pointer
Dog* dog_ref{dynamic_cast<Dog*>(animal_cat)};

//------------------------------------------------------------------------------------------
// Covariant
// Every possible return type for the derived must be a valid return type for the base
class Base {
  // subclass implementation must return the same class or
  // subclass of what the virtual function in the base function returns
  virtual LandAnimal& GetFavoriteAnimal();
};
class Derived: public Base {
  // Fails to compile: Not all animals are land animals.
  Animal& GetFavoriteAnimal() override;
  // Compiles: All land animals are land animals.
  LandAnimal& GetFavoriteAnimal() override;
  // Compiles: All dogs are land animals.
  Dog& GetFavoriteAnimal() override;
};

// Contravariants
// Every possible parameter to the base must be a possible parameter for the derived
class Base {
  virtual void UseAnimal(LandAnimal&);
};
class Derived: public Base {
  // Compiles: All land animals are valid input (animals).
  void UseAnimal(Animal&) override;
  // Compiles: All land animals are valid input (land animals).
  void UseAnimal(LandAnimal&) override;
  // Fails to compile: Not All land animals are valid input (dogs).
  void UseAnimal(Dog&) override;
};
//------------------------------------------------------------------------------------------
// Default arguments and virtuals
// Default arguments are determined at compile time for efficiency's sake
// Hence, default arguments need to use the static type of the function
// Avoid default arguments when overriding virtual functions!
class Base {
  virtual void PrintNum(int i = 1) {
  std::cout << "Base " << i << '\n';
  }
};

class Derived: public Base {
  void PrintNum(int i = 2) override {
  std::cout << "Derived " << i << '\n';
  }
};

int main() {
  Derived derived;
  Base& base{derived};
  derived.PrintNum(); // Prints "Derived 2"
  base->PrintNum(); // Prints "Derived 1" since it use the static type fo the function
}

//=================================================================
// tuple








//=================================================================
