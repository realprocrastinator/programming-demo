#include<stdio.h>
#define ADD ((void *)0x40000000)

void F(char** argv[]){
   printf("%s\n",(*argv)[2]);
}

int main(int argc, char* argv[]) {
   printf("%p\n",ADD);
   


    return 0;
}

