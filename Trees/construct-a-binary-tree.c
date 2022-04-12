#include <stdio.h>
#include <stdlib.h>

#define MAX_N 120

typedef struct _btnode{
    char id;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

void buildTree(BTNode** node, char* preO, char* postO);
void inOrder(BTNode *cur);
void preOrder(BTNode *cur);
void postOrder(BTNode *cur);

int main()
{
    char preO[MAX_N];
    char postO[MAX_N];
    scanf("%s",preO);
    scanf("%s",postO);

    BTNode* root=NULL;
    buildTree(&root,preO,postO);
    if(root==NULL) printf("error\n");
    preOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n");

    inOrder(root);
    printf("\n");

    return 0;
}
void inOrder(BTNode *cur){
    if (cur == NULL)
        return;

    inOrder(cur->left);
    printf("%c",cur->id);
    inOrder(cur->right);
}
void preOrder(BTNode *cur){
    if (cur == NULL)
        return;

    printf("%c",cur->id);
    preOrder(cur->left);
    preOrder(cur->right);
}
void postOrder(BTNode *cur){
    if (cur == NULL)
        return;

    postOrder(cur->left);
    postOrder(cur->right);
    printf("%c",cur->id);
}

void buildTree(BTNode** node, char* preO, char* postO)
{
// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
// Write your code here
    char postO2[MAX_N], preO2[MAX_N], preO3[MAX_N], postO3[MAX_N];
    BTNode* root = (BTNode*)malloc(sizeof(BTNode)), *leaf;
    *node = root;
    root->id = preO[0];

    int size = strlen(preO), i = 0;

    memmove(&preO[0],&preO[1],strlen(preO));
    memmove(&postO[(size-1)] , &postO[size], (strlen(postO)-(size-1)));
    size--;
    int head = preO[0];

    if(size == 0) return;
    if(size == 1)
    {
        leaf = (BTNode*)malloc(sizeof(BTNode));
        leaf->id = preO[0];
        leaf->left = NULL;
        leaf->right = NULL;
        (*node)->left = leaf;
        return;
    }
    
    //After 1 is settled, located where 2 is in postO
    for(i=0; i<size; i++)
    {
        if(postO[i] == head) break;
    }
    i++;
    
    strncpy(postO2,postO,i);
    strncpy(preO2,preO,i);
    postO2[i]='\0';
    preO2[i]='\0';
    
    strcpy(postO3,postO+i);
    strcpy(preO3,preO+i);
    
    if(preO2[0]!='\0')
    {
        leaf = (BTNode*)malloc(sizeof(BTNode));
        (*node)->left = leaf;
        buildTree(&(*node)->left, preO2, postO2);
    }
    if(preO3[0]!='\0')
    {
        leaf = (BTNode*)malloc(sizeof(BTNode));
        (*node)->right = leaf;
        buildTree(&(*node)->right, preO3,postO3);
    }
}