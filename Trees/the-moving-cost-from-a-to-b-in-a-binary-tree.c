#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode{
    int nodeV;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

typedef struct _queuenode{
    BTNode* node;
    struct _queuenode *next;
}QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

void printBTNode(BTNode *root, int space,int left);
//Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode * node);
int dequeue(Queue *qPtr);
BTNode* getFront(Queue q);
int isEmptyQueue(Queue q);

int twoNodesCost(BTNode* node, int nodeV1,int nodeV2);

int main()
{
    BTNode* root = (BTNode*) malloc(sizeof(BTNode));

    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    BTNode* node;
    enqueue(&q,root);

    int nodeV;
    char opL, opR;

    while(!isEmptyQueue(q)){
            scanf("%d %c %c",&nodeV,&opL,&opR);
            node = getFront(q);dequeue(&q);
            node->nodeV = nodeV;

            if(opL != '@'){
                node->left = (BTNode*) malloc(sizeof(BTNode));
                enqueue(&q,node->left);
            }
            else node->left =NULL;
            if(opR != '@'){
                node->right = (BTNode*) malloc(sizeof(BTNode));
                enqueue(&q,node->right);
            }
            else
                node->right = NULL;
    }

    int v1,v2;
    scanf("%d %d",&v1,&v2);
    int cost = twoNodesCost(root,v1,v2);

    printBTNode(root,0,0);

    printf("Distance is %d\n",cost);
    return 0;
}

void enqueue(Queue *qPtr, BTNode *node){
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->node = node;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr){
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

BTNode* getFront(Queue q){
    return q.head->node;
}

int isEmptyQueue(Queue q){
    if(q.size==0) return 1;
    else return 0;
}
void printBTNode(BTNode *root,int space,int left){
      if (root != NULL)
      {

          int i;
          for (i = 0; i < space-1; i++)
                 printf("|\t");


          if(i<space){
            if(left==1)
              printf("|---");
            else
              printf("|___");
          }

          printf("%d\n", root->nodeV);

          space++;
          printBTNode(root->left, space,1);
          printBTNode(root->right, space,0);
      }
}

int twoNodesCost(BTNode* node, int nodeV1,int nodeV2)
{
    BTNode* lowestCommonAncestor(BTNode* root, int x, int y);
    int cycle(BTNode* root, int x, int y);
// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail

// Write your code here
    BTNode* LCA = lowestCommonAncestor(node, nodeV1, nodeV2);
    return cycle(LCA, nodeV1, nodeV2);
}

BTNode* lowestCommonAncestor(BTNode* root, int x, int y){
    if(root->nodeV == x || root->nodeV == y) return root;
    if(root->left == NULL && root->right == NULL) return NULL; //leaf node

    //internal node
    BTNode *left = NULL, *right = NULL;
    if(root->left != NULL) left = lowestCommonAncestor(root->left, x, y);
    if(root->right != NULL) right = lowestCommonAncestor(root->right, x, y);
    if(left != NULL && right != NULL) return root;
    if(left != NULL && right == NULL) return left;
    if(left == NULL && right != NULL) return right;
    if(left == NULL && right == NULL) return NULL;
}

int cycle(BTNode* root, int x, int y){
    if(root->nodeV == x || root->nodeV == y) return root->nodeV;
    if(root->left == NULL && root->right == NULL) return 0;

    int res = 0, left = 0, right = 0;

    if(root->left != NULL) left = cycle(root->left, x, y);
    if(root->right != NULL) right = cycle(root->right, x, y);

    res += left; res+=right;
    if(left != 0 || right !=0) return res+(root->nodeV);
    return res;
}