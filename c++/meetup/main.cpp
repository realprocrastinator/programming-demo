#include "foo.hpp"

using namespace missinglink;

int main(){
  TheClass classInstance{};
  return classInstance.classMethod(TheClass::STATIC_CLASS_CONST);

}

