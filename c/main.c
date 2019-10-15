#include<stdio.h>

void F(char** argv[]){
   printf("%s\n",(*argv)[2]);
}

int main(int argc, char* argv[]) {
    char* arr[] = {"this","is","greate"};
    char* arr2[] = {"two","for","good"};
   //printf("%s\n",argv[1]);
   
    F(&argv);


    return 0;
}

