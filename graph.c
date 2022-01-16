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

struct Graph*createGraph(int V)
{
    struct Graph* graph=(struct Graph*)malloc(sizeof(struct Graph));

    graph->V=V;

    // Create an array of adjacency lists.  Size of array will be V

    graph->array=(struct List*)malloc(sizeof(struct List)*V*2);

    // Initialize each adjacency list as empty by making head as NULL
    int i;

    for(i=0;i<V;i++)
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

void printGraph(struct Graph* graph)
{
    for (int v = 0; v < graph->V; v++)
    {
        struct Node* trav = graph->array[v].head;
        graph->array[v].dist = 1000;
        if(trav)
            printf("\n Adjacency list of vertex %d\n head ", graph->array[v].id);

        while (trav)
        {
            if(trav->dest != -1)
                printf("-> d-%d,w-%d", trav->dest,trav->weight);

            trav = trav->next;
        }
        printf("\n");
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
            graph->array[j].head = NULL;
            add_from_n(graph,i,inp);
            check = 1;
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
            graph->array[j].id = -1;
            graph->array[j].head = NULL;
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
