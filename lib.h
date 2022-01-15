struct Node
{
    int dest;
    int weight;
    struct Node* next;
};

struct List
{
    struct Node* head;
    int id;
    int dist;
    int pass;
};

struct Graph
{
    int V;
    struct List* array;
};

struct Node* c_node( int src,int dest,int w);

struct Graph*createGraph(int V);

int find_id(struct Graph* graph,int src);

struct Graph* addEdge(struct Graph* graph,int src,int des,int weight);

void printGraph(struct Graph* graph);

struct Graph* add_from_n(struct Graph* graph,int i,char* inp);

struct Graph* add_node(struct Graph* graph,int i,char* inp);

void reset(struct Graph* graph);

struct Graph* remove_node(struct Graph* graph,int i,char* inp);

struct Graph* travers_list(struct Graph* graph);

int shortest (struct Graph* graph,int src,int dest);

bool not_inside(char *arr,char c);

int tsp(struct Graph* graph,char *arr,char head);

void tsp_cmd(struct Graph* graph,char *inp,int i);



