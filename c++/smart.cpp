#include <meory>
#include <iosteam>

// =========================================================================
// unique pointer
//unique pointer:takes the ownership of the object it points to
//which is only pointer points to the object, when destroyed
// -------------------------------------------------------------
// uniquee pointer operation
unique_ptr<double> p1 = std::make_unique<double>(99.0);
auto p11 = std::make_unique<double>(99.0);

unique_ptr<double> p2(new string("strange")); // tamke a raw pointer
unique_ptr<double> p3(p1);// error no copy construtors for unique_ptr
p1 = p2; i// error no copy assignment

// -------------------------------------------------------------
//unique_ptr operations
unique_ptr<T> u1; // u1 points to type T using delete to free its pointer
unique_ptr<T,D> u2; //using callable object D to free its pointer
u = nullptr; //delete the object u points make u null
u.release(); //handover the control of the pointer u had, return the pointer and make u null
u.reset(); //delete the object to which u oints
u.reset(q); //make u points to what raw pointer q points to and delte what u previously points to
u.reset(nullptr); //delete the object u points to and set u to nullptr
u.get() // return the raw pointer u pionts to

// -------------------------------------------------------------
//transform ownership
unique_ptr<string> p2(p1.release()); //p1 release the ownership becomes null
unique_ptr<string> p3(new string("erik"));
unique_ptr<string> p4(new string("erik2"));
//p3 release its pointer and becomes null
p2.reset(p3.release());// reset deletes the memeory p2 previously points to
p2 = std::move(p4); // move is okay, p2 original object destroyed p4

//whenever we release a smart pointer we need to pass onto another one
p2.release(); //WRONG, p2 will get lost and not freed

//unique pointer can not be copied or assigned 
//but can be done if it is about to be destroyed
unique_ptr<int> clone(int p){
    //complier would know that r is about to be destroyed
    unique_ptr<int> r(new int(p));
    return r;
}

// -------------------------------------------------------------
//use unique pointer for dynamic array
unique_ptr<T[]> u;
unique_ptr<T[]> u(p); //u points to the dynamically allocated array to which raw pointer p points, p must convertable to T*
unique_ptr<int[]> up(new int[10]); //<int[]> inidate points to an array of this type
unique_ptr<int[]> up = make_unique<int[]>(10) //<int[]> inidate points to an array of this type
up.reset(); // automatically use delete [] to destroy its pointer

//accessing elements using [] since it now points to an array
for(size_t i = 0;i != 10;++i)
    up[i] = i;


// =========================================================================
// shared pointers
// ----------------------------------------
// initialisation
//like emplace ,make_shared will take the argument and pass to construtors
//to construct an object,if not passed value then value is default initialised
shared_ptr<int> p3 = make_shared<int>(42);//allocate space and init with value return a shared pointer
shared_ptr<string> p4 = make_shared<string>(10,'9');//'9999999999'
shared_ptr<int> p5 = make_shared<int>();//inti the 0

// ----------------------------------------
// conpy construct and assignment
//when shared pointer is copied ,the object referenced count will increase
auto q(p4); // copy construct and reference count will increase
auto r = make_shared<int>(42);
//r now points to what q points to which is different than what it points to before
//object r original points to reference decrease , object that r currently points to
//reference count gets increased
r = q; // copy assignment

/* when do we use share pointer instead of unique_ptr?
 * when we do not know which series pointes points to the single resources
 * would last longer, if we know we will set that pointer as unique_ptr with rest 
 * as observer pointer
 */

// ----------------------------------------
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
shared_ptr<T> p(u.release()); //p takes ownership from unique_ptr u,make u null
p.reset(u.release()) // transfer ownership 

shared_ptr<T> p(p2,d); //p is a copy of shared_ptr p2, p will use callable 
                       //object d in place of delte to free p2
                       
/*if p is the only pointer points to its object reset will free this
 * object  and make p null
*/
p.reset(); //if p is not the unique shared pointer , then reference count decrease
p.reset(q);//q is raw pointer, make p points to q and use free to free q
p.reset(q,d); //use d instead of free to free q 

// =========================================================================
// weak pointer
//weak pointer:points to an object that is mannaged by a shared_ptr
// when to use weak pointer:
// e.g. cache: we do not want to use strong pointer for cache since 
// if the application do no reference to the object but cache still and 
// it will therefore stays in the memory.
// if we use weak pointer, we can access cache when there is stil applicaiton use it
// but no need to cache if it is not in the memory
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

// =========================================================================
// Exception
// Common types are:
// std::invalid_argument:
// std::out_of_bounds:
#include <stdexcept>

try {
 // Code that may throw an exception
} catch (/* exception type */) {
 // Do something with the exception
} catch (...) { // any exception
 // Do something with the exception
}

// --------------------------------------------------------------
// throw exception by value is costly do all the copies
// somethigs will have object sliceing 
class Giraffe {
    public:
        Giraffe() { std::cout << "Giraffe constructed" << '\n'; }
        Giraffe(const Giraffe &g) { std::cout << "Giraffe copy-constructed" << '\n'; }
        ~Giraffe() { std::cout << "Giraffe destructed" << '\n'; }
};

