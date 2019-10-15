#include <stdio.h>
#include <stdlib.h>

struct link {
    int data;
    struct link *next;
};

void push(struct link*,int);

void push(struct link* pt,int i){
    struct link *curr_pt;
    if(pt == NULL) { //head is null
        printf("iam here\n");
         curr_pt =(struct link *) malloc(sizeof(struct link));
         curr_pt->data = i;
         curr_pt->next = NULL;
         pt = curr_pt;
    }else { //at least one element in linked list already
         curr_pt = pt;
         for(;curr_pt->next !=NULL;curr_pt = curr_pt->next);
         curr_pt->next =(struct link *) malloc(sizeof(struct link));
         curr_pt->next->data = i;
         curr_pt->next->next = NULL;
    }
}

struct link *pt = NULL;
int main() {

   for(int i = 0; i < 5;i++){
       push(pt, i);
   }
   //now we check if we can retrive all the info from the linked list
   while(pt != NULL){
        printf("The linked list content is %d\n",pt->data);
        pt = pt->next;
   }



   return 0;

};
