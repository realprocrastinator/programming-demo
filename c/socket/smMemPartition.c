#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>

//#define ADDR  ((void *) 0x10a40f000) // start of the nmap address
#define ADDR ((int)0)// start of the nmap address

//---------------------------------------------------------------
int nid = 2;
int start_page_addr;
int end_page_addr;

//---------------------------------------------------------------
int split(char* s, char* delim, char** result){
    int counter = 0;

    for(char* pch = strtok(s,delim);pch !=NULL;
            result[counter++] = pch, pch = strtok (NULL, delim));

    return counter;
}
//---------------------------------------------------------------
void smMemPartition(){
    int pages = 37;
    int nodes = 13;
    
    for(int nid=0;nid<nodes;++nid){
        int page_interval = pages/nodes; // int division of number of pages
        int remain_pages = pages % nodes; // remainder of the pages
    
        if(!remain_pages){ // if equal divide
            start_page_addr = ADDR + nid*page_interval;//*getpagesize();
            end_page_addr = start_page_addr + page_interval;//*getpagesize(); 
        }else{ // not equal dividable
            if(nid <= (remain_pages-1)){ // spread the remaining pages from the start of the node
                start_page_addr = ADDR + nid*(page_interval + 1);//*getpagesize();
                end_page_addr = start_page_addr + (page_interval + 1);//*getpagesize(); 
            }else {// the rest node will get the equal dividable number of pages
                start_page_addr = ADDR + (nid*page_interval+ remain_pages);//*getpagesize();
                end_page_addr = start_page_addr + page_interval;//*getpagesize(); 
            } 
        }
        printf("Node%d has %d pages, start page:%d, end page%d\n",
                nid,end_page_addr- start_page_addr,start_page_addr,end_page_addr);
    }
}

//---------------------------------------------------------------
int main() {

    smMemPartition();


}
