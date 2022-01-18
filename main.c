#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include "lib.h"

int main()
{
    int size;
    char current;
    char inp[100] = "";
    struct Graph* graph;
    int i = 0;
    while((scanf("%c",&current))){
        if(current == '\n'||current == EOF){
            break;
        }
        if(current != ' ' && current != '\t' && current != '\r'){
            inp[i] = current;
            i++;
        }
    }
    for(int i = 0;i<strlen(inp);i++){
        if(inp[i] == 'A'){
            size = inp[i+1] - '0';
            if (i<5){
                graph=(struct Graph*)malloc(sizeof(struct Graph));
                graph = createGraph(graph,size);
            }
            else{
                freeGraph(graph);
                free(graph);
                graph=(struct Graph*)malloc(sizeof(struct Graph));
                graph = createGraph(graph,size);
            }
            continue;
        }
        if(inp[i] == 'n'){
            add_from_n(graph,i,inp);
        }
        if(inp[i] == 'B'){
            add_node(graph,i,inp);
            continue;
        }
        if(inp[i] == 'D'){
            remove_node(graph,i,inp);
            continue;
        }
        if(inp[i] == 'S'){
            int src =  inp[i+1]-'0';
            int dest = inp[i+2]-'0';
            printf("Dijsktra shortest path: %d \n",shortest(graph,src,dest));
            continue;
        }
        if(inp[i] == 'T'){
            tsp_cmd(graph,inp,i);
        }
    }
    freeGraph(graph);
    //free(graph->array);
    free(graph);
    return 0;
}