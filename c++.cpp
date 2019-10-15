//=================================================================
//Debugging
//GDB Debugging 
https://www.youtube.com/watch?v=J7L2x1ATOgk



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

