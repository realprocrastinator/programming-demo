#include <iostream>

using namespace::std;

// Automatic type deduction "auto"
// Auto deduction: Take exactly the type on the right-hand side but strip off
// the top-level const and &.


// When doing call by value, top-level const has no effect on the objects
// passed ot the function. A parameter that has a top-level const is
// indistinguishable from the one without
// Top-level const ignored
Record Lookup(Phone p);
Record Lookup(const Phone p); // redefinition
// Low-level const not ignored
Record Lookup(Phone &p); (1)
Record Lookup(const Phone &p); (2)