void zebra() {
    throw Giraffe{};
}

void llama() {
    try {
        zebra();
    } catch (Giraffe g) {
        std::cout << "caught in llama; rethrow" << '\n';
        throw;
    }
}
// --------------
int main() {
    try {
       llama();
    } catch (Giraffe g) {
       std::cout << "caught in main" << '\n';
    }


// --------------------------------------------------------------
// always catch by const reference 
// to avoid copy and can use polymorphism for dervied classess of exceptions
 class Giraffe {
    public:
        Giraffe() { std::cout << "Giraffe constructed" << '\n'; }
        Giraffe(const Giraffe &g) { std::cout << "Giraffe copy-constructed" << '\n'; }
        ~Giraffe() { std::cout << "Giraffe destructed" << '\n'; }
};

void zebra() {
    throw Giraffe{};
}

void llama() {
    try {
        zebra();
    } catch (const Giraffe& g) {
        std::cout << "caught in llama; rethrow" << '\n';
        throw;
    }
}
// --------------
int main() {
    try {
       llama();
    } catch (const Giraffe& g) {
       std::cout << "caught in main" << '\n';
    }
}

// --------------------------------------------------------------
// rethrow
// somethins we want outer layers of try and catch to do something with the
// exception so we rethrow the exception s.t. it progprogate to the outer layer
// of the exception catch bolck to get processed
try {
    try {
        try {
            throw T{}; // expression after throw is not excute like return
        } catch (T& e1) { // catch this block exception
            std::cout << "Caught\n";
            throw; // so that the try catch enclosing this block will catch the excpetion
        }
    } catch (T& e2) {
        std::cout << "Caught too!\n";
        throw;
    }
} catch (...) {
    std::cout << "Caught too!!\n";
} 


/* when to rethrow an exeption?
 * when you want the hihger level of catch to do something with the exception
 * to proprogate the exception to the higher level for processing
 *
 */
// --------------------------------------------------------------
// stack unwinding
/* when an exception is thrown, excution of the current function is suspended.
 * it will search for a matching catch if no match is found then this function will
 * exit and the search continues in the calling function
 * This wuld continue up the chain of nexted function calls until a matching catch is found
 * or the main function is exited without having found a matching catch
 * if a catch has been found then code inside the catch will be excuted and then continue
 * immediately after the try catch block
 * during stack unwinding, function may exit prematurely, and during this process like function exit
 * local object created within the function will get destroyed, compiler will call destructor for
 * the locally created objects
 * if exception occurs in the constructor, the partially constructe object's initiallsed memebr
 * will get destructed
 */

// example of potential problem when there is uname heap object being created during
// the stack unwinding, which would not be able to dectroyed when the exception occurrs
// solution would to tie the heap object othe the stack frame suing smart pointers

/* stack unwinding happens when exception fuction will call destructor for objects created locally
 * on the stack , if there is exception occurs in the destructor , progrogramme would terminate
 * potentail problem during the process is unmanaged resources for example object allocated on the heap 
 * before the exception ocurrs , would not be properly relased.
 * The way to solve this is the make sure that objects are owned by either another resource, the stack
 * or an unnamed temperatry variable
 */
void g() {
    throw std::runtime_error{""};
}
int main() {
    auto ptr = new int{5};
    g();
    // Never executed.
    delete ptr;
}

// ---------
// better solution
void g() {
    throw std::runtime_error{""};
}
int main() {
    auto ptr = std::make_unique<int>(5);
    g();
}


// partially constructed object will not call destructor of this object
class UnsafeClass {
    UnsafeClass::UnsafeClass(int a, int b):
        a_{new int{a}}, b_{new int{b}} {}

    ~UnsafeClass() { // destructor will not called when there is exception in the constrcutor
        delete a_;
        delete b_;
    }

    int* a_;
    int* b_;
}

// ---------
// better solution
class SafeClass {
    // if exception occurs during the construction
    // since its partially construct object is tied to the stack frame
    // therefore its memeber will be dsturctor by calling its object destructor
    SafeClass::SafeClass(int a, int b):
        a_{std::make_unique<int>(a)},
        b_{std::make_unique<int>(b)} {}

    std::unique_ptr<int> a_; 
    std::unique_ptr<int> b_;
}

// --------------------------------------------------------------
// different levels of exception safety
// No-throw guarantee
/* no exception would ocurrs like close files, free memeory
 */


// Strong exception exception safety
// if exception ocurrs would roll back to the exact previous state
// when the exception did not occur
/* Operations can fail, but failed operations are guaranteed to have no visible
 * like copy assignment swap, it will be either success or nothing happens
 *
 * To achive strong exception:
 * First perform any operations that may throw, but don't do anything irreversible
 * Then perform any operations that are irreversible, but don't throw
 * like allocate meory and copy before destroy olde object and deallocate memeory
 */

// Basic exception safety
/* might have side effects but there is no leak of memeory
 * all data contains valid value, even it was different from before
 * like not nonexcept move constructor
 */

// no except safty
/* no gaurantee any safety
 */
