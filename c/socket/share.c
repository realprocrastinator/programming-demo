#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h>
//#include <sm.h>


int main(int argc,char* argv[]){

    // register current node with the allocator node
    // args for the user node will be passed in in argc and argv
    // the total number of node process and th node id of the current node will 
    // be returned in nodes and nid
    int nodes,nid;

    printf("client has received args:\n");
    for(int i =0; i < argc;++i){
        printf(" %s",argv[i]);
    }
    printf("\n----------\n");


    //sm_node_init (int *argc, char **argv[], int *nodes, int *nid);





    return 0;
}



