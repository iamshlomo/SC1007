/*
In the case of 4 vertices, {1,2},{2,3},{3,4},{3,1},{4,2},
this is a strongly connected graph but the output will be
otherise. 

This is because the code is only designed to test for
either a direct edge between last node and initial node,
or indirect limited to last node to 1 intermediary to intial.

In the above case, 2 intermediaries are needed:
4-->2-->3-->1

*/
#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph{
    int V;
    int E;
    int *visited; //store the visited vertices
    int **matrix;
}Graph;

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} Stack;

// You should not change the prototypes of these functions
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
////GRAPH////////////////////////////////////////////
void printGraphMatrix(Graph );
////////////////////////////////////////////

int Connected (Graph);

int main()
{
    Graph g;
    int i,j;
    

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
       for(j=0;j<g.V;j++)
           g.matrix[i][j] = 0;
	
	g.visited = (int *) malloc(sizeof(int)*g.V);
    for(i=0;i<g.V;i++) g.visited[i] = 0;
    
    
    int V1, V2;
    printf("Enter a directed edge: (press a to stop)\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.matrix[V1-1][V2-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter a directed edge: (press a to stop)\n");
    }
    scanf("%*c");
    
    
    int res = Connected(g);
    if(res == 1)
        printf("The graph is strongly connected.\n");
    else
        printf("The graph is not strongly connected.\n");

    return 0;
}

int Connected (Graph g)
{
    //write your code here
    
    // 1. if no vertices at all
    if(g.V == 0) return 0;

    // 2. if only 1 vertice
    if(g.V == 1) return 1; 
    
    Stack s;
    s.size = 0;
    s.head = NULL;

    int j, stopNode, i, w, x[g.V], status;
    // array used to record all nodes that
    // are connected to the starting node

    // you want to test every single node
    for(j=0;j<g.V;j++)
    {
        push(&s,j+1);
        g.visited[j] = 1;

        while(isEmptyStack(s)==0)
        {
            w = peek(s);
            stopNode = 0;
            for(i=0; i<g.V; i++)
            {
                if(g.matrix[w-1][j]==1)x[w-1]=1; 
                if(g.matrix[w-1][i]==1 && g.visited[i]==0)
                {
                    push(&s, i+1);
                    g.visited[i]=1;
                    stopNode=1;
                    break;
                }
            }
            //after reaching the last unvisited node
            if(stopNode == 0)
            {
                //if this last node has an edge that links
                //back to the starting node, then
                //clearly the graph is cyclic this round
                //and is strongly connected, so no issue.

                //however, if there is no such edge,
                //there is chance this might not be a
                //strongly connected graph.
                if(g.matrix[w-1][j]==0)
                {
                    status = 0; 
                    // to test if the last node is connected
                    // to any other node that has an edge
                    // that links to the initial node
                    // to make it a cyclic graph
                    for(i=0;i<g.V;i++)
                    {
                        if(x[i]==1)
                        {
                            if(g.matrix[w-1][i]==1) status=1;
                        }
                    }
                    // if last node is not connected to
                    // any node that can link back to the
                    // initial node, cannot link back
                    // within 2 edges.
                    if(status == 0) return 0;
                }
                while(isEmptyStack(s)==0) pop(&s);
            }
        }
        for(i=0;i<g.V;i++)
        {
            g.visited[i]=0;
        }
    }
    return 1;
}


void printGraphMatrix(Graph g)
{
    int i,j;

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.matrix[i][j]);
        printf("\n");
    }

}

void push(Stack *sPtr, int vertex)
{
	StackNode *newNode;
    newNode= malloc(sizeof(StackNode));
    newNode->vertex = vertex;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if(sPtr==NULL || sPtr->head==NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

int isEmptyStack(Stack s)
{
     if(s.size==0) return 1;
     else return 0;
}

int peek(Stack s){
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
	while(pop(sPtr));
}
