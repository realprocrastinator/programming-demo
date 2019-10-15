// execl
// excute a executable with args
char *args[]={"./Hello","arg1","arg2",NULL};
execvp(args[0],args);

// wait(& int)
// http://man7.org/linux/man-pages/man2/waitpid.2.html
int status;
/*
 * If wstatus is not NULL, wait() and waitpid() store status information
  in the int to which it points.  This integer can be inspected with
  the following macros (which take the integer itself as an argument,
  not a pointer to it, as is done in wait() and waitpid()!):
*/
wait(&status) // store the child process exit info in to the status later can be inspect
WIFEXITED(wstatus) //returns true if the child terminated normally, that is, by
                   //calling exit(3) or _exit(2), or by returning from main().check 

// -----------------------------------------------------------------
// how to connect to vina
https://piazza.com/class/k0eoutxdu7j1hm?cid=44
// login to cse machine and then ssh vina0x (where x is the number 0 - 9)

// static libarary
https://www.geeksforgeeks.org/static-vs-dynamic-libraries/
https://medium.com/@meghamohan/all-about-static-libraries-in-c-cea57990c495
ar rcs lib_mylib.a lib_mylib.o // create static lib archive
// static link the lib -l would be the lib with outlib prefix and postifx
gcc -o driver driver.o -L. -l_mylib 

// make files
http://nuclear.mutantstargoat.com/articles/make//
https://opensource.com/article/18/8/what-how-makefile

// -----------------------------------------------------------------
//
