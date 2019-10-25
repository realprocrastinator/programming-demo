#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>

//#define ADDR  ((void *) 0x10a40f000) // start of the nmap address
//#define ADDR ((int)0)// start of the nmap address
#define ADDR  ((long)0x10a40f000)
#define PAGE_NUM ((int)0xffff)   // number of pages for the virtual memory

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
void smMemPartition_bak(){
    int pages = PAGE_NUM; 
    int nodes = 3;
    
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

#include <unistd.h>
long sm_start_addr = 0;
long sm_end_addr = 0;
//---------------------------------------------------------------
void smMemPartition(long* start_addr,long* end_addr){
    int _sm_nid = 2;
    int _sm_nodes = 3;

    int page_interval = PAGE_NUM/_sm_nodes; // int division of number of pages
    int remain_pages = PAGE_NUM % _sm_nodes; // remainder of the pages
    long start_page_addr;
    long end_page_addr;
    printf("page_interval: %d,remain_pages: %d\n",page_interval,remain_pages);

    if(!remain_pages){ // if equal divide
        start_page_addr = ADDR + _sm_nid*page_interval*getpagesize();
        end_page_addr = start_page_addr + page_interval*getpagesize();
    }else{ // not equal dividable
        if(_sm_nid <= (remain_pages-1)){ // spread the remaining pages from the start of the node
            start_page_addr = ADDR + _sm_nid*(page_interval + 1)*getpagesize();
            end_page_addr = start_page_addr + (page_interval + 1)*getpagesize();
        }else {// the rest node will get the equal dividable number of pages
            start_page_addr = ADDR + (_sm_nid*page_interval+ remain_pages)*getpagesize();
            end_page_addr = start_page_addr + page_interval*getpagesize();
        }
    }

    *start_addr = start_page_addr;
    *end_addr = end_page_addr;

    printf("Node 2 has %ld pages, start page:%p, end page%p\n",
         (end_page_addr - start_page_addr)/getpagesize(),(void *)start_page_addr,(void *)end_page_addr);
}
//---------------------------------------------------------------
int sm_cum_alloc = 0;
//int sm_end_addr = 20;
//int sm_start_addr = 0;

//int getpagesize(){return 3;}

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
int page_table[PAGE_NUM] = {};
void regPage(char* start_string, char* end_string,int nid){

    void *pt1;
    void *pt2;
    sscanf(start_string,"%p",&pt1);
    sscanf(end_string,"%p",&pt2);
    long start_addr = (long)pt1;
    long end_addr = (long)pt2;
    //printf("string addr: %s, to long address:%ld\n",addr,start_addr);

    int page_start = ((start_addr - ADDR) / getpagesize()); // start page offset
    int page_num = ((start_addr - end_addr) / getpagesize() + 1); // total number of pages
    printf("start addr: %ld, end addr: %ld, page start %d, total page: %d\n", 
            start_addr, end_addr,page_start,PAGE_NUM);
    printf("page size:%d\n",getpagesize());
    
    //for(int i = page_start;i<page_num;++i) page_table[i] = nid;
}

//---------------------------------------------------------------



#include <sys/mman.h>

//---------------------------------------------------------------
int main() {
    void* pt = malloc(256);
    char buff[256];
    sprintf(buff,"%p",pt);
    printf("This is addr_str:%s",buff);
    printf("This is add:%p",pt);

    /*
    long start_addr, end_addr;
    smMemPartition(&start_addr,&end_addr);
    printf("Node 2 has %ld pages, start page:%p, end page%p\n",
         (end_addr - start_addr)/getpagesize(),(void *)start_addr,(void *)end_addr);



    //smMemPartition();
    //smMalloc(5);
    void *pt;
    char* addr = "0x114eb9000";
    sscanf(addr,"%p",&pt);
    long start_addr = (long)pt;
    printf("string addr: %s, to long address:%ld\n",addr,start_addr);

    char* start_string = addr;
    char* end_string =addr;
    regPage(start_string,end_string,1);

   */

    /*
    void *addr = mmap((void *)ADDR,getpagesize(),PROT_WRITE|PROT_READ, 
                        MAP_PRIVATE| MAP_ANONYMOUS,-1,0);
    if (MAP_FAILED == addr) perror("mmap");

    *((int *)addr) = 1;
    printf("%d\n",*((int*)addr));
    */



}
