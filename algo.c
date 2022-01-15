#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#include<ctype.h>
#include "lib.h"

struct Graph* travers_list(struct Graph* graph){
    int yes = 0;
    int min_d;
    int pass = 0;
    int id;
    for (int v = 0; v < graph->V; ++v)
    {
        struct List trav = graph->array[v];
        if(trav.pass == 1){
            yes = 1;
            if(pass == 0){
                min_d = trav.dist;
                pass = 1;
            }
            if(trav.dist<=min_d){
                id = find_id(graph,trav.id);
                min_d = trav.dist;
            }
        }
    }
    if(yes==1){
        struct Node* trav = graph->array[id].head;
        graph->array[id].pass=0;
        while(trav){
            if((trav->weight+graph->array[id].dist<graph->array[find_id(graph,trav->dest)].dist)&&(trav->dest>-1))
            {

                graph->array[find_id(graph,trav->dest)].dist = trav->weight+graph->array[id].dist;
                graph->array[find_id(graph,trav->dest)].pass = 1;
            }
            trav = trav->next;
        }
        return graph;
    }
    return NULL;
}

int shortest (struct Graph* graph,int src,int dest){
    int id = find_id(graph,src);
    graph->array[id].dist = 0;
    graph->array[id].pass = 1;
    while(travers_list(graph)){
    }
     if(graph->array[find_id(graph,dest)].dist<100&&graph->array[find_id(graph,dest)].dist>0) {
         int dis  = graph->array[find_id(graph, dest)].dist;
         reset(graph);
         return dis;
     }
     else{
         reset(graph);
         return -1;
     }
}

bool not_inside(char *arr,char c){
    for(int i = 0;i< strlen(arr);i++) {
        if(c ==arr[i])
            return false;
    }
    return true;
}

int tsp(struct Graph* graph,char *arr,char head){
    char new_arr[7] = "";
    new_arr[0] = head;
    int sum = 0;
    for(int j = 0;j <= strlen(arr);j++) {
        int min = 1000;
        int temp;
        for (int i = 0; i + 1 <= strlen(arr); i++) {
            if (not_inside(new_arr, arr[i])) {
                temp = shortest(graph, new_arr[j]-'0', arr[i] - '0');
                if (temp < min && temp > 0) {
                    min = temp;
                    new_arr[j + 1] = arr[i];
                }
            }

        }
        if (min != 1000)
            sum += min;
    }

    if (strlen(new_arr) == strlen(arr)){
        return sum;}
    else
        return -1;
}

void tsp_cmd(struct Graph* graph,char *inp,int i){
    char arr[7] = "";
    int now = 0;
    for(int j=1; isdigit(inp[i+j]);j++) {

        if(find_id(graph,inp[i+j]-'0')>=0&&find_id(graph,inp[i+j]-'0'<10)){
        }
        if(not_inside(arr,inp[i+j])&& (find_id(graph,inp[i+j]-'0')>=0&&find_id(graph,inp[i+j]-'0'<10))){
            arr[now] = inp[i + j];
            now++;
        }
    }
    int min = 1000;
    int temp;
    for(int k = 0;k< strlen(arr);k++){
        temp = tsp(graph,arr,arr[k]);
        if(temp>0 && temp < min){
            min = temp;
        }
    }
    if(min == 1000){
        printf("TSP shortest path: -1\n");
    } else
        printf("TSP shortest path: %d\n",min);
}
