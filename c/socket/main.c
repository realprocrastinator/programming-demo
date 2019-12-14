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
long start_page_addr;
long end_page_addr;
long getpagesize(){return 100;}

//---------------------------------------------------------------
void smMemPartition_bak(){
    int pages = PAGE_NUM; 
    int nodes = 3;
    
    for(int nid=0;nid<nodes;++nid){
        int page_interval = pages/nodes; // int division of number of pages
        int remain_pages = pages % nodes; // remainder of the pages
    
        if(!remain_pages){ // if equal divide
            start_page_addr = ADDR + nid*page_interval*getpagesize();
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
        printf("Node%d has %ld pages, start page:%ld, end page%ld\n",
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
// split according to delim and will stop tokenise if second string is readreply,
// will not tokenise the remaining string after readreply
// special case in format: nid readreply content_of_page
//char s = "register|exit|nid readreply page_contentnid write addr|"
int splitString(char* s, char* delim, char** result){
    int counter = 0;
    char* pch;
    int read_flag = 0;
    int pipe_flag = strcmp(delim,"|")? 0 :1;

    for(pch = strtok(s,delim);pch !=NULL;
            result[counter++] = pch, pch = strtok (NULL, delim)){

        if(!strcmp(pch,"readReply")) { // to process words for each message
            read_flag = 1;
            break;
        }

    }

    if(read_flag){
        result[counter++] = pch;
        result[counter] = pch + strlen(result[counter -1]) + 1;
        ++counter;
    }

    return counter;
}

//---------------------------------------------------------------
#define PAGE_SIZE (strlen("hello word")+1)
#define BUFF_SIZE 256//(strlen("page content") - 1)

char* findChar(char* s,char delim,int len){
    for(int i = 0; i < len;++i) 
        if(*(s+i) == delim) return s + i;
    return NULL;
}

char* findNthChar(char* s, char delim, int len,int n){
    int count = 0;
    for(int i = 0; i < len;++i)
        if(*(s+i) == delim && ++count == n) return s + i;
    return NULL;
}


int splitToken(char* s,char delim, char** result,int recv_len){
    char* ptBegin = s ,*ptEnd = s;
    int count = 0,len = recv_len;

    while((ptEnd = findChar(ptBegin,delim,len))){
        // spcecial case to exclude page special char conflict with delim
        // in format: nid readreply page|content here|nid write addr
        char *space_pt = findNthChar(ptBegin,' ',len,3); // find third space
        char *delim_pt = findChar(ptBegin,'|',len);

        // only consider when there is no token before the possible readreply;;
        if(delim_pt > space_pt && space_pt &&
                !strncmp(space_pt+1,"readReply", strlen("readReply"))){

            char *space_pt2 = findChar(space_pt + 1,' ',len); // find second space
            printf("fourth space:%s\n",space_pt2);
            // skip the space from second space acroos all page content and replace
            // the delimiter by the end of the page by string terminator
            ptEnd = space_pt2 + 1 + (PAGE_SIZE);
        }

        *ptEnd = '\0'; // change delimiter to string terminator
        result[count++] = ptBegin; // mark this token
        len -= (ptEnd - ptBegin);
        ptBegin = ptEnd + 1; // move pt for the next token
    }

    if(len) result[count++] = ptBegin; // if reach the end but there is still string

    return count;
}

void makeReadReply(int nid1, int nid2, void* addr, char* send_buff){
    char header[50];
    sprintf(header,"%d %d %p readReply ",nid1,nid2,addr);



}

//---------------------------------------------------------------
// Params:
// -------
// s:String buffer
// result: store tokenised results
// read_len:actual read buffer len
int Tokeniser(char*s ,char** result,int read_len){
    char* currPt = s;
    char* endPt = currPt + read_len;
    int count = 0,len;

    for(sscanf(currPt,"%d",&len);currPt <endPt && !strncmp(currPt + 4,"begin",5);
            currPt += len){
        result[count++] = currPt;
        sscanf(currPt,"%d",&len);// recover message len
    }
    return count;
}

//---------------------------------------------------------------
/// Params:
// -------
// s: the star of the message sring
// result: to store pointers where the space is delimited
int MesDelim(char*s , char** result){
     // split each message according to white sapce
     // each message in format:19beign nid write ....
     int len,count = 0; 
     char* endPt, *currPt = s;

     for(sscanf(currPt,"%d",&len),endPt = currPt + len,currPt +=4;
             currPt < endPt;++currPt){
         if(*currPt == ' ')
             result[count++] = currPt + 1;
     }
     return count;
}

//---------------------------------------------------------------
// Params:
// --------
// s: the message string literal
// buffer: the buffer about to send message
int makeMsg(char* s,char* buffer,int buffer_size){
    printf("s len:%4d\n",(int)strlen(s));

    memset(buffer,'\0',buffer_size);
    int msg_len =  4 + strlen("begin") + strlen(s);
    sprintf(buffer,"%4dbegin %s",msg_len,s);

    return msg_len;
}

//---------------------------------------------------------------
// allocate page owenr ship equally amoung nodes whcih match node protection
void pageAlloc(int nodes,int page_num, int* page_table){
    int equal_pages = page_num/nodes;
    int remain_pages = page_num % nodes;
    int dist_remain_mark = remain_pages*(equal_pages +(remain_pages? 1: 0));
    
    for(int i = 0; i < page_num;++i){
        page_table[i] = i < dist_remain_mark? 
            i/(equal_pages + (remain_pages? 1:0)) :remain_pages + (i - dist_remain_mark)/equal_pages; 
    }
}


//---------------------------------------------------------------
#include <sys/mman.h>
#include <stdio.h>

#define BUFFER_SIZE 256 
#define ADDR  0x10a40f000 // start of the nmap address
int main() {

    smMemPartition_bak();

    /*
    int page_num = 30;
    int page_table[30] = {};
    int nodes = 13;

    pageAlloc(nodes, page_num,page_table);

    printf("Page table:\n");
    for(int i = 0;i < page_num;++i) printf("%d\n",page_table[i]);
    */



    /*

    //char s[BUFFER_SIZE] ="1 2 addr readReply hello world|3 write|1 2 addr readReply hello world|3 write|     " ;
    //char s[BUFFER_SIZE] ="1 2 addr readReply hello world|3 write|\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\01 2 addr readReply hello world|3 write|\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\01 2 addr readReply hello world|3 write|\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0" ;
    char s[BUFFER_SIZE] = "1 2 addr readReply hello world|1 2 addr readReply hello world|1 2 addr readReply hello world";
    //char s[BUFFER_SIZE] = "|";
    printf("Received message:%s\n",s);
    

    //printf("[SERVER] receive message:%s with len:%d\n", s,strlen(s));
    char* msgs[256];
    int token_len = splitToken(s,'|', msgs,sizeof(s));
    //int token_len = splitString(recv_buffer,"|", msgs);

    for(int i = 0; i < token_len;++i){
        printf("[MSG] whole msg %d:%s\n",token_len,msgs[i]);
        char* msg[256];
        int msg_len = splitString(msgs[i]," ", msg);
        for(int i = 0;i< msg_len;++i) printf("msg %d:%s\n",msg_len,msg[i]);
    }

    */
}
