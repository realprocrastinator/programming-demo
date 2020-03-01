#include<stdio.h>
#define ADD ((void *)0x40000000)

void F(char** argv[]){
   printf("%s\n",(*argv)[2]);
}

int main(int argc, char* argv[]) {
   printf("%p\n",ADD);
   int a = 0;
   int *p = a + 1;
   printf("%d\n",*p);
   


    return 0;
}

