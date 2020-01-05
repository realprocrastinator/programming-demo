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
int sm_cum_alloc = 0;
int sm_end_addr = 20;
int sm_start_addr = 0;

int getpagesize(){return 3;}

// give alloc size 
void *smMalloc(size_t size){
    //=================== register alloctor if new page needed============================
    int curr_addr = sm_start_addr + size;
    int curr_cum  = sm_cum_alloc + (int)size;
    int reg_start_addr; // regist with allocator start and end page range
    int reg_end_addr;

    if(curr_addr > sm_end_addr) return NULL; // alloc will exceed the memory partition

    // check if need to register a new page with the allocator 
    if(!sm_cum_alloc){// need to register new page 
        reg_start_addr = sm_start_addr;
        reg_end_addr = curr_addr - (curr_cum % getpagesize());

        printf("register page address: %d - %d \n",reg_start_addr,reg_end_addr);
    }else{ // current upto touched page has been registered
        if(curr_cum > getpagesize()){
            // start page address is one page ahead of the previous page aligned start
            reg_start_addr = sm_start_addr + (getpagesize() - sm_cum_alloc); // the next aligned paged
            reg_end_addr = curr_addr - (curr_cum % getpagesize());

            printf("register page address: %d - %d \n",reg_start_addr,reg_end_addr);
        } 
    }
    
    // update the alloc address and cum address
    sm_cum_alloc = curr_cum % getpagesize();
    sm_start_addr = curr_addr; // keep track where allocated so far 
    
    return (void *)curr_addr;
}

//---------------------------------------------------------------
int main() {
    //smMemPartition();
    smMalloc(5);
    smMalloc(5);



}
