#include <iostream>
#include <vector>
#include <map>
#include "stack.h"

using namespace std;
class A{
    public:
        static int class_num_;

        int num_ = 99; 
};

int A::class_num_ = 88;
void func(double a){
    cout << a << endl;
}

int main() {
    double a = 9.9;
    func(a);

    
}
