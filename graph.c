#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include "lib.h"

//Function to create a new adjacency list node
struct Node* c_node( int src,int dest,int w)
{
    struct Node* q=(struct Node*)malloc(sizeof(struct Node));

    q->dest = dest;

    q->weight=w;

    q->next=NULL;

    return q;
}

struct Graph*createGraph(struct Graph* graph, int V)
{

    graph->V=V;

    // Create an array of adjacency lists.  Size of array will be V
    graph->array=(struct List*)malloc(sizeof(struct List)*V*2);




    // Initialize each adjacency list as empty by making head as NULL

    for(int i=0;i<V*2;i++)
    {
       
        graph->array[i].head=NULL;
        graph->array[i].dist=1000;
        graph->array[i].id = -1;
        graph->array[i].pass=0;
    }
    return graph;
}

int find_id(struct Graph* graph,int src){
    for(int j = 0;j<graph->V;j++){
        if(src == graph->array[j].id){
            return j;
        }
    }
    return -1;
}

// Adds an edge to a directed graph
struct Graph* addEdge(struct Graph* graph,int src,int des,int weight)
{
    int id = 0;
    if(find_id(graph,src)!= -1) {
        id = find_id(graph, src);
    }
    else{
        for(int j = 0;j<graph->V;j++){
            if(graph->array[j].id == -1 ){
                graph->array[j].id = src;
                id = j;
                break;
            }
        }
    }

    if(find_id(graph,des)== -1) {
        for(int j = 0;j<graph->V;j++){
            if(graph->array[j].id == -1 ){
                graph->array[j].id = des;
                break;
            }
        }
    }

    struct Node*temp=c_node(src,des,weight);

    temp->next=graph->array[id].head;


    graph->array[id].head=temp;
    return graph;

}

void freelist(struct Graph* graph,int v){
    struct Node* trav = graph->array[v].head;
    struct Node* trav_free = graph->array[v].head;
    int i = 0;
    while (trav&&graph->array[v].id!=-1){
        if(trav->next!=NULL)
            trav = trav->next;
        if(trav->next==NULL){
            trav_free->next=NULL;
            free(trav);
            trav =NULL;
            break;
        }    
        i++;
        if(i>4)
            break;
        trav = trav->next;
        trav_free= trav_free->next;
    }

}

void freeGraph(struct Graph* graph)
{
    for (int v = 0; v < graph->V; v++)
    {
        int e = 0;
        while(e<3){
            freelist(graph,v);
            e++;
        }
        if(graph->array[v].head){
            free(graph->array[0].head);
            graph->array[0].head=NULL;
        }
        //free(graph->array);
    }
}

struct Graph* add_from_n(struct Graph* graph,int i,char* inp){
    int src = inp[i+1]-'0';
    if(find_id(graph,src)== -1){
        for(int j = 0;j<graph->V;j++){
            if(graph->array[j].id == -1 ){
                graph->array[j].id = src;
                break;
            }
        }
    }
    for (int j = 0;(isalpha(inp[i+j+2]) == 0 && isalpha(inp[i+j+3]) == 0&&i+j+2< strlen(inp));j+=2){
        addEdge(graph,src,inp[i+j+2]-'0',inp[i+j+3]-'0');
    }
    return graph;
}

struct Graph* add_node(struct Graph* graph,int i,char* inp){
    int node = inp[i+1]-'0';
    int check = 0;
    for(int j = 0;j<graph->V;j++){
        if(node == graph->array[j].id){
            freelist(graph,j);
            //graph->array[j].head = NULL;
            free(graph->array[j].head);
            //add_from_n(graph,i,inp);
            check = 0;
        }
    }

    if(check == 0){
        graph->V=graph->V+1;
        //graph->array=(struct List*)malloc(sizeof(struct List)*V);
        graph->array[graph->V-1].head=NULL;
        graph->array[graph->V-1].id = node;
        struct Node*temp=c_node(node,inp[i+2]-'0',inp[i+3]-'0');
        temp->next=graph->array[graph->V-1].head;
        graph->array[graph->V-1].head=temp;
        struct Node*temp_2=c_node(node,inp[i+4]-'0',inp[i+5]-'0');
        temp_2->next=graph->array[graph->V-1].head;
        graph->array[graph->V-1].head=temp_2;
    }
    return graph;
}

void reset(struct Graph* graph){
    for (int v = 0; v < graph->V; ++v) {
        graph->array[v].pass = 0;
        graph->array[v].dist = 1000;
    }
}

struct Graph* remove_node(struct Graph* graph,int i,char* inp){
    int node = inp[i+1]-'0';
    for(int j = 0;j<graph->V;j++) {
        if (node == graph->array[j].id) {
            graph->array[j].id = -2;
            for (int v = 0; v < graph->V; v++) {
                struct Node *trav = graph->array[v].head;
                while (trav) {
                    if (trav->dest == node) {
                        trav->dest = -1;
                    }
                    trav = trav->next;
                }
            }
        }
    }
    return graph;
}